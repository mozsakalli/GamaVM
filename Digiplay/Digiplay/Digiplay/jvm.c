//
//  jvm.c
//  Digiplay
//
//  Created by mustafa on 9.05.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#include "jvm.h"
#include "miniz.h"
#include "natives.h"

extern void *__platform_read_file(const char* path, int *size);


#define READ_U4(data) ((unsigned char)data[0] << 24) | ((unsigned char)data[1] << 16) | ((unsigned char)data[2] << 8) | (unsigned char)data[3];
#define READ_U2(data) ((unsigned char)data[0] << 8) | (unsigned char)data[1];
#define READ_U1(data) (unsigned char)data[0];

jint compare_string_string(Object* jstr1, Object* jstr2) {
    if(jstr1 == jstr2) return 1;
    if(!jstr1 || !jstr2) return 0;
    StringFields *str1 = jstr1->instance;
    StringFields *str2 = jstr2->instance;
    if(str1->length != str2->length) return 0;
    jchar *ch1 = ARRAY_DATA_C(str1->chars) + str1->start;
    jchar *ch2 = ARRAY_DATA_C(str2->chars) + str2->start;
    int len = str1->length;
    for(int i=0; i<len; i++) if(ch1[i] != ch2[i]) return 0;
    return 1;
}

jint compare_string_cstring(Object* jstr1, const char *str2) {
    if(!jstr1) return 0;
    int len = (int)strlen(str2);
    StringFields *str1 = jstr1->instance;
    if(str1->length != len) return 0;
    jchar *ch1 = ARRAY_DATA_C(str1->chars) + str1->start;
    for(int i=0; i<len; i++) if(ch1[i] != str2[i]) return 0;
    return 1;
}

jint compare_string(void *str1, void *str2, int isString) {
    return isString ? compare_string_string((Object*)str1, (Object*)str2) : compare_string_cstring((Object*)str1, (const char *)str2);
}

Object *str_intern(VM *vm, Object *str) {
    /*
    StringPool *ptr = vm->strings;
    while(ptr) {
        if(compare_string_string(ptr->str, str)) {
            free(str->chars);
            free(str);
            return ptr->str;
        }
        ptr = ptr->next;
    }
    
    ptr = (StringPool*)malloc(sizeof(StringPool));
    ptr->str = str;
    ptr->next = vm->strings;
    vm->strings = ptr;
    */
    return str;
}

char *string2c(Object *jstr) {
    static char tmp[1024];
    StringFields *str = jstr->instance;
    int len = str->length;
    if(len > 1023) len = 1023;
    jchar *chars = (jchar *)str->chars->instance;
    chars += str->start;
    for(int i=0; i<len; i++) tmp[i] = chars[i];
    tmp[len] = 0;
    return tmp;
}

void jstr_print(Object *jstr) {
    StringFields *str = jstr->instance;
    char buf[2048];
    for(int i=0; i<str->length; i++)
        buf[i] = ((jchar*)str->chars->instance)[str->start+i];
    buf[str->length] = 0;
    printf("%s", buf);
}

void jstr_println(Object *str) {
    jstr_print(str);
    printf("\n");
}

void print_stack_trace(VM *vm) {
    for(int i=vm->exceptionFP; i>=0; i--) {
        Frame *f = &vm->frames[i];
        if(f->method) {
            printf("at %s:", string2c(CLS_FIELD(MTH_FIELD(f->method,declaringClass),name)));
            printf(":%s", string2c(MTH_FIELD(f->method,name)));
            printf(":%s line=%d\n", string2c(MTH_FIELD(f->method,signature)), f->line);
        }
    }
}

Object
java_lang_Object, java_lang_B, java_lang_Z, java_lang_C, java_lang_S, java_lang_I, java_lang_F, java_lang_D, java_lang_J,
java_lang_V,java_lang_C1D,java_lang_Class, java_lang_String, java_lang_reflect_Field, java_lang_reflect_Method,
java_lang_Class1D, java_lang_reflect_Field1D,java_lang_reflect_Method1D;

Object *vm_find_string(VM *vm, jchar *utf, jint len) {
    StringPool *ptr = vm->strings;
    while(ptr) {
        StringFields *strf = ptr->str->instance;
        if(strf->length == len) {
            int equals = 1;
            jchar *chars = (jchar*)strf->chars->instance;
            for(int i=0; i<len; i++)
                if(chars[i] != utf[i]) {
                    equals = 0;
                    break;
                }
            if(equals) {
                return ptr->str;
            }
        }
        ptr = ptr->next;
    }
    return NULL;
}


Object* parse_utf8(VM *vm, char *data, int length) {
    char *end = data + length;
    char *ptr = data;
    int jlen = 0;
    while(ptr < end) {
        unsigned int c = *ptr++;
        jlen++;
        if(c < 0x80) {}
        else if(c < 0xE0) ptr++;
        else if(c < 0xF0) ptr += 2;
        else ptr += 3;
    }
    jint strlen = jlen;
    jchar buf[strlen];
    
    //jchar* target = &buf[0];// (jchar*)str->chars->data;
    ptr = data;
    jlen = 0;
    while (ptr < end) {
        if(jlen > strlen) {
            printf("!!!!!!!!!!!!! UTF PANIC\n");
        }
        unsigned int c = *ptr++;
        if (c < 0x80) {
            buf[jlen++] = c;
        } else if (c < 0xE0) {
            buf[jlen++] = (((c & 0x3F) << 6) | ((*ptr++) & 0x7F));
        } else if (c < 0xF0) {
            unsigned int c2 = *ptr++;
            buf[jlen++] = (char) (((c & 0x1F) << 12) | ((c2 & 0x7F) << 6) | ((*ptr++) & 0x7F));
        } else {
            unsigned int c2 = *ptr++;
            unsigned int c3 = *ptr++;
            buf[jlen++] = ((c & 0x0F) << 18) | ((c2 & 0x7F) << 12) | ((c3 & 0x7F) << 6) | ((*ptr++ & 0x7F));
        }
    }
    
    Object *str = vm_find_string(vm, buf, strlen);
    if(!str) {
        str = alloc_string_utf_nogc(vm, &buf[0], strlen);
        StringPool *sp = (StringPool*)malloc(sizeof(StringPool));
        sp->str = str;
        sp->next = vm->strings;
        vm->strings = sp;
    }
    return str;//alloc_string_utf_nogc(vm, &buf[0], strlen);
}

void parse_setup_method_args(MethodFields *method) {
    StringFields *signature = (StringFields*)method->signature->instance;
    jchar *ch = ARRAY_DATA_C(signature->chars);
    ch++; //(
    int count = 0;
    int jcount = 0;
    jint tmp[256]; //enough for paramters? :)
    if(!IS_STATIC(method)) {
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
    method->argMap = (jint*)malloc(sizeof(jint) * count);
    memcpy(method->argMap, tmp, sizeof(jint) * count);
    method->argCount = count;
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
                cp[i].value.O = (Object*)parse_utf8(vm, data, len);
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

Object *alloc_class(VM *vm, Object *name) {
    Object *boot = NULL;
    if(compare_string_cstring(name, "java/lang/Object")) boot = &java_lang_Object;
    else if(compare_string_cstring(name, "java/lang/String")) boot = &java_lang_String;
    else if(compare_string_cstring(name, "java/lang/Class")) boot = &java_lang_Class;
    else if(compare_string_cstring(name, "java/lang/reflect/Field")) boot = &java_lang_reflect_Field;
    else if(compare_string_cstring(name, "[java/lang/reflect/Field;")) boot = &java_lang_reflect_Field1D;
    else if(compare_string_cstring(name, "java/lang/reflect/Method")) boot = &java_lang_reflect_Method;
    else if(compare_string_cstring(name, "[java/lang/reflect/Method;")) boot = &java_lang_reflect_Method1D;
    else if(compare_string_cstring(name, "B")) boot = &java_lang_B;
    else if(compare_string_cstring(name, "Z")) boot = &java_lang_Z;
    else if(compare_string_cstring(name, "C")) boot = &java_lang_C;
    else if(compare_string_cstring(name, "[C")) boot = &java_lang_C1D;
    else if(compare_string_cstring(name, "S")) boot = &java_lang_S;
    else if(compare_string_cstring(name, "I")) boot = &java_lang_I;
    else if(compare_string_cstring(name, "F")) boot = &java_lang_F;
    else if(compare_string_cstring(name, "D")) boot = &java_lang_D;
    else if(compare_string_cstring(name, "J")) boot = &java_lang_J;

    if(!boot) {
        boot = (Object*)malloc(sizeof(Object));
        memset(boot, 0, sizeof(Object));
    }
    if(!boot->instance) {
        boot->instance = malloc(sizeof(ClassFields));
        memset(boot->instance, 0, sizeof(ClassFields));
    }
    boot->cls = &java_lang_Class;
    boot->gc.atomic = 1;
    
    return boot;
}

void* vm_resolve_native_method(VM *vm, Object *method) {
    NativeMethodInfo *ptr = &NATIVES[0];

    Object *name = MTH_FIELD(method, name);
    Object *sign = MTH_FIELD(method, signature);
    Object *cls = CLS_FIELD(MTH_FIELD(method, declaringClass), name);
    
    while (ptr && ptr->cls) {
        if(compare_string_cstring(cls, ptr->cls) &&
           compare_string_cstring(name, ptr->name) &&
           compare_string_cstring(sign, ptr->sign)) {
            return ptr->handle;
        }
        ptr++;
    }
    return NULL;
}

void vm_invoke_native(VM *vm, Object *method, VAR *args) {
    void *handler = vm_resolve_native_method(vm, method);
    if(handler) {
        MethodFields *m = method->instance;
        m->entry = handler;
        ((JVM_CALL)handler)(vm, method, args);
        return;
    }

    
    printf("!!! Native !!! %s", string2c(CLS_FIELD(MTH_FIELD(method, declaringClass),name)));
    printf(":%s",string2c(MTH_FIELD(method,name)));
    printf(":%s\n",string2c(MTH_FIELD(method,signature)));
    throw_nullpointerexception(vm);
}
 
Object *parse_class(VM *vm,char *data, void **entries) {
    int magic = READ_U4(data); data += 4;
    if(magic != 0xCAFEBABE)
        return NULL;
    READ_U2(data); data += 2; //major
    READ_U2(data); data += 2; //minor
    
    CPItem *cp = NULL;
    data = parse_constant_pool(vm, data, &cp);
    
    jint accessFlags = READ_U2(data); data += 2;
    jint nameIndex = READ_U2(data); data += 2;
    jint superIndex = READ_U2(data); data += 2;
    Object *clsName = cp[cp[nameIndex].index1].value.O;
    printf("-- parsing: %s\n", string2c(clsName));
    //Object *superName = cp[cp[superIndex].index1].value.O;
    //Object *superClass = NULL;
    /*if(superName) {
        superClass = resolve_class(vm, superName, 1);
        if(vm->exception) return NULL;
    }*/
    
    Object *clso = alloc_class(vm, clsName);
    ClassFields *cls = clso->instance;
    //clso->cls = &java_lang_Class;
    cls->cp = cp;

    cls->accessFlags = accessFlags;
    cls->name = clsName;
    cls->superIndex = superIndex;
    //cls->superClass = superClass;
    //cls->nameIndex = nameIndex;
    //cls->superIndex = superIndex;
    //cls->name = CLS_NAME(cls);
    //cls->superName = CLS_SUPERNAME(cls);
    
    //printf("--parsing: %s  super=", string2c(cls->name));
    //printf("%s\n", superName ? string2c(superName) : "NULL");
    
    int count = READ_U2(data); data += 2;
    if(count > 0) {
        cls->interfaces = alloc_object_array_nogc(vm, resolve_class(vm,"[Ljava/lang/Class;",0), count);
        for(int i=0; i<count; i++) {
            int iindex = READ_U2(data); data += 2;
            Object *iname = cls->cp[cls->cp[iindex].index1].value.O;
            Object *intf = resolve_class(vm, iname, 1);
            if(!intf) goto ERROR;
            ARRAY_DATA_O(cls->interfaces)[i] = intf;
        }
    }
    
    //fields
    int len = READ_U2(data); data += 2;
    Object* arr = cls->fields = alloc_object_array_nogc(vm, &java_lang_reflect_Field1D, len);
    //arr->length = len;
    //arr->length = READ_U2(data); data += 2;
    if(arr->length > 0) {
        //arr->data = malloc(sizeof(Field*) * arr->length);
        //Field** fields = (Field**)arr->data;
        for(int i=0; i<arr->length; i++) {
            Object *fo = alloc_object_nogc(vm, &java_lang_reflect_Field);
            ARRAY_DATA_O(arr)[i] = fo;
            //Field *f = fields[i] = (Field*)malloc(sizeof(Field));
            FieldFields *f = fo->instance;
            f->declaringClass = clso;
            f->accessFlags = READ_U2(data); data += 2;
            int nameIndex = READ_U2(data); data += 2;
            int signatureIndex = READ_U2(data); data += 2;
            f->name = cp[nameIndex].value.O;
            f->signature = cp[signatureIndex].value.O;
            fo->cls = &java_lang_reflect_Field;
            int ac = READ_U2(data); data += 2;
            for(int k=0; k<ac; k++) {
                READ_U2(data); data += 2; //name
                int len = READ_U4(data); data += 4;
                data += len;
            }
        }
    }
    
    //methods
    len = READ_U2(data); data += 2;
    arr = cls->methods = alloc_object_array_nogc(vm, &java_lang_reflect_Method1D, len);
    arr->length = len;
    if(arr->length > 0) {
        //arr->data = malloc(sizeof(Method*) * arr->length);
        //Method** methods = (Method**)arr->data;
        for(int i=0; i<arr->length; i++) {
            Object *mo = ARRAY_DATA_O(arr)[i] = alloc_object_nogc(vm, &java_lang_reflect_Method);
            MethodFields *m = mo->instance;
            m->accessFlags = READ_U2(data); data += 2;
            int nameIndex = READ_U2(data); data += 2;
            int signatureIndex = READ_U2(data); data += 2;
            m->declaringClass = clso;
            m->name = cp[nameIndex].value.O;
            m->signature = cp[signatureIndex].value.O;
            if(!IS_STATIC(m) && compare_string_cstring(m->name, "finalize")) cls->finalizer = mo;
            parse_setup_method_args(m);
            m->entry = entries ? entries[i] : (IS_NATIVE(m) ? (void*)&vm_invoke_native : (void*)&vm_interpret_method);
            
            //printf("-- method - %d: %s\n", i, string2c(MTH_FIELD(mo, name)));
            //m->cls = &java_lang_reflect_Method;
            /*
            printf("Method: argc:%d ",m->argCount);
            jstr_print((String*)cls->cp[m->nameIndex].value.O);
            printf(" ");
            jstr_print((String*)cls->cp[m->signatureIndex].value.O);
            printf("\n");
            */
            int ac = READ_U2(data); data += 2;
            for(int k=0; k<ac; k++) {
                int nameIndex = READ_U2(data); data += 2; //name
                int attrlen = READ_U4(data); data += 4;
                Object *attrName = cls->cp[nameIndex].value.O;
                //printf("Attr: ");jstr_print(attrName);printf(" of %d\n",ac);
                if(compare_string_cstring(attrName, "Code")) {
                    m->maxStack = READ_U2(data); data += 2;
                    m->maxLocals = READ_U2(data); data += 2;
                    m->declaringClass = clso;
                    
                    int codeSize = m->codeSize = READ_U4(data); data += 4;
                    if(codeSize > 0) {
                        m->code = malloc(codeSize);
                        memcpy(m->code, data, codeSize);
                        data += codeSize;
                    }
                    
                    m->catchTableSize = READ_U2(data); data += 2;
                    if(m->catchTableSize > 0) {
                        m->catchTable = (CatchInfo*)malloc(sizeof(CatchInfo) * m->catchTableSize);
                        for(int j=0; j<m->catchTableSize; j++) {
                            CatchInfo *c = &m->catchTable[j];
                            c->start = READ_U2(data); data += 2; //start
                            c->end = READ_U2(data); data += 2; //end
                            c->pc = READ_U2(data); data += 2; //handler
                            c->type = READ_U2(data); data += 2; //type
                        }
                    }
                    //attrs
                    int cattrcount = READ_U2(data); data += 2;
                    for(int j=0; j<cattrcount; j++) {
                        int tmp = READ_U2(data); data += 2;
                        Object *attrName = cls->cp[tmp].value.O;
                        int len = READ_U4(data); data += 4;
                        if(compare_string_cstring(attrName, "LocalVariableTable")) {
                            int lvCount = READ_U2(data); data += 2;
                            //LocalVarInfo tmpLocals[m->maxLocals];
                            m->localVarTable = (LocalVarInfo*)malloc(lvCount * sizeof(LocalVarInfo));
                            for(int z=0; z<lvCount; z++) {
                                LocalVarInfo *vi = &m->localVarTable[z];
                                vi->start = READ_U2(data); data += 2;
                                vi->length = READ_U2(data); data += 2;
                                int tmp = READ_U2(data); data += 2;
                                vi->name = cls->cp[tmp].value.O;
                                tmp = READ_U2(data); data += 2;
                                vi->signature = cls->cp[tmp].value.O;
                                vi->index = READ_U2(data); data += 2;
                                //printf("local %d: ",vi->index);
                                //jstr_print(vi->name); printf(" : "); jstr_print(vi->signature); printf("\n");
                            }
                        } else if(compare_string_cstring(attrName, "LineNumberTable")) {
                            m->lineNumberTableSize = READ_U2(data); data += 2;
                            m->lineNumberTable = (LineNumberInfo*)malloc(sizeof(LineNumberInfo) * m->lineNumberTableSize);
                            for(int q=0; q<m->lineNumberTableSize; q++) {
                                m->lineNumberTable[q].pc = READ_U2(data); data += 2;
                                m->lineNumberTable[q].line = READ_U2(data); data += 2;
                            }
                        } else
                        data += len;
                    }
                } else {
                    data += attrlen;
                }
            }
        }
        
        //class attrs
        count = READ_U2(data); data += 2;
        for(int i=0; i<count; i++) {
            int tmp = READ_U2(data); data += 2;
            Object *attrName = cls->cp[tmp].value.O;
            int len = READ_U4(data); data += 4;
            if(compare_string_cstring(attrName, "SourceFile")) {
                tmp = READ_U2(data); data += 2;
                cls->source_file = cls->cp[tmp].value.O;
            } else data += len;
        }
    }

    
    /*if(cls->methods)
        for(int i=0; i<cls->methods->length; i++) {
            Object *om = ARRAY_DATA_O(cls->methods)[i];
            printf("   %s\n",string2c(CLS_FIELD(om->cls, name)));
            printf("   meth:%p\n", MTH_FIELD(om, name));
        }
     */
    return clso;
    
ERROR:
    return NULL;
}

//AOTClassData* AOTSLOTS[4] = {NULL, NULL, NULL, NULL};
extern AOTClassData AOT[];
AOTClassData *find_aot_class(void *name, int isString) {
    //for(int i=0; i<4; i++) {
    /*
        AOTClassData *aot = &AOT[0];
        while (aot && aot->name) {
            if(!isString) {
                if(!strcmp((const char *)name, aot->name)) return aot;
            } else {
                if(compare_string_cstring((Object*)name, aot->name)) return aot;
            }
            aot++;
        }
    //}
     */
    return NULL;
}
Object *find_class(VM *vm, void *name, int isString) {
    Object *cls = vm->classes;
    while (cls) {
        //printf("cls: %s\n", string2c(CLS_FIELD(cls, name)));
        if(compare_string(CLS_FIELD(cls,name), name, isString)) return cls;
        cls = CLS_FIELD(cls, listNext);
    }
    return NULL;
}
Object *load_class(VM *vm, void *name, int isString) {
    printf("-- loading: %s\n", isString ? string2c((Object*)name) : (char*)name);
    AOTClassData *aot = find_aot_class(name, isString);
    if(aot) {
        //AOT class found
        Object *cls = parse_class(vm, aot->data, aot->methods);
        CLS_FIELD(cls,listNext) = vm->classes;
        vm->classes = cls;
        return cls;
    }

    int jarSize;
    void *jar = __platform_read_file("jvm_test.jar", &jarSize);
    if(jar) {
        char tmp[512];
        char *str = tmp;
        mz_zip_archive zip = {0};
        if(mz_zip_reader_init_mem(&zip, jar, jarSize, 0) == MZ_FALSE) {
            free(jar);
            return NULL;
        }
        if(isString) str += sprintf(str,"%s", string2c((Object*)name)); else str += sprintf(str, "%s", (char*)name);
        sprintf(str, ".class");
        int file_index = mz_zip_reader_locate_file(&zip, tmp, NULL, 0);//
        mz_zip_archive_file_stat file_stat = {0};
        if (!mz_zip_reader_file_stat(&zip, file_index, &file_stat)) {
            free(jar);
            return NULL;
        }
        size_t uncompressed_size = (size_t) file_stat.m_uncomp_size;
        void *p = mz_zip_reader_extract_file_to_heap(&zip, file_stat.m_filename, &uncompressed_size, 0);
        if (!p) {
            free(jar);
            return NULL;
        } else {
            Object *cls = parse_class(vm, (char *)p, NULL);
            mz_free(p);
            free(jar);
            if(cls) {
                CLS_FIELD(cls,listNext) = vm->classes;
                vm->classes = cls;
                return cls;
            }
        }
    }
    return NULL;
}
/*
String* make_java_string(const char* chars) {
    String* str = malloc(sizeof(String));
    int len = (int)strlen(chars);
    str->cls = &java_lang_String;
    str->chars = malloc(sizeof(Array) + sizeof(jchar) * len);
    str->chars->cls = &java_lang_C1D;
    str->chars->length = (int)strlen(chars);
    jchar* target = (jchar*)str->chars->data;
    for(int i=0; i<len; i++) target[i] = chars[i];
    str->start = 0;
    str->length = len;
    
    return str;
}
*/
Object *find_method(Object *clso, void *name, void *signature, int isString) {
    ClassFields *cls = clso->instance;
    if(cls->methods) {
        Object **methods = (Object**)cls->methods->instance;
        for(int i=0; i<cls->methods->length; i++) {
            MethodFields *m = methods[i]->instance;
            if(compare_string(m->name, name, isString) && compare_string(m->signature, signature, isString))
                return methods[i];
        }
    }
    return NULL;
}

Object *find_field(Object *clso, void *name, int isString) {
    ClassFields *cls = clso->instance;
    Object **fields = (Object**)cls->fields->instance;
    for(int i=0; i<cls->fields->length; i++) {
        FieldFields *f = fields[i]->instance;
        if(compare_string(f->name, name, isString))
            return fields[i];
    }
    return NULL;
}

//jint PRIMSIZE[] = {sizeof(jbyte),sizeof(jbool),sizeof(jchar),sizeof(jshort),sizeof(jint),sizeof(jfloat),sizeof(jlong),sizeof(jdouble)};
jint get_prim_size(int chr) {
    switch(chr) {
        case 'B': return sizeof(jbyte);
        case 'Z': return sizeof(jbool);
        case 'C': return sizeof(jchar);
        case 'S': return sizeof(jshort);
        case 'I': return sizeof(jint);
        case 'F': return sizeof(jfloat);
        case 'J': return sizeof(jlong);
        case 'D': return sizeof(jdouble);
        default : return sizeof(ObjectPtr);
    }
}
jint get_signature_size(Object *signature) {
    jint chr = ARRAY_DATA_C(((StringFields*)signature->instance)->chars)[0];
    return get_prim_size(chr);
}

Object *find_override_method(Object *cls, Object *method) {
    Object *name = ((MethodFields*)method->instance)->name;
    Object *sign = ((MethodFields*)method->instance)->signature;
    while(cls) {
        Object *found = find_method(cls, name, sign, 1);
        if(found) return found;
        cls = CLS_FIELD(cls, superClass);
    }
    return NULL;
}

void clInit(VM *vm, Object *clso) {
    ClassFields *cls = clso->instance;
    if(!cls->initialized) {
        cls->initialized = 1;
        
        if(!cls->superClass && clso != &java_lang_Object && cls->cp) {
            Object *superName = cls->cp[cls->cp[cls->superIndex].index1].value.O;
            if(superName) {
                cls->superClass = resolve_class(vm, superName, 1);
                if(!cls->superClass) return;
            }
        }
            
        //Setup Fields
        cls->instanceSize = 0;
        int parentSize = 0;
        if(cls->superClass) {
            clInit(vm, cls->superClass);
            parentSize = cls->instanceSize = CLS_FIELD(cls->superClass,instanceSize);
        }
        if(cls->interfaces) {
            for(int i=0; i<cls->interfaces->length; i++)
                clInit(vm, ((Object**)cls->interfaces->instance)[i]);
        }
        
        int globalSize = 0;
        if(cls->fields) {
            Object** fields = (Object**)cls->fields->instance;
            for(int i=0; i<cls->fields->length; i++) {
                FieldFields *f = fields[i]->instance;
                int size = get_signature_size(f->signature);
                if(IS_STATIC(f)) {
                    f->offset = globalSize;
                    globalSize += size;
                } else {
                    f->offset = cls->instanceSize;
                    cls->instanceSize += size;
                    //printf("   %s:%d\n",string2c(f->name),size);
                }
            }
            
            //printf("%s size=%d string=%d  parent=%d\n",string2c(cls->name),cls->instanceSize+sizeof(Object),(int)sizeof(Class),parentSize);
        }
        //globalSize = ((globalSize + 3) / 4) * 4;
        //cls->instanceSize = cls->instanceSize;
        if(globalSize > 0) {
            cls->globals = malloc(globalSize); //malloc(globalSize);
            memset(cls->globals, 0, globalSize);
        }
        
        if(cls->superClass) cls->maxMethodIndex = CLS_FIELD(cls->superClass,maxMethodIndex);
        
        //Give methods an index
        if(cls->methods && IS_INTERFACE(cls)) {
            for(int i=0; i<cls->methods->length; i++) {
                Object *mo = ARRAY_DATA_O(cls->methods)[i];
                //printf(" ----m %d: %s\n", i, string2c(MTH_FIELD(mo, name)));
                MethodFields *m = mo->instance;
                //printf("-- %s\n", string2c(m->name));
                //if(IS_INTERFACE(cls)) {
                    m->iTableIndex = vm->itable_counter++;
                    if(cls->maxMethodIndex < m->iTableIndex) cls->maxMethodIndex = m->iTableIndex;
                //}
            }
        }
        /*
        if(IS_INTERFACE(cls))
            cls->tableIndex = ITABLE_INDEX++;
        else
            cls->tableIndex = VTABLE_INDEX++;
         */
        
        //Setup Interface Table
        if(cls->superClass) {
            cls->itable = realloc(cls->itable, sizeof(Object*) * CLS_FIELD(cls->superClass,iTableSize));
            memcpy(cls->itable, CLS_FIELD(cls->superClass,itable), sizeof(Object*) * CLS_FIELD(cls->superClass,iTableSize));
            cls->iTableSize = CLS_FIELD(cls->superClass,iTableSize);
        }
        if(cls->interfaces) {
            int maxIndex = 0;
            for(int i=0; i<cls->interfaces->length; i++) {
                Object *intf = ((Object**)cls->interfaces->instance)[i];
                if(CLS_FIELD(intf,maxMethodIndex) > maxIndex) maxIndex = CLS_FIELD(intf,maxMethodIndex);
            }
            if(maxIndex + 1 >= cls->iTableSize) {
                cls->itable = realloc(cls->itable, sizeof(Object*) * (maxIndex+1));
                cls->iTableSize = maxIndex+1;
            }
            for(int i=0; i<cls->interfaces->length; i++) {
                Object *intf = ((Object**)cls->interfaces->instance)[i];
                Object *imethods = CLS_FIELD(intf, methods);
                for(int k=0; k<imethods->length; k++) {
                    Object *om = ARRAY_DATA_O(imethods)[k];
                    MethodFields *m = om->instance;
                    Object *override = find_method(clso, m->name, m->signature, 1);
                    if(override) {
                        MethodFields *omm = override->instance;
                        if(!IS_ABSTRACT(omm)) cls->itable[m->iTableIndex] = override;
                    }
                }
            }
        }
        
        if(!IS_INTERFACE(cls)) {
            //Setup Virtual Table
            if(cls->superClass) {
                cls->vtable = realloc(cls->vtable, sizeof(Object*) * CLS_FIELD(cls->superClass,vTableSize));
                memcpy(cls->vtable, CLS_FIELD(cls->superClass,vtable), sizeof(Object*) * CLS_FIELD(cls->superClass,vTableSize));
                cls->vTableSize = CLS_FIELD(cls->superClass,vTableSize);
            }
            if(cls->methods) {
                for(int i=0; i<cls->methods->length; i++) {
                    Object *om = ((Object**)cls->methods->instance)[i];
                    MethodFields *m = om->instance;
                    if(!IS_STATIC(m) && ARRAY_DATA_C(((StringFields*)m->name->instance)->chars)[0]!='<') {
                        Object *override = find_override_method(cls->superClass, om);
                        if(override) {
                            MethodFields *omm = override->instance;
                            m->vTableIndex = omm->vTableIndex;
                            //printf("----- %s override ",string2c(cls->name));
                            //printf(":%s",string2c(m->name));printf(":%s @%d\n",string2c(m->signature), m->vTableIndex);

                        } else {
                            m->vTableIndex = vm->vtable_counter++;
                        }
                        if(m->vTableIndex + 1 >= cls->vTableSize) {
                            cls->vTableSize = m->vTableIndex + 1;
                            cls->vtable = (Object**)realloc(cls->vtable, sizeof(Object*) * cls->vTableSize);
                        }
                        cls->vtable[m->vTableIndex] = om;
                    }
                }
            }
        }
        
        Object *clInit = find_method(clso, "<clinit>", "()V", 0);
        if(clInit) {
            ((JVM_CALL)(MTH_FIELD(clInit, entry)))(vm, clInit, NULL);
        }
    }
}

Object *resolve_class_by_signature(VM *vm, void *name, int isString) {
    char tmp[256];
    int len = 0;
    if(!isString) {
        len = (int)strlen((char*)name);
        memcpy(tmp, name, len);
    } else {
        len = ((StringFields*)((Object*)name)->instance)->length;
        memcpy(tmp, string2c((Object*)name), len);
    }
    tmp[len] = 0;
    int ptr = 0;
    if(tmp[ptr] == 'L' && tmp[len-1] == ';') {
        ptr++;
        tmp[len-1] = 0;
    }
    return resolve_class(vm, &tmp[ptr], 0);
}

Object *resolve_class(VM *vm, void *name, int isString) {
    //printf("--- resolving: %s\n", isString ? string2c((Object*)name) : (char*)name);
    Object *cls = find_class(vm, name, isString);
    if(cls) return cls;
    

    
    jint isArray = !isString ? ((char*)name)[0] == '[' : ARRAY_DATA_C(((StringFields*)((Object*)name)->instance)->chars)[0] == '[';
    if(isArray) {
        char tmp[256];
        int len = 0;
        if(!isString) {
            len = (int)strlen((char*)name);
            memcpy(tmp, name, len);
        } else {
            len = ((StringFields*)((Object*)name)->instance)->length;
            memcpy(tmp, string2c((Object*)name), len);
        }
        tmp[len] = 0;
        int ptr = 1;
        if(tmp[ptr] == 'L' && tmp[len-1] == ';') {
            ptr++;
            tmp[len-1] = 0;
        }
        Object *element = resolve_class(vm, &tmp[ptr], 0);
        if(!element) return NULL;
        
        if(ptr == 2) tmp[len-1] = ';';
        cls = alloc_class(vm, alloc_string_nogc(vm, tmp));
        CLS_FIELD(cls, name) = alloc_string_nogc(vm, tmp);
        CLS_FIELD(cls, superClass) = &java_lang_Object;
        CLS_FIELD(cls,elementClass) = element;
        //CLS_FIELD(cls, initialized) = 1;
        
        CLS_FIELD(cls,listNext) = vm->classes;
        vm->classes = cls;
        printf("loading class : %s %p\n",tmp, CLS_FIELD(cls, fields));
    } else
    cls = load_class(vm, name, isString);
    
    if(!cls) {
        throw_classnotfoundexception(vm, isString ? (Object*)name : alloc_string_nogc(vm, (char*)name));
        return NULL;
    }
    if(cls) {
        clInit(vm, cls);
    } else {
        printf("!!!!!!!! Class Not Found : %s\n", isString ? string2c((Object*)name) : (char*)name);
    }
    return cls;
}
Object *resolve_class_by_index(VM *vm, Object *cls, int index) {
    CPItem *cp = CLS_FIELD(cls, cp);
    return resolve_class(vm,cp[cp[index].index1].value.O,1);
}
Object *resolve_array_class_by_index(VM *vm, Object *cls, int index) {
    char tmp[152];
    Object *elemento = resolve_class_by_index(vm, cls, index);
    if(!elemento) return NULL;
    ClassFields *element = elemento->instance;
    if(element->primitiveType) {
        StringFields *str = element->name->instance;
        sprintf(tmp, "[%c", *((jchar*)str->chars->instance));
    } else if(element->elementClass) {
        sprintf(tmp, "[%s", string2c(element->name));
    } else {
        sprintf(tmp, "[L%s;", string2c(element->name));
    }
    
    //printf("--- resolve array %s -> %s\n", string2c(element->name), tmp);
    return resolve_class(vm, tmp, 0);
}

Object *resolve_method(VM *vm, void *clsName, void *name, void *signature, int isString) {
    Object *cls = resolve_class(vm, clsName, isString);
    if(vm->exception) return NULL;
    while(cls) {
        Object *m = find_method(cls, name, signature, isString);
        if(m) return m;
        cls = CLS_FIELD(cls,superClass);
    }
    
    if(isString) {
        printf("NoSuchMethod: %s", string2c((Object*)clsName));
        printf(":%s", string2c((Object*)name));
        printf(":%s\n", string2c((Object*)signature));
    } else {
        printf("NoSuchMethod: %s:%s:%s\n", clsName, name, signature);
    }
    return NULL;
}

Object *resolve_method_by_index(VM *vm,Object *cls, int index) {
    CPItem *cp = CLS_FIELD(cls,cp);
    Object *clsName = cp[cp[cp[index].index1].index1].value.O;
    Object *name = cp[cp[cp[index].index2].index1].value.O;
    Object *signature = cp[cp[cp[index].index2].index2].value.O;
    return resolve_method(vm, clsName, name, signature, 1);
}

Object *resolve_field(VM *vm, void *clsName, void *name, int isString) {
    Object *cls = resolve_class(vm, clsName, isString);
    if(vm->exception) return NULL;
    while(cls) {
        Object *f = find_field(cls, name, isString);
        if(f) return f;
        cls = CLS_FIELD(cls,superClass);
    }
    
    throw_nullpointerexception(vm);
    
    return NULL;
}
Object *resolve_field_by_index(VM *vm,Object *cls, int index) {
    CPItem *cp = CLS_FIELD(cls,cp);
    Object *clsName = cp[cp[cp[index].index1].index1].value.O;
    Object *name = cp[cp[cp[index].index2].index1].value.O;
    Object *signature = cp[cp[cp[index].index2].index2].value.O;
    /*printf("-- resolve field: %s", string2c(cls->name));
    printf(":%s", string2c(name));
    printf(":%s\n",string2c(signature));*/
    return resolve_field(vm, clsName, name, 1);
}
/*
ObjectPtr alloc_object(VM *vm,Class *cls) {
    int size = sizeof(Object) + cls->instanceSize;
    ObjectPtr o = (ObjectPtr)gc_alloc(size);
    memset(o, 0, size);
    o->cls = cls;
    
    o->gcVersion = vm->gcVersion;
    o->gcNext = vm->gcROOT;
    vm->gcROOT = o;
    
    return o;
}
ObjectPtr alloc_object_array(VM *vm, Class *cls, int length) {
    int size = sizeof(Array) + sizeof(Object*) * length;
    Array *arr = (Array*)gc_alloc(size);
    memset(arr, 0, size);
    arr->cls = cls;
    arr->length = length;
    
    arr->gcVersion = vm->gcVersion;
    arr->gcNext = vm->gcROOT;
    vm->gcROOT = (Object*)arr;
    
    return (ObjectPtr)arr;
}
ObjectPtr alloc_prim_array(VM *vm, Class *cls, int length) {
    int size = sizeof(Array) + cls->elementClass->instanceSize * length;
    Array *arr = (Array*)gc_alloc_atomic(size);
    memset(arr, 0, size);
    arr->cls = cls;
    arr->length = length;
    
    arr->gcVersion = vm->gcVersion;
    arr->gcNext = vm->gcROOT;
    vm->gcROOT = (Object*)arr;
    
    return (ObjectPtr)arr;
}
*/
void build_iof_table(Object *cls) {
    static int version = 0;
    
    version++;
    
    printf("iof: %s\n",string2c(CLS_FIELD(cls,name)));
    Object *table[1024]; //enough?
    int count = 0;
    Object *c = cls;
    while(c) {
        //if(version != cls->iofVersion) {
        if(cls != &java_lang_Object)
            table[count++] = cls;
        printf(" iof-child: %s\n", string2c(CLS_FIELD(c,name)));
        //}
        Object *interfaces = CLS_FIELD(c, interfaces);
        if(interfaces) {
            for(int i=0; i<interfaces->length; i++) {
                Object *ic = ARRAY_DATA_O(interfaces)[i];
                while(ic) {
                    //if(version != ic->iofVersion) {
                    if(ic != &java_lang_Object)
                        table[count++] = ic;
                    printf(" iof-child: %s\n", string2c(CLS_FIELD(ic,name)));
                    //}
                    ic = CLS_FIELD(ic,superClass);
                }
            }
        }
        c = CLS_FIELD(c,superClass);
    }
    
    ClassFields *clsf = cls->instance;
    clsf->iofTable = (Object**)malloc(sizeof(Object*) * count);
    memcpy(clsf->iofTable, table, sizeof(Object*) * count);
    clsf->iofCount = count;
}

jint is_class_son_of(Object *json, Object *jof) {
    if(!json || !jof) return 0;
    if(json == jof || jof == &java_lang_Object) return 1;
    ClassFields *son = json->instance;
    ClassFields *of = jof->instance;
    if(!son->iofTable) build_iof_table(json);
    for(int i=0; i<son->iofCount; i++)
        if(son->iofTable[i] == jof) return 1;
    return 0;
}

jint check_cast(VM *vm, Object *object, Object *cls) {
    if(!object) return 0;
    int r = is_class_son_of(object->cls, cls);
    //printf("check_cast: %s -> ",string2c(object->cls->name));
    //printf("%s = %d\n", string2c(cls->name), r);
    //if(r) return 1;
    return 1;
}

int get_line_number(MethodFields *method, int pc) {
    if(method->lineNumberTable) {
        for(int i=method->lineNumberTableSize - 1; i>=0; i--)
            if(method->lineNumberTable[i].pc <= pc)
                return method->lineNumberTable[i].line;
    }
    return -1;
}

void throw_exception(VM *vm, Object *exception) {
    int fp = vm->FP;
    vm->exception = exception;
    vm->exceptionFP = fp;
    if(exception) {
        ((ThrowableFields*)exception->instance)->FP = fp;
        ((ThrowableFields*)exception->instance)->cause = exception;
    }
    
    if(exception && fp > 0) {
        static Object *arrCls = NULL;
        static Object *cls = NULL;
        if(!arrCls) arrCls = resolve_class(vm, "[Ljava/lang/StackTraceElement;", 0);
        if(!cls) cls = resolve_class(vm, "java/lang/StackTraceElement", 0);
        Object *arr = alloc_object_array(vm, arrCls, fp);
        for(int i=1; i<=fp; i++) {
            Frame *f = &vm->frames[i];
            Object *seo = alloc_object(vm, cls);
            StackTraceElementFields *se = (StackTraceElementFields*)seo->instance;
            MethodFields *mth = f->method->instance;
            se->declaringClass = CLS_FIELD(mth->declaringClass,name);
            se->file_name = CLS_FIELD(mth->declaringClass,source_file);
            se->method_name = mth->name;
            se->line_number = f->line; //get_line_number(f->method->instance, f->pc);
            ((ObjectPtr*)arr->instance)[i-1] = (Object*)seo;
        }
        ((ThrowableFields*)exception->instance)->stack_trace = arr;
    }
}

void throw_nullpointerexception(VM *vm) {
    static Object *npe = NULL;
    static Object *mth = NULL;
    if(!npe) {
        npe = resolve_class(vm, "java/lang/NullPointerException", 0);
        if(vm->exception) return;
        
        mth = find_method(npe, "<init>", "()V", 0);
        if(vm->exception) return;
    }
    Object *exp = alloc_object(vm, npe);
    if(mth) {
        VAR args[1] = {{ .O = exp }};
        CALL_JVM_V(vm, mth, &args[0]);
    }
    throw_exception(vm, exp);
}

void throw_classnotfoundexception(VM *vm, Object *name) {
    static Object *npe = NULL;
    static Object *mth = NULL;
    if(!npe) {
        npe = resolve_class(vm, "java/lang/ClassNotFoundException", 0);
        if(vm->exception) return;
        
        mth = find_method(npe, "<init>", "(Ljava/lang/String;)V", 0);
        if(vm->exception) return;
    }
    Object *exp = alloc_object(vm, npe);
    if(mth) {
        VAR args[2] = {{ .O = exp }, { .O = name }};
        CALL_JVM_V(vm, mth, &args[0]);
    }
    
    printf("Class Not Found! : %s\n", string2c(name));
    throw_exception(vm, exp);
}

void throw_arrayboundsexception(VM *vm, int index, int length) {
    static Object *npe = NULL;
    static Object *mth = NULL;
    if(!npe) {
        npe = resolve_class(vm, "java/lang/ArrayIndexOutOfBoundsException", 0);
        if(vm->exception) return;
        
        mth = find_method(npe, "<init>", "(Ljava/lang/String;)V", 0);
        if(vm->exception) return;
    }
    Object *exp = alloc_object(vm, npe);
    if(mth) {
        //VAR args[2] = {{ .O = exp }, { .O = name }};
        //call_java_V(vm, mth, &args[0]);
    }
    throw_exception(vm, exp);
}

void throw_castexception(VM *vm, Object *son, Object *of) {
    static Object *npe = NULL;
    static Object *mth = NULL;
    if(!npe) {
        npe = resolve_class(vm, "java/lang/ArrayClassCastException", 0);
        if(vm->exception) return;
        
        mth = find_method(npe, "<init>", "(Ljava/lang/String;)V", 0);
        if(vm->exception) return;
    }
    Object *exp = alloc_object(vm, npe);
    if(mth) {
        //VAR args[2] = {{ .O = exp }, { .O = name }};
        //call_java_V(vm, mth, &args[0]);
    }
    throw_exception(vm, exp);
}

CatchInfo *find_catch_block(VM *vm, Object *omethod, Object *exception, int pc) {
    MethodFields *method = omethod->instance;
    for(int i=0; i<method->catchTableSize; i++) {
        CatchInfo *c = &method->catchTable[i];
        if(pc >= c->start && pc < c->end) {
            if(c->type != 0) {
                Object *caughtClass = resolve_class_by_index(vm, method->declaringClass, c->type);
                if(!caughtClass) {
                    vm->exception = NULL;
                    continue;
                }
                
                if(!check_cast(vm, exception, caughtClass)) continue;
            }
            return c;
        }
    }
    return NULL;
}



jlong mil() {
    struct timeval now;
    gettimeofday(&now, NULL);
    return now.tv_sec * 1000000LL + now.tv_usec;
}

int val(double d, int v) { return (int)d+12+v; }
static int fibonacci(int n) {
    if (n == 0 || n == 1) {
        return n;
    } else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

int nat() {
    //return fibonacci(40);
    int r = 0;
    for(int k=0; k<1000000; k++) r += k;//val(1.4565,k);
    return r;
}
extern void *gc_alloc(VM*, int);
void vm_test() {
    
    VM *vm = malloc(sizeof(VM));
    memset(vm, 0, sizeof(VM));
    alloc_init(vm);

    memset(&java_lang_Object, 0, sizeof(Object));

    memset(&java_lang_String, 0, sizeof(Object));
    java_lang_String.instance = malloc(sizeof(ClassFields));
    memset(java_lang_String.instance, 0, sizeof(ClassFields));
    CLS_FIELD(&java_lang_String, instanceSize) = sizeof(StringFields);
    //CLS_FIELD(&java_lang_String, listNext) = vm->classes;
    //vm->classes = &java_lang_String;
    
    memset(&java_lang_Class, 0, sizeof(Object));
    java_lang_Class.instance = malloc(sizeof(ClassFields));
    memset(java_lang_Class.instance, 0, sizeof(ClassFields));
    CLS_FIELD(&java_lang_Class, instanceSize) = sizeof(ClassFields);
    //CLS_FIELD(&java_lang_Class, listNext) = vm->classes;
    //vm->classes = &java_lang_Class;

    memset(&java_lang_reflect_Method, 0, sizeof(Object));
    java_lang_reflect_Method.instance = malloc(sizeof(ClassFields));
    memset(java_lang_reflect_Method.instance, 0, sizeof(ClassFields));
    CLS_FIELD(&java_lang_reflect_Method, instanceSize) = sizeof(MethodFields);

    memset(&java_lang_reflect_Field, 0, sizeof(Object));
    java_lang_reflect_Field.instance = malloc(sizeof(ClassFields));
    memset(java_lang_reflect_Field.instance, 0, sizeof(ClassFields));
    CLS_FIELD(&java_lang_reflect_Field, instanceSize) = sizeof(FieldFields);

    memset(&java_lang_reflect_Method1D, 0, sizeof(Object));
    java_lang_reflect_Method1D.instance = malloc(sizeof(ClassFields));
    memset(java_lang_reflect_Method1D.instance, 0, sizeof(ClassFields));
    CLS_FIELD(&java_lang_reflect_Method1D, instanceSize) = sizeof(ClassFields);
    CLS_FIELD(&java_lang_reflect_Method1D, elementClass) = &java_lang_reflect_Method;
    
    //vm->stack = (VAR*)gc_alloc_global(vm, sizeof(VAR) * MAX_STACK);
    memset(&java_lang_C1D, 0, sizeof(Object));
    java_lang_C1D.cls = &java_lang_Class;
    java_lang_C1D.instance = malloc(sizeof(ClassFields));
    memset(java_lang_C1D.instance, 0, sizeof(ClassFields));
    ClassFields *c1d = java_lang_C1D.instance;
    c1d->elementClass = &java_lang_C;
    //c1d->name = alloc_string_c(vm,"[C");
    c1d->superClass = &java_lang_Object;
    c1d->initialized = 1;
    c1d->listNext = vm->classes;
    vm->classes = &java_lang_C1D;

    Object *prims[] = {&java_lang_C, &java_lang_B, &java_lang_Z, &java_lang_S, &java_lang_I, &java_lang_F, &java_lang_J, &java_lang_D,&java_lang_V};
    const char *primNames[] = {"C","B","Z","S","I","F","J","D","V"};
    
    for(int i=0; i<9; i++) {
        Object *po = prims[i];
        memset(po, 0, sizeof(Object));
        po->instance = malloc(sizeof(ClassFields));
        memset(po->instance, 0, sizeof(ClassFields));
        
        ClassFields *p = po->instance;
        po->cls = &java_lang_Class;
        p->superClass = &java_lang_Object;
        p->name = alloc_string_nogc(vm, (char*)primNames[i]);
        p->initialized = 1;
        p->primitiveType = i + 1;
        p->instanceSize = get_prim_size((char)primNames[i][0]);
        printf("prim: %s = %d\n", primNames[i], p->instanceSize);
        p->listNext = vm->classes;
        vm->classes = po;
    }
    c1d->name = alloc_string_nogc(vm,"[C");

    memset(&java_lang_Class1D, 0, sizeof(Object));
    java_lang_Class1D.cls = &java_lang_Class;
    java_lang_Class1D.instance = malloc(sizeof(ClassFields));
    memset(java_lang_Class1D.instance, 0, sizeof(ClassFields));
    c1d = java_lang_Class1D.instance;
    c1d->elementClass = &java_lang_Class;
    c1d->name = alloc_string_nogc(vm,"[Ljava/lang/Class;");
    c1d->superClass = &java_lang_Object;
    c1d->initialized = 1;
    c1d->listNext = vm->classes;
    vm->classes = &java_lang_Class1D;

    resolve_class(vm, "java/lang/Object", 0);
    resolve_class(vm, "java/lang/Class", 0);
    resolve_class(vm, "java/lang/String", 0);
    resolve_class(vm, "java/lang/reflect/Field", 0);
    resolve_class(vm, "java/lang/reflect/Method", 0);
    resolve_class(vm, "[Ljava/lang/reflect/Field;", 0);
    resolve_class(vm, "[Ljava/lang/reflect/Method;", 0);

    //Class *cls = resolve_class_c(vm, "com/digitoygames/compiler/Test");
    
    //Class *cls = parse_class(buffer, NULL);
    
    //resolve_class(vm, "com/digitoygames/compiler/Test", 0);
    Object *method =
    //resolve_method(vm, "com/digitoygames/compiler/Test", "main", "()I", 0);
    resolve_method(vm, "Main", "main", "()V", 0);
    if(!method) {
        printf("Method not found!!\n");
        return;
    }
    //cls->listNext = vm->classes;
    //vm->classes = cls;
    
    /*
    Frame frame = {
        .stack = (VAR*)malloc(sizeof(VAR)*16),
        .local = (VAR*)malloc(sizeof(VAR)*16),
        .sp = 0,
        .method = ((Method**)cls->methods->data)[2]
    };
    
    VM *vm = &_VM;
    vm->fp = 1;
    //vm->frames = &frame;
    */
    
    for(int i=0; i<10; i++) {
        jlong t;
        
        t = mil();
        ((JVM_CALL)((MethodFields*)method->instance)->entry)(vm, method, NULL);
        int r = vm->frames[vm->FP].retVal.I;
        if(vm->exception) print_stack_trace(vm);
        //int r = call_java_I(vm,method, NULL);
        //
        //int r = __call_vi(vm, ((Method**)cls->methods->data)[2]);
        t = mil() - t;
        printf("vm-direct-%d = %d in %f\n", i,r, t/1000000.0);

        t = mil();
        r = nat();
        t = mil() - t;
        printf("nat-test-%d = %d in %f\n", i,r, t/1000000.0);
    }

    /*
    vm_init();
    Class *cls = find_class("com/digitoygames/compiler/Test");
    if(!cls) printf("Can't find class!!");
    
    Object* o = malloc(sizeof(Object));
    o->cls = cls;
    
    CPItem item = {.index1 = 0, .index2 = 0, .value = {.O = NULL}};
    
    String *str = (String *)cls->cp[cls->nameIndex].value.O;
    int result = com_digitoygames_compiler_Test_test__I(o);
    printf("Result = %d\n", result);
    */
}
