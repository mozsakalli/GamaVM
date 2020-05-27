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

jint compare_string_string(String* str1, String* str2) {
    if(str1 == str2) return 1;
    if(str1->length != str2->length) return 0;
    jchar *ch1 = (jchar*)str1->chars->data + str1->start;
    jchar *ch2 = (jchar*)str2->chars->data + str2->start;
    int len = str1->length;
    for(int i=0; i<len; i++) if(ch1[i] != ch2[i]) return 0;
    return 1;
}

jint compare_string_cstring(String* str1, const char *str2) {
    int len = (int)strlen(str2);
    if(str1->length != len) return 0;
    jchar *ch1 = (jchar*)str1->chars->data + str1->start;
    for(int i=0; i<len; i++) if(ch1[i] != str2[i]) return 0;
    return 1;
}

jint compare_string(void *str1, void *str2, int isString) {
    return isString ? compare_string_string((String*)str1, (String*)str2) : compare_string_cstring((String*)str1, (const char *)str2);
}

String *str_intern(VM *vm, String *str) {
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
    
    return str;
}

char *string2c(String *str) {
    static char tmp[1024];
    int len = str->length;
    if(len > 1023) len = 1023;
    jchar *chars = (jchar *)str->chars->data;
    chars += str->start;
    for(int i=0; i<len; i++) tmp[i] = chars[i];
    tmp[len] = 0;
    return tmp;
}

void jstr_print(String *str) {
    char buf[2048];
    for(int i=0; i<str->length; i++)
        buf[i] = ((jchar*)str->chars->data)[str->start+i];
    buf[str->length] = 0;
    printf("%s", buf);
}

void jstr_println(String *str) {
    jstr_print(str);
    printf("\n");
}

Class
java_lang_Object, java_lang_B, java_lang_Z, java_lang_C, java_lang_S, java_lang_I, java_lang_F, java_lang_D, java_lang_J,
java_lang_V,java_lang_C1D,java_lang_Class, java_lang_String, java_lang_reflect_Field, java_lang_reflect_Method;

String *vm_find_string(VM *vm, jchar *utf, jint len) {
    StringPool *ptr = vm->strings;
    while(ptr) {
        if(ptr->str->length == len) {
            int equals = 1;
            jchar *chars = (jchar*)ptr->str->chars->data;
            for(int i=0; i<len; i++)
                if(chars[i] != utf[i]) {
                    equals = 0;
                    break;
                }
            if(equals) return ptr->str;
        }
        ptr = ptr->next;
    }
    return NULL;
}

void vm_add_string(VM *vm, String *str) {
    StringPool *ptr = (StringPool*)malloc(sizeof(StringPool));
    ptr->str = str;
    ptr->next = vm->strings;
    vm->strings = ptr;
}

String* parse_utf8(VM *vm, char *data, int length) {
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
    
    jchar* target = &buf[0];// (jchar*)str->chars->data;
    ptr = data;
    jlen = 0;
    while (ptr < end) {
        unsigned int c = *ptr++;
        if (c < 0x80) {
            target[jlen++] = c;
        } else if (c < 0xE0) {
            target[jlen++] = (((c & 0x3F) << 6) | ((*ptr++) & 0x7F));
        } else if (c < 0xF0) {
            unsigned int c2 = *ptr++;
            target[jlen++] = (char) (((c & 0x1F) << 12) | ((c2 & 0x7F) << 6) | ((*ptr++) & 0x7F));
        } else {
            unsigned int c2 = *ptr++;
            unsigned int c3 = *ptr++;
            target[jlen++] = ((c & 0x0F) << 18) | ((c2 & 0x7F) << 12) | ((c3 & 0x7F) << 6) | ((*ptr++ & 0x7F));
        }
    }
    
    String *str = vm_find_string(vm, buf, strlen);
    if(!str) {
        str = (String*)malloc(sizeof(String));
        str->cls = &java_lang_String;
        str->chars = (Array*)malloc(sizeof(Array) + strlen * sizeof(jchar));
        str->chars->cls = &java_lang_C1D;
        str->chars->length = str->length = strlen;
        str->start = 0;
        memcpy(str->chars->data, buf, strlen * sizeof(jchar));
        vm_add_string(vm, str);
    }
    return str;
}

void parse_setup_method_args(Method *method) {
    String *signature = method->signature;
    jchar *ch = (jchar*)signature->chars->data;
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
        case 1: //CONSTANT_Utf8
            {
                int len = READ_U2(data); data += 2;
                cp[i].value.O = (Object*)parse_utf8(vm, data, len);
                cp[i].type = 'S';
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
        }
    }
    return data;
}

#define CLS_NAME(cls) (String*)cls->cp[cls->cp[cls->nameIndex].index1].value.O
#define CLS_SUPERNAME(cls) (String*)cls->cp[cls->cp[cls->superIndex].index1].value.O
#define MTH_NAME(m) (String*)m->declaringClass->cp[m->nameIndex].value.O
#define MTH_SIGNATURE(m) (String*)m->declaringClass->cp[m->signatureIndex].value.O

/*
static Class
java_lang_Object, java_lang_B, java_lang_Z, java_lang_C, java_lang_S, java_lang_I, java_lang_F, java_lang_D, java_lang_J,
java_lang_V,java_lang_C1D,java_lang_Class, java_lang_String, java_lang_reflect_Field, java_lang_reflect_Method;
*/
Class *alloc_class(VM *vm, String *name) {
    Class *boot = NULL;
    if(compare_string_cstring(name, "java/lang/Object")) boot = &java_lang_Object;
    else if(compare_string_cstring(name, "java/lang/String")) boot = &java_lang_String;
    else if(compare_string_cstring(name, "java/lang/Class")) boot = &java_lang_Class;
    else if(compare_string_cstring(name, "java/lang/reflect/Field")) boot = &java_lang_reflect_Field;
    else if(compare_string_cstring(name, "java/lang/reflect/Method")) boot = &java_lang_reflect_Method;
    else if(compare_string_cstring(name, "B")) boot = &java_lang_B;
    else if(compare_string_cstring(name, "Z")) boot = &java_lang_Z;
    else if(compare_string_cstring(name, "C")) boot = &java_lang_C;
    else if(compare_string_cstring(name, "[C")) boot = &java_lang_C1D;
    else if(compare_string_cstring(name, "S")) boot = &java_lang_S;
    else if(compare_string_cstring(name, "I")) boot = &java_lang_I;
    else if(compare_string_cstring(name, "F")) boot = &java_lang_F;
    else if(compare_string_cstring(name, "D")) boot = &java_lang_D;
    else if(compare_string_cstring(name, "J")) boot = &java_lang_J;

    if(!boot) boot = (Class*)malloc(sizeof(Class));
    memset(boot, 0, sizeof(Class));
    return boot;
}

extern void vm_interpret_method(VM *vm, Method *method, VAR *args);
void* vm_resolve_native_method(VM *vm, Method *method) {
    NativeMethodInfo *ptr = &NATIVES[0];
    while (ptr && ptr->cls) {
        if(compare_string_cstring(method->declaringClass->name, ptr->cls) &&
           compare_string_cstring(method->name, ptr->name) &&
           compare_string_cstring(method->signature, ptr->sign)) {
            return ptr->handle;
        }
        ptr++;
    }
    return NULL;
}

void vm_invoke_native(VM *vm, Method *method, VAR *args) {
    void *handler = vm_resolve_native_method(vm, method);
    if(handler) {
        method->entry = handler;
        ((JVM_CALL)handler)(vm, method, args);
        return;
    }

    printf("!!! Native !!! %s", string2c(method->declaringClass->name));
    printf(":%s",string2c(method->name));
    printf(":%s\n",string2c(method->signature));
    throw_nullpointerexception(vm);
}
 
Class *parse_class(VM *vm,char *data, void **entries) {
    int magic = READ_U4(data); data += 4;
    //printf("%x\n",magic);
    if(magic != 0xCAFEBABE)
        return NULL;
    READ_U2(data); data += 2; //major
    READ_U2(data); data += 2; //minor
    
    CPItem *cp = NULL;
    data = parse_constant_pool(vm, data, &cp);
    
    jint accessFlags = READ_U2(data); data += 2;
    jint nameIndex = READ_U2(data); data += 2;
    jint superIndex = READ_U2(data); data += 2;
    String *clsName = (String*)cp[cp[nameIndex].index1].value.O;
    
    Class *cls = alloc_class(vm, clsName);
    cls->cls = &java_lang_Class;
    cls->cp = cp;

    cls->accessFlags = accessFlags;
    cls->nameIndex = nameIndex;
    cls->superIndex = superIndex;
    cls->name = CLS_NAME(cls);
    cls->superName = CLS_SUPERNAME(cls);
    
    int count = READ_U2(data); data += 2;
    if(count > 0) {
        cls->interfaceDefs = (jint*)malloc(sizeof(jint)*(count+1));
        for(int i=0; i<count; i++) {
            int index = READ_U2(data); data += 2;
            cls->interfaceDefs[i] = index;
        }
        cls->interfaceDefs[count] = -1;
    }
    
    //fields
    int len = READ_U2(data); data += 2;
    Array* arr = cls->fields = (Array*)malloc(sizeof(Array) + sizeof(Field*) * len);
    arr->length = len;
    //arr->length = READ_U2(data); data += 2;
    if(arr->length > 0) {
        //arr->data = malloc(sizeof(Field*) * arr->length);
        Field** fields = (Field**)arr->data;
        for(int i=0; i<arr->length; i++) {
            Field *f = fields[i] = (Field*)malloc(sizeof(Field));
            f->declaringClass = cls;
            f->accessFlags = READ_U2(data); data += 2;
            f->nameIndex = READ_U2(data); data += 2;
            f->signatureIndex = READ_U2(data); data += 2;
            f->name = MTH_NAME(f);
            f->signature = MTH_SIGNATURE(f);
            f->cls = &java_lang_reflect_Field;
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
    arr = cls->methods = (Array*)malloc(sizeof(Array) + sizeof(Method*) * len);
    arr->length = len;
    if(arr->length > 0) {
        //arr->data = malloc(sizeof(Method*) * arr->length);
        Method** methods = (Method**)arr->data;
        for(int i=0; i<arr->length; i++) {
            Method *m = methods[i] = (Method*)malloc(sizeof(Method));
            memset(m, 0, sizeof(Method));
            m->accessFlags = READ_U2(data); data += 2;
            m->nameIndex = READ_U2(data); data += 2;
            m->signatureIndex = READ_U2(data); data += 2;
            m->declaringClass = cls;
            m->name = MTH_NAME(m);
            m->signature = MTH_SIGNATURE(m);
            if(!IS_STATIC(m) && compare_string_cstring(m->name, "finalize")) cls->finalizer = m;
            parse_setup_method_args(m);
            m->entry = entries ? entries[i] : (IS_NATIVE(m) ? (void*)&vm_invoke_native : (void*)&vm_interpret_method);
            m->cls = &java_lang_reflect_Method;
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
                String *attrName = (String*)cls->cp[nameIndex].value.O;
                //printf("Attr: ");jstr_print(attrName);printf(" of %d\n",ac);
                if(compare_string_cstring(attrName, "Code")) {
                    m->maxStack = READ_U2(data); data += 2;
                    m->maxLocals = READ_U2(data); data += 2;
                    m->declaringClass = cls;
                    
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
                        String *attrName = (String*)cls->cp[tmp].value.O;
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
                                vi->name = (String*)cls->cp[tmp].value.O;
                                tmp = READ_U2(data); data += 2;
                                vi->signature = (String*)cls->cp[tmp].value.O;
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
            String *attrName = (String*)cls->cp[tmp].value.O;
            int len = READ_U4(data); data += 4;
            if(compare_string_cstring(attrName, "SourceFile")) {
                tmp = READ_U2(data); data += 2;
                cls->source_file = (String*)cls->cp[tmp].value.O;
            } else data += len;
        }
    }

    return cls;
}

//AOTClassData* AOTSLOTS[4] = {NULL, NULL, NULL, NULL};
extern AOTClassData AOT[];
AOTClassData *find_aot_class(void *name, int isString) {
    //for(int i=0; i<4; i++) {
        AOTClassData *aot = &AOT[0];
        while (aot && aot->name) {
            if(!isString) {
                if(!strcmp((const char *)name, aot->name)) return aot;
            } else {
                if(compare_string_string((String*)name, aot->name)) return aot;
            }
            aot++;
        }
    //}
    return NULL;
}
Class *find_class(VM *vm, void *name, int isString) {
    Class *cls = vm->classes;
    while (cls) {
        if(compare_string(cls->name, name, isString)) return cls;
        cls = cls->listNext;
    }
    return NULL;
}
Class *load_class(VM *vm, void *name, int isString) {
    printf("-- loading: %s\n", isString ? string2c((String*)name) : (char*)name);
    AOTClassData *aot = find_aot_class(name, isString);
    if(aot) {
        //AOT class found
        Class *cls = parse_class(vm, aot->data, aot->methods);
        cls->listNext = vm->classes;
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
        if(isString) str += sprintf(str,"%s", string2c((String*)name)); else str += sprintf(str, "%s", (char*)name);
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
            Class *cls = parse_class(vm, (char *)p, NULL);
            mz_free(p);
            free(jar);
            if(cls) {
                cls->listNext = vm->classes;
                vm->classes = cls;
                return cls;
            }
        }
    }
    return NULL;
}

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

Method *find_method(Class *cls, void *name, void *signature, int isString) {
    if(cls->methods) {
        Method **methods = (Method**)cls->methods->data;
        for(int i=0; i<cls->methods->length; i++) {
            Method *m = methods[i];
            if(compare_string(m->name, name, isString) && compare_string(m->signature, signature, isString))
                return m;
        }
    }
    return NULL;
}
Field *find_field(Class *cls, void *name, int isString) {
    Field **fields = (Field**)cls->fields->data;
    for(int i=0; i<cls->fields->length; i++) {
        Field *f = fields[i];
        if(compare_string(f->name, name, isString))
            return f;
    }
    return NULL;
}

jint PRIMSIZE[] = {sizeof(jbyte),sizeof(jbool),sizeof(jchar),sizeof(jshort),sizeof(jint),sizeof(jfloat),sizeof(jlong),sizeof(jdouble)};
jint get_signature_size(String *signature) {
    jint chr = ((jchar*)signature->chars->data)[0];
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

Method *find_override_method(Class *cls, Method *method) {
    while(cls) {
        Method *found = find_method(cls, method->name, method->signature, 1);
        if(found) return found;
        cls = cls->superClass;
    }
    return NULL;
}

extern void *gc_alloc_global(VM *vm, int size);

void clInit(VM *vm, Class *cls) {
    if(!cls->initialized) {
        cls->initialized = 1;
        
        //Setup Fields
        cls->instanceSize = 0;
        int parentSize = 0;
        if(cls->superClass) {
            clInit(vm, cls->superClass);
            parentSize = cls->instanceSize = cls->superClass->instanceSize;
        }
        if(cls->interfaces) {
            for(int i=0; i<cls->interfaces->length; i++)
                clInit(vm, ((Class**)cls->interfaces->data)[i]);
        }
        
        int globalSize = 0;
        if(cls->fields) {
            Field** fields = (Field**)cls->fields->data;
            for(int i=0; i<cls->fields->length; i++) {
                Field *f = fields[i];
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
            cls->globals = gc_alloc_global(vm, globalSize); //malloc(globalSize);
            memset(cls->globals, 0, globalSize);
        }
        
        if(cls->superClass) cls->maxMethodIndex = cls->superClass->maxMethodIndex;
        
        //Give methods an index
        if(cls->methods) {
            for(int i=0; i<cls->methods->length; i++) {
                Method *m = ((Method**)cls->methods->data)[i];
                if(IS_INTERFACE(cls)) {
                    m->iTableIndex = vm->itable_counter++;
                    if(cls->maxMethodIndex < m->iTableIndex) cls->maxMethodIndex = m->iTableIndex;
                }
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
            cls->itable = realloc(cls->itable, sizeof(Method*) * cls->superClass->iTableSize);
            memcpy(cls->itable, cls->superClass->itable, sizeof(Method*) * cls->superClass->iTableSize);
            cls->iTableSize = cls->superClass->iTableSize;
        }
        if(cls->interfaces) {
            int maxIndex = 0;
            for(int i=0; i<cls->interfaces->length; i++) {
                Class *intf = ((Class**)cls->interfaces->data)[i];
                if(intf->maxMethodIndex > maxIndex) maxIndex = intf->maxMethodIndex;
            }
            if(maxIndex + 1 >= cls->iTableSize) {
                cls->itable = realloc(cls->itable, sizeof(Method*) * (maxIndex+1));
                cls->iTableSize = maxIndex+1;
            }
            for(int i=0; i<cls->interfaces->length; i++) {
                Class *intf = ((Class**)cls->interfaces->data)[i];
                for(int k=0; k<intf->methods->length; k++) {
                    Method *m = ((Method**)intf->methods->data)[k];
                    Method *override = find_method(cls, m->name, m->signature, 1);
                    if(override && !IS_ABSTRACT(override)) {
                        cls->itable[m->iTableIndex] = override;
                    }
                }
            }
        }
        
        if(!IS_INTERFACE(cls)) {
            //Setup Virtual Table
            if(cls->superClass) {
                cls->vtable = realloc(cls->vtable, sizeof(Method*) * cls->superClass->vTableSize);
                memcpy(cls->vtable, cls->superClass->vtable, sizeof(Method*) * cls->superClass->vTableSize);
                cls->vTableSize = cls->superClass->vTableSize;
            }
            if(cls->methods) {
                for(int i=0; i<cls->methods->length; i++) {
                    Method *m = ((Method**)cls->methods->data)[i];
                    if(!IS_STATIC(m) && ((jchar*)m->name->chars->data)[0]!='<') {
                        Method *override = find_override_method(cls->superClass, m);
                        if(override) {
                            m->vTableIndex = override->vTableIndex;
                            //printf("----- %s override ",string2c(cls->name));
                            //printf(":%s",string2c(m->name));printf(":%s @%d\n",string2c(m->signature), m->vTableIndex);

                        } else {
                            m->vTableIndex = vm->vtable_counter++;
                        }
                        if(m->vTableIndex + 1 >= cls->vTableSize) {
                            cls->vTableSize = m->vTableIndex + 1;
                            cls->vtable = (Method**)realloc(cls->vtable, sizeof(Method*) * cls->vTableSize);
                        }
                        cls->vtable[m->vTableIndex] = m;
                    }
                }
            }
        }
        
        Method *clInit = find_method(cls, "<clinit>", "()V", 0);
        if(clInit) {
            call_java_V(vm, clInit, NULL);
        }
    }
}

Class *resolve_class_by_signature(VM *vm, void *name, int isString) {
    char tmp[256];
    int len = 0;
    if(!isString) {
        len = (int)strlen((char*)name);
        memcpy(tmp, name, len);
    } else {
        len = ((String*)name)->length;
        memcpy(tmp, string2c((String*)name), len);
    }
    tmp[len] = 0;
    int ptr = 0;
    if(tmp[ptr] == 'L' && tmp[len-1] == ';') {
        ptr++;
        tmp[len-1] = 0;
    }
    return resolve_class(vm, &tmp[ptr], 0);
}

Class *resolve_class(VM *vm, void *name, int isString) {
    //printf("--- resolving: %s\n", isString ? string2c((String*)name) : (char*)name);
    Class *cls = find_class(vm, name, isString);
    if(cls) return cls;
    

    jint isArray = !isString ? ((char*)name)[0] == '[' : ((jchar*)((String*)name)->chars->data)[0] == '[';
    if(isArray) {
        char tmp[256];
        int len = 0;
        if(!isString) {
            len = (int)strlen((char*)name);
            memcpy(tmp, name, len);
        } else {
            len = ((String*)name)->length;
            memcpy(tmp, string2c((String*)name), len);
        }
        tmp[len] = 0;
        int ptr = 1;
        if(tmp[ptr] == 'L' && tmp[len-1] == ';') {
            ptr++;
            tmp[len-1] = 0;
        }
        Class *element = resolve_class(vm, &tmp[ptr], 0);
        if(!element) return NULL;
        
        cls = (Class*)malloc(sizeof(Class));
        memset(cls, 0, sizeof(Class));
        cls->cls = &java_lang_Class;
        cls->elementClass = element;
        if(ptr == 2) tmp[len-1] = ';';
        cls->name = make_java_string(tmp);
        cls->superName = java_lang_Object.name;
        cls->listNext = vm->classes;
        vm->classes = cls;
        printf("loading class : %s\n",tmp);
    } else
    cls = load_class(vm, name, isString);
    
    if(!cls) {
        throw_classnotfoundexception(vm, name);
        return NULL;
    }
    if(cls) {
        if(cls->superName && !cls->superClass) {
            cls->superClass = resolve_class(vm, cls->superName, 1);
        }
        if(cls->interfaceDefs) {
            int *name = &cls->interfaceDefs[0];
            int count = 0;
            while(*name != -1) { count++; name++; }
            
            name = &cls->interfaceDefs[0];
            cls->interfaces = (Array*)malloc(sizeof(Array) + sizeof(Object*)*count);
            cls->interfaces->cls = resolve_class(vm, "[java/lang/Class", 0);
            cls->interfaces->length = count;
            //cls->interfaces->data = malloc(sizeof(Object*)*count);
            ObjectPtr *list = (ObjectPtr*)cls->interfaces->data;
            for(int i=0; i<count; i++) {
                list[i] = (Object*)resolve_class(vm, cls->cp[cls->cp[*name].index1].value.O, 1);
                name++;
            }
        }

        clInit(vm, cls);
    } else {
        printf("!!!!!!!! Class Not Found : %s\n", isString ? string2c((String*)name) : (char*)name);
    }
    return cls;
}
Class *resolve_class_by_index(VM *vm, Class *cls, int index) {
    return resolve_class(vm,cls->cp[cls->cp[index].index1].value.O,1);
}
Class *resolve_array_class_by_index(VM *vm, Class *cls, int index) {
    char tmp[152];
    Class *element = resolve_class_by_index(vm, cls, index);
    if(!element) return NULL;
    if(element->primitiveType)
        sprintf(tmp, "[%c", *((jchar*)element->name->chars->data));
    else if(element->elementClass) {
        sprintf(tmp, "[%s", string2c(element->name));
    } else {
        sprintf(tmp, "[L%s;", string2c(element->name));
    }
    
    //printf("--- resolve array %s -> %s\n", string2c(element->name), tmp);
    return resolve_class(vm, tmp, 0);
}

Method *resolve_method(VM *vm, void *clsName, void *name, void *signature, int isString) {
    Class *cls = resolve_class(vm, clsName, isString);
    if(*vm->exception) return NULL;
    while(cls) {
        Method *m = find_method(cls, name, signature, isString);
        if(m) return m;
        cls = cls->superClass;
    }
    
    if(isString) {
        printf("NoSuchMethod: %s", string2c((String*)clsName));
        printf(":%s", string2c((String*)name));
        printf(":%s\n", string2c((String*)signature));
    } else {
        printf("NoSuchMethod: %s:%s:%s\n", clsName, name, signature);
    }
    return NULL;
}

Method *resolve_method_by_index(VM *vm,Class *cls, int index) {
    CPItem *cp = cls->cp;
    String *clsName = (String*)cp[cp[cp[index].index1].index1].value.O;
    String *name = (String*)cp[cp[cp[index].index2].index1].value.O;
    String *signature = (String*)cp[cp[cp[index].index2].index2].value.O;
    return resolve_method(vm, clsName, name, signature, 1);
}

Field *resolve_field(VM *vm, void *clsName, void *name, int isString) {
    Class *cls = resolve_class(vm, clsName, isString);
    if(*vm->exception) return NULL;
    while(cls) {
        Field *f = find_field(cls, name, isString);
        if(f) {
            return f;
        }
        cls = cls->superClass;
    }
    return NULL;
}
Field *resolve_field_by_index(VM *vm,Class *cls, int index) {
    CPItem *cp = cls->cp;
    String *clsName = (String*)cp[cp[cp[index].index1].index1].value.O;
    String *name = (String*)cp[cp[cp[index].index2].index1].value.O;
    String *signature = (String*)cp[cp[cp[index].index2].index2].value.O;
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
void build_iof_table(Class *cls) {
    static int version = 0;
    
    version++;
    
    printf("iof: %s\n",string2c(cls->name));
    Class *table[1024]; //enough?
    int count = 0;
    Class *c = cls;
    while(c) {
        //if(version != cls->iofVersion) {
        if(cls != &java_lang_Object)
            table[count++] = cls;
        printf(" iof-child: %s\n", string2c(c->name));
        //}
        if(c->interfaces) {
            for(int i=0; i<c->interfaces->length; i++) {
                Class *ic = ((Class**)c->interfaces->data)[i];
                while(ic) {
                    //if(version != ic->iofVersion) {
                    if(ic != &java_lang_Object)
                        table[count++] = ic;
                    printf(" iof-child: %s\n", string2c(ic->name));
                    //}
                    ic = ic->superClass;
                }
            }
        }
        c = c->superClass;
    }
    
    cls->iofTable = (Class**)malloc(sizeof(Class*) * count);
    memcpy(cls->iofTable, table, sizeof(Class*) * count);
    cls->iofCount = count;
}

jint is_class_son_of(Class *son, Class *of) {
    if(!son || !of) return 0;
    if(son == of || of == &java_lang_Object) return 1;
    if(!son->iofTable) build_iof_table(son);
    for(int i=0; i<son->iofCount; i++)
        if(son->iofTable[i] == of) return 1;
    return 0;
}

jint check_cast(VM *vm, Object *object, Class *cls) {
    if(!object) return 0;
    int r = is_class_son_of(object->cls, cls);
    printf("check_cast: %s -> ",string2c(object->cls->name));
    printf("%s = %d\n", string2c(cls->name), r);
    //if(r) return 1;
    return 1;
}

int get_line_number(Method *method, int pc) {
    if(method->lineNumberTable) {
        for(int i=method->lineNumberTableSize - 1; i>=0; i--)
            if(method->lineNumberTable[i].pc <= pc)
                return method->lineNumberTable[i].line;
    }
    return -1;
}

void throw_exception(VM *vm, Object *exception) {
    int fp = vm->FP;
    *vm->exception = exception;
    vm->exceptionFP = fp;
    if(exception) {
        ((Throwable*)exception)->FP = fp;
        ((Throwable*)exception)->cause = exception;
    }
    
    if(exception && fp > 0) {
        static Class *arrCls = NULL;
        static Class *cls = NULL;
        if(!arrCls) arrCls = resolve_class(vm, "[Ljava/lang/StackTraceElement;", 0);
        if(!cls) cls = resolve_class(vm, "java/lang/StackTraceElement", 0);
        Array *arr = (Array*)alloc_object_array(vm, arrCls, fp);
        for(int i=1; i<=fp; i++) {
            Frame *f = &vm->frames[i];
            //printf("se = %d %d\n", sizeof(StackTraceElement), sizeof(Object)+cls->instanceSize);
            StackTraceElement *se = (StackTraceElement*)alloc_object(vm, cls);
            se->declaringClass = f->method->declaringClass->name;
            se->file_name = f->method->declaringClass->source_file;
            se->method_name = f->method->name;
            se->line_number = get_line_number(f->method, f->pc);
            ((ObjectPtr*)arr->data)[i-1] = (Object*)se;
        }
        ((Throwable*)exception)->stack_trace = arr;
    }
    
    if(exception) printf("%s\n", string2c(exception->cls->name));
    print_stack_trace(vm);
}

void throw_nullpointerexception(VM *vm) {
    static Class *npe = NULL;
    static Method *mth = NULL;
    if(!npe) {
        npe = resolve_class(vm, "java/lang/NullPointerException", 0);
        if(*vm->exception) return;
        
        mth = find_method(npe, "<init>", "()V", 0);
        if(*vm->exception) return;
    }
    Object *exp = alloc_object(vm, npe);
    if(mth) {
        VAR args[1] = {{ .O = exp }};
        call_java_V(vm, mth, &args[0]);
    }
    throw_exception(vm, exp);
}

void throw_classnotfoundexception(VM *vm, Object *name) {
    static Class *npe = NULL;
    static Method *mth = NULL;
    if(!npe) {
        npe = resolve_class(vm, "java/lang/ClassNotFoundException", 0);
        if(*vm->exception) return;
        
        mth = find_method(npe, "<init>", "(Ljava/lang/String;)V", 0);
        if(*vm->exception) return;
    }
    Object *exp = alloc_object(vm, npe);
    if(mth) {
        VAR args[2] = {{ .O = exp }, { .O = name }};
        call_java_V(vm, mth, &args[0]);
    }
    throw_exception(vm, exp);
}

void throw_arrayboundsexception(VM *vm, int index, int length) {
    static Class *npe = NULL;
    static Method *mth = NULL;
    if(!npe) {
        npe = resolve_class(vm, "java/lang/ArrayIndexOutOfBoundsException", 0);
        if(*vm->exception) return;
        
        mth = find_method(npe, "<init>", "(Ljava/lang/String;)V", 0);
        if(*vm->exception) return;
    }
    Object *exp = alloc_object(vm, npe);
    if(mth) {
        //VAR args[2] = {{ .O = exp }, { .O = name }};
        //call_java_V(vm, mth, &args[0]);
    }
    throw_exception(vm, exp);
}

void throw_castexception(VM *vm, Class *son, Class *of) {
    static Class *npe = NULL;
    static Method *mth = NULL;
    if(!npe) {
        npe = resolve_class(vm, "java/lang/ArrayClassCastException", 0);
        if(*vm->exception) return;
        
        mth = find_method(npe, "<init>", "(Ljava/lang/String;)V", 0);
        if(*vm->exception) return;
    }
    Object *exp = alloc_object(vm, npe);
    if(mth) {
        //VAR args[2] = {{ .O = exp }, { .O = name }};
        //call_java_V(vm, mth, &args[0]);
    }
    throw_exception(vm, exp);
}

CatchInfo *find_catch_block(VM *vm, Method *method, Object *exception, int pc) {
    for(int i=0; i<method->catchTableSize; i++) {
        CatchInfo *c = &method->catchTable[i];
        if(pc >= c->start && pc < c->end) {
            if(c->type != 0) {
                Class *caughtClass = resolve_class_by_index(vm, method->declaringClass, c->type);
                if(!caughtClass) {
                    *vm->exception = NULL;
                    continue;
                }
                
                if(!check_cast(vm, exception, caughtClass)) continue;
            }
            return c;
        }
    }
    return NULL;
}


/*
#define DEF_ALLOC_ARRAY(t,n,j) \
ObjectPtr alloc_array_##t(VM *vm, int length) { \
    static Class *cls = NULL; \
    if(!cls) cls = resolve_class(vm, n, 0); \
    Array *array = (Array*)malloc(sizeof(Array) + sizeof(j) * length); \
    array->cls = cls; \
    array->length = length; \
    memset(array->data, 0, sizeof(j)*length); \
    return (ObjectPtr)array; \
}

DEF_ALLOC_ARRAY(Z, "[Z", jbool);
DEF_ALLOC_ARRAY(B, "[B", jbyte);
DEF_ALLOC_ARRAY(C, "[C", jchar);

/*
ObjectPtr alloc_array_B(VM *vm, int length) {
    static Class *cls = NULL;
    if(!cls) cls = resolve_class(vm, "[B", 0);
    Array *array = (Array*)malloc(sizeof(Array));
    array->cls = cls;
    array->length = length;
    array->data = malloc(sizeof(jbyte) * length);
    memset(array->data, 0, sizeof(jbyte)*length);
    return (ObjectPtr)array;
}
*/
jlong mil() {
    struct timeval now;
    gettimeofday(&now, NULL);
    return now.tv_sec * 1000000LL + now.tv_usec;
}

extern int __call_vi(VM *vm, Method *method);

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
    gc_init(vm);
    
    vm->exception = gc_alloc_global(vm, sizeof(Object*));
    memset(vm->exception, 0, sizeof(Object*));
    
    //vm->stack = (VAR*)gc_alloc_global(vm, sizeof(VAR) * MAX_STACK);
    
    Class *prims[] = {&java_lang_B, &java_lang_Z, &java_lang_C, &java_lang_S, &java_lang_I, &java_lang_F, &java_lang_J, &java_lang_D,&java_lang_V};
    const char *primNames[] = {"B","Z","C","S","I","F","J","D","V"};
    const int primSizes[] = {sizeof(jbyte),sizeof(jbool),sizeof(jchar),sizeof(jshort),sizeof(jint),sizeof(jfloat),sizeof(jlong),sizeof(jdouble),0};
    
    for(int i=0; i<9; i++) {
        Class *p = prims[i];
        memset(p, 0, sizeof(Class));
        p->cls = &java_lang_Class;
        p->superClass = &java_lang_Object;
        p->name = make_java_string(primNames[i]);
        p->listNext = vm->classes;
        p->initialized = 1;
        p->primitiveType = i + 1;
        p->instanceSize = primSizes[i];
        vm->classes = p;
    }
    memset(&java_lang_C1D, 0, sizeof(Class));
    java_lang_C1D.cls = &java_lang_Class;
    java_lang_C1D.elementClass = &java_lang_C;
    java_lang_C1D.name = make_java_string("[C");
    java_lang_C1D.superClass = &java_lang_Object;
    java_lang_C1D.initialized = 1;
    
    resolve_class(vm, "java/lang/Object", 0);
    resolve_class(vm, "java/lang/Class", 0);
    resolve_class(vm, "java/lang/String", 0);
    resolve_class(vm, "java/lang/reflect/Field", 0);
    resolve_class(vm, "java/lang/reflect/Method", 0);
    
    //Class *cls = resolve_class_c(vm, "com/digitoygames/compiler/Test");
    
    //Class *cls = parse_class(buffer, NULL);
    
    //resolve_class(vm, "com/digitoygames/compiler/Test", 0);
    Method *method =
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
        int r = call_java_I(vm,method, NULL);
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
