//
//  parse.c
//  digi
//
//  Created by mustafa on 7.06.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#include "vm.h"

#define READ_U4(data) ((unsigned char)data[0] << 24) | ((unsigned char)data[1] << 16) | ((unsigned char)data[2] << 8) | (unsigned char)data[3];
#define READ_U2(data) ((unsigned char)data[0] << 8) | (unsigned char)data[1];
#define READ_U1(data) (unsigned char)data[0];

Object *parse_cp_utf8(VM *vm, char *data, int len) {
    int charlen = get_utf8_length(data, len);
    JCHAR search[charlen];
    decode_utf8(data, len, search);
    
    Object *ptr = vm->strings;
    while(ptr) {
        if(STRLEN(ptr) == charlen && compare_chars(search, STRCHARS(ptr), charlen)) {
            return ptr;
        }
        ptr = STR(ptr, next);
    }
    
    Object *str = alloc_string_java(vm, search, charlen, 1);
    STR(str, next) = vm->strings;
    vm->strings = str;
    
    return str;
}

char *parse_constant_pool(VM *vm, char *data, CPItem** cpTarget) {
    int count = READ_U2(data); data += 2;
    CPItem *cp = (CPItem*)malloc(sizeof(CPItem)*count);
    *cpTarget = cp;
    memset(cp, 0, sizeof(CPItem)*count);
    
    for(int i=1; i<count; i++) {
        int type = READ_U1(data); data++;
        switch(type) {
            default:
                printf("!!!!!!!!!!!!!!!!!!Unknown CP %d\n", type);
                break;
        case 1: //CONSTANT_Utf8
            {
                int len = READ_U2(data); data += 2;
                cp[i].value.O = parse_cp_utf8(vm, data, len);
                //printf("CP = %s\n", string2c(cp[i].value.O));
                cp[i].type = 'O';
                data += len;
                //jstr_println(cp[i].value.O);
            }
            break;
        case 3: //CONSTANT_Integer
            {
                Int2Float i2f;
                i2f.c3 = (unsigned char)*data++;
                i2f.c2 = (unsigned char)*data++;
                i2f.c1 = (unsigned char)*data++;
                i2f.c0 = (unsigned char)*data++;
                cp[i].value.I = i2f.i;
                cp[i].type = 'I';
            }
            break;
        case 4: //CONSTANT_Float
            {
                Int2Float i2f;
                i2f.c3 = (unsigned char)*data++;
                i2f.c2 = (unsigned char)*data++;
                i2f.c1 = (unsigned char)*data++;
                i2f.c0 = (unsigned char)*data++;
                cp[i].value.F = i2f.f;
                cp[i].type = 'F';
            }
            break;
        case 5: //CONSTANT_Long
            {
                Long2Double l2d;
                l2d.c7 = (unsigned char)*data++;
                l2d.c6 = (unsigned char)*data++;
                l2d.c5 = (unsigned char)*data++;
                l2d.c4 = (unsigned char)*data++;
                l2d.c3 = (unsigned char)*data++;
                l2d.c2 = (unsigned char)*data++;
                l2d.c1 = (unsigned char)*data++;
                l2d.c0 = (unsigned char)*data++;
                cp[i].value.J = l2d.l;
                cp[i].type = 'J';
            }
            i++;
            break;
        case 6: //CONSTANT_Double
            {
                Long2Double l2d;
                l2d.c7 = (unsigned char)*data++;
                l2d.c6 = (unsigned char)*data++;
                l2d.c5 = (unsigned char)*data++;
                l2d.c4 = (unsigned char)*data++;
                l2d.c3 = (unsigned char)*data++;
                l2d.c2 = (unsigned char)*data++;
                l2d.c1 = (unsigned char)*data++;
                l2d.c0 = (unsigned char)*data++;
                cp[i].value.D = l2d.d;
                cp[i].type = 'D';
            }
            i++;
            break;

        case 7: //CONSTANT_Class
        case 8: //CONSTANT_String
        case 16: // CONSTANT_MethodType
        case 19: // CONSTANT_Module
        case 20: // CONSTANT_Package
                cp[i].index1 = READ_U2(data); data += 2;
                cp[i].type = type;
            break;
            
        case 9: //CONSTANT_Fieldref
        case 10: //CONSTANT_Methodref
        case 11: //CONSTANT_InterfaceMethodref
        case 12: //CONSTANT_NameAndType
        case 18: // CONSTANT_InvokeDynamic
            cp[i].index1 = READ_U2(data); data += 2;
            cp[i].index2 = READ_U2(data); data += 2;
            cp[i].type = type;
            break;
                
        case 15: //CONSTANT_MethodHandle
                cp[i].index1 = (unsigned char)*data++;
                cp[i].index2 = READ_U2(data); data += 2;
                cp[i].type = type;
                break;
        }
    }
    return data;
}

char *parse_field(VM *vm, char *data, Object *f, CPItem *cp) {
    FLD(f,flags) = READ_U2(data); data += 2;
    int name = READ_U2(data); data += 2;
    int signature = READ_U2(data); data += 2;
    FLD(f,name) = cp[name].value.O;
    FLD(f,signature) = cp[signature].value.O;
    
    //attributes
    int ac = READ_U2(data); data += 2;
    for(int k=0; k<ac; k++) {
        int tmp = READ_U2(data); data += 2;
        Object *attrName = cp[tmp].value.O;
        int len = READ_U4(data); data += 4;
        if(STRLEN(attrName) == 13 && compare_chars(STRCHARS(attrName), L"ConstantValue", 13)) {
            int ci = READ_U2(data); data += 2;
            FLD(f,constantValue) = &cp[ci].value;
        } else data += len;
        //READ_U2(data); data += 2; //name
        //int len = READ_U4(data); data += 4;
        //data += len;
    }
    return data;
}

void setup_method_args(Method *method) {
    JCHAR *ch = STRCHARS(method->signature);
    ch++; //(
    int count = 0;
    int jcount = 0;
    JINT tmp[256]; //enough for paramters? :)
    memset(tmp, 0, sizeof(tmp));
    
    if(!IS_STATIC(method->flags)) {
        count++;
        tmp[0] = 0;
        jcount++;
    }
    while(1) {
        if(*ch == ')') break;
        count++;
        tmp[count-1] = jcount++;
        while(*ch == '[') ch++;
        if(*ch == 'L') {
            while(*ch != ';') ch++;
        }
        if(*ch == 'D' || *ch == 'J') jcount++;
        ch++;
    }
    
    method->argMap = (JINT*)malloc(sizeof(JINT) * count);
    memcpy(method->argMap, tmp, sizeof(JINT) * count);
    method->argCount = count;
}

char *parse_code(VM *vm, char *data, Object *m, CPItem *cp) {
    MTH(m,maxStack) = READ_U2(data); data += 2;
    MTH(m,maxLocals) = READ_U2(data); data += 2;
    
    int codeSize = MTH(m,codeSize) = READ_U4(data); data += 4;
    if(codeSize > 0) {
        MTH(m,code) = malloc(codeSize);
        memcpy(MTH(m,code), data, codeSize);
        data += codeSize;
    }
    
    //TryCatch Info
    int count = MTH(m,catchTableSize) = READ_U2(data); data += 2;
    if(count > 0) {
        MTH(m,catchTable) = (CatchInfo*)vm_alloc(sizeof(CatchInfo) * count);
        for(int j=0; j<count; j++) {
            CatchInfo *c = &(MTH(m,catchTable))[j];
            c->start = READ_U2(data); data += 2; //start
            c->end = READ_U2(data); data += 2; //end
            c->pc = READ_U2(data); data += 2; //handler
            c->type = READ_U2(data); data += 2; //type
        }
    }
    
    //Attributes
    count = READ_U2(data); data += 2;
    for(int j=0; j<count; j++) {
        int tmp = READ_U2(data); data += 2;
        Object *attrName = cp[tmp].value.O;
        int len = READ_U4(data); data += 4;
        if(STRLEN(attrName)==18 && compare_chars(L"LocalVariableTable", STRCHARS(attrName), STRLEN(attrName))) {
            int lvCount = MTH(m,localVarTableSize) = READ_U2(data); data += 2;
            MTH(m,localVarTable) = (LocalVarInfo*)vm_alloc(lvCount * sizeof(LocalVarInfo));
            for(int z=0; z<lvCount; z++) {
                LocalVarInfo *vi = &(MTH(m,localVarTable))[z];
                vi->start = READ_U2(data); data += 2;
                vi->length = READ_U2(data); data += 2;
                int tmp = READ_U2(data); data += 2;
                vi->name = cp[tmp].value.O;
                tmp = READ_U2(data); data += 2;
                vi->signature = cp[tmp].value.O;
                vi->index = READ_U2(data); data += 2;
            }
        } else if(STRLEN(attrName)==15 && compare_chars(L"LineNumberTable", STRCHARS(attrName), STRLEN(attrName))) {
            MTH(m,lineNumberTableSize) = READ_U2(data); data += 2;
            MTH(m,lineNumberTable) = (LineNumberInfo*)vm_alloc(sizeof(LineNumberInfo) * MTH(m,lineNumberTableSize));
            for(int q=0; q<MTH(m,lineNumberTableSize); q++) {
                LineNumberInfo *l = &(MTH(m, lineNumberTable))[q];
                l->pc = READ_U2(data); data += 2;
                l->line = READ_U2(data); data += 2;
                l->breakpoint = 0;
            }
        } else
        data += len;
    }
    
    
    return data;
}

char *parse_annotations(VM *vm, char *data, CPItem *cp, int *externalFlags, Object **exName) {
    int count = READ_U2(data); data += 2;
    *externalFlags = 0;
    for(int k=0; k<count; k++) {
        int tmp = READ_U2(data); data += 2;
        Object *anClassName = cp[tmp].value.O;
        if(STRLEN(anClassName)==17 && compare_chars(STRCHARS(anClassName),L"Lgamavm/External;",17)) {
            *externalFlags = 1;
        }
        int valueCount = READ_U2(data); data += 2;
        for(int vc = 0; vc < valueCount; vc++) {
            tmp = READ_U2(data); data += 2;
            Object *valName = cp[tmp].value.O;
            int valType = (unsigned char)*data++;
            int valIndex = READ_U2(data); data += 2;
            if(*externalFlags) {
                if(STRLEN(valName) == 7 && compare_chars(STRCHARS(valName),L"isField",7)) {
                    *externalFlags |= cp[valIndex].value.I ? 2 : 0;
                } else
                if(STRLEN(valName) == 4 && compare_chars(STRCHARS(valName),L"name",4)) {
                    *exName = cp[valIndex].value.O;
                    if(cp[valIndex].value.O && STRLEN(cp[valIndex].value.O) == 0) *exName = NULL;
                }
            }
        }
    }
    return data;
}

char *parse_method(VM *vm, char *data, Object *m, CPItem *cp) {
    MTH(m,flags) = READ_U2(data); data += 2;
    int name = READ_U2(data); data += 2;
    int signature = READ_U2(data); data += 2;
    MTH(m,name) = cp[name].value.O;
    MTH(m,signature) = cp[signature].value.O;
    Method *mth = m->instance;

    int ac = READ_U2(data); data += 2;
    for(int i=0; i<ac; i++) {
        int tmp = READ_U2(data); data += 2; //name
        Object *attrName = cp[tmp].value.O;
        int attrlen = READ_U4(data); data += 4;
        int attrNameLen = STRLEN(attrName);
        if (attrNameLen == 4 && compare_chars(L"Code", STRCHARS(attrName), 4)) {
            data = parse_code(vm, data, m, cp);
        }
        else if(attrNameLen == 27 && compare_chars(L"RuntimeInvisibleAnnotations", STRCHARS(attrName), 27)) {
            data = parse_annotations(vm, data, cp, &mth->externalFlags, &mth->externalName);
        }
        else {
            data += attrlen;
        }

    }
    return data;
}

int parse_class(VM *vm, char *data, Object *clsObject) {
    int magic = READ_U4(data); data += 4;
    if(magic != 0xCAFEBABE)
        return 0;
    READ_U2(data); data += 2; //major
    READ_U2(data); data += 2; //minor

    Class *cls = (Class*)clsObject->instance;
    CPItem *cp = NULL;
    data = parse_constant_pool(vm, data, &cp);
    cls->cp = cp;
    cls->flags = READ_U2(data); data += 2;
    JINT nameIndex = READ_U2(data); data += 2;
    JINT superIndex = READ_U2(data); data += 2;
    cls->name = cp[cp[nameIndex].index1].value.O;
    Object *superName = cp[cp[superIndex].index1].value.O;
    if(superName)
        cls->superClass = resolve_class(vm, STRCHARS(superName), STRLEN(superName), 0, NULL);
    
    //parse interfaces
    int count = READ_U2(data); data += 2;
    if(count > 0) {
        cls->interfaces = alloc_array(vm, get_arrayclass_of(vm, vm->jlClass), count, 1);
        for(int i=0; i<count; i++) {
            int iindex = READ_U2(data); data += 2;
            Object *iname = cls->cp[cls->cp[iindex].index1].value.O;
            Object *intf = resolve_class(vm, STRCHARS(iname), STRLEN(iname), 0, NULL);
            if(!intf || vm->exception) return 0;
            ((Object**)cls->interfaces->instance)[i] = intf;
        }
    }
    
    //parse fields
    count = READ_U2(data); data += 2;
    if(count > 0) {
        cls->fields = alloc_array(vm, get_arrayclass_of(vm, vm->jlField), count, 1);
        for(int i=0; i<count; i++) {
            Object *field = alloc_object(vm, vm->jlField, 1);
            ((Object**)cls->fields->instance)[i] = field;
            FLD(field, declaringClass) = clsObject;
            data = parse_field(vm, data, field, cp);
        }
    }
    
    //parse methods
    count = READ_U2(data); data += 2;
    if(count > 0) {
        cls->methods = alloc_array(vm, get_arrayclass_of(vm, vm->jlMethod), count, 1);
        for(int i=0; i<count; i++) {
            Object *mth = alloc_object(vm, vm->jlMethod, 1);
            ((Object**)cls->methods->instance)[i] = mth;
            MTH(mth, declaringClass) = clsObject;
            data = parse_method(vm, data, mth, cp);
            MTH(mth, entry) =
            IS_NATIVE(MTH(mth, flags)) ? &vm_native_exec : &vm_interpret_exec;
            setup_method_args((Method*)mth->instance);
            
            Object *mname = MTH(mth, name);
            if(!IS_STATIC(MTH(mth,flags)) && STRLEN(mname)==8 &&
               compare_chars(L"finalize", STRCHARS(mname), 8)) {
                CLS(clsObject, finalizer) = mth;
            }
        }
    }

    //class attrs
    count = READ_U2(data); data += 2;
    for(int i=0; i<count; i++) {
        int tmp = READ_U2(data); data += 2;
        Object *attrName = cls->cp[tmp].value.O;
        int len = READ_U4(data); data += 4;
        if(STRLEN(attrName)==10 && compare_chars(L"SourceFile",STRCHARS(attrName),10)) {
            tmp = READ_U2(data); data += 2;
            cls->sourceFile = cls->cp[tmp].value.O;
        }
        else if(STRLEN(attrName) == 27 && compare_chars(L"RuntimeInvisibleAnnotations", STRCHARS(attrName), 27)) {
            data = parse_annotations(vm, data, cp, &cls->externalFlags, &cls->externalName);
        }

        else data += len;
    }

    return 1;
}

