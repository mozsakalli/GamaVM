//
//  jvm.c
//  Digiplay
//
//  Created by mustafa on 9.05.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#include "jvm.h"
#include "miniz.h"

extern void *__platform_read_file(const char* path, int *size);


VM _VM;

#define JVM_LINE(line)

typedef jint (*CALL_ODI_I)(Object*,jdouble,jint);
typedef void (*CALL)(VM*);

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

static Class
java_lang_Object, java_lang_B, java_lang_Z, java_lang_C, java_lang_S, java_lang_I, java_lang_F, java_lang_D, java_lang_J,
java_lang_V,java_lang_C1D,java_lang_Class, java_lang_String, java_lang_reflect_Field, java_lang_reflect_Method;

String* parse_utf8(char *data, int length) {
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
    String* str = (String*)malloc(sizeof(String));
    str->cls = &java_lang_String;
    str->chars = (Array*)malloc(sizeof(Array));
    str->chars->cls = &java_lang_C1D;
    str->chars->length = str->length = jlen;
    str->start = 0;
    jchar* target = str->chars->data = (jchar*)malloc(jlen * sizeof(jchar*));
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
    return str;
}

void parse_setup_method_args(Method *method) {
    String *signature = method->signature;
    jchar *ch = (jchar*)signature->chars->data;
    ch++; //(
    int count = 0;
    int jcount = 0;
    jint tmp[128]; //enough for paramters? :)
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

char *parse_constant_pool(char *data, CPItem** cpTarget) {
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
                cp[i].value.O = (Object*)parse_utf8(data, len);
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
            break;
            
        case 9: //CONSTANT_Fieldref
        case 10: //CONSTANT_Methodref
        case 11: //CONSTANT_InterfaceMethodref
        case 12: //CONSTANT_NameAndType
        case 18: // CONSTANT_InvokeDynamic
            cp[i].index1 = READ_U2(data); data += 2;
            cp[i].index2 = READ_U2(data); data += 2;
            break;
        }
    }
    return data;
}

#define CLS_NAME(cls) (String*)cls->cp[cls->cp[cls->nameIndex].index1].value.O
#define CLS_SUPERNAME(cls) (String*)cls->cp[cls->cp[cls->superIndex].index1].value.O
#define MTH_NAME(m) (String*)m->declaringClass->cp[m->nameIndex].value.O
#define MTH_SIGNATURE(m) (String*)m->declaringClass->cp[m->signatureIndex].value.O

Class *alloc_class(VM *vm, String *name) {
    Class *boot = NULL;
    if(compare_string_cstring(name, "java/lang/Object")) boot = &java_lang_Object;
    else if(compare_string_cstring(name, "java/lang/String")) boot = &java_lang_String;
    else if(compare_string_cstring(name, "java/lang/Class")) boot = &java_lang_Class;
    else if(compare_string_cstring(name, "java/lang/reflect/Field")) boot = &java_lang_reflect_Field;
    else if(compare_string_cstring(name, "java/lang/reflect/Method")) boot = &java_lang_reflect_Method;

    if(!boot) boot = (Class*)malloc(sizeof(Class));
    memset(boot, 0, sizeof(Class));
    return boot;
}

Class *parse_class(VM *vm,char *data, void **entries) {
    int magic = READ_U4(data); data += 4;
    //printf("%x\n",magic);
    if(magic != 0xCAFEBABE)
        return NULL;
    READ_U2(data); data += 2; //major
    READ_U2(data); data += 2; //minor
    
    CPItem *cp = NULL;
    data = parse_constant_pool(data, &cp);
    
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
        cls->interfaces = (CPItem**)malloc(sizeof(CPItem*)*(count+1));
        for(int i=0; i<count; i++) {
            int index = READ_U2(data); data += 2;
            cls->interfaces[i] = &cls->cp[index];
        }
        cls->interfaces[count] = NULL;
    }
    
    //fields
    Array* arr = cls->fields = (Array*)malloc(sizeof(Array));
    arr->length = READ_U2(data); data += 2;
    if(arr->length > 0) {
        arr->data = malloc(sizeof(Field*) * arr->length);
        Field** fields = (Field**)arr->data;
        for(int i=0; i<arr->length; i++) {
            Field *f = fields[i] = (Field*)malloc(sizeof(Field));
            f->declaringClass = cls;
            f->accessFlags = READ_U2(data); data += 2;
            f->nameIndex = READ_U2(data); data += 2;
            f->signatureIndex = READ_U2(data); data += 2;
            f->name = MTH_NAME(f);
            f->cls = &java_lang_reflect_Field;
            /*printf("Field: ");
            jstr_print(cls->cp[f->nameIndex].value.O);
            printf(" ");
            jstr_print(cls->cp[f->signatureIndex].value.O);
            printf("\n");
            */
            int ac = READ_U2(data); data += 2;
            for(int k=0; k<ac; k++) {
                READ_U2(data); data += 2; //name
                int len = READ_U4(data); data += 4;
                data += len;
            }
        }
    }
    
    //methods
    arr = cls->methods = (Array*)malloc(sizeof(Array));
    arr->length = READ_U2(data); data += 2;
    if(arr->length > 0) {
        arr->data = malloc(sizeof(Method*) * arr->length);
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
            parse_setup_method_args(m);
            m->entry = entries ? entries[i] : (IS_NATIVE(m) ? NULL : (void*)&interpreter_execute_direct);
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
                    
                    int exceptionCount = READ_U2(data); data += 2;
                    for(int j=0; j<exceptionCount; j++) {
                        READ_U2(data); data += 2; //start
                        READ_U2(data); data += 2; //end
                        READ_U2(data); data += 2; //handler
                        READ_U2(data); data += 2; //type
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
                        } else
                        data += len;
                    }
                } else {
                    data += attrlen;
                }
            }
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

Method *find_method(Class *cls, void *name, void *signature, int isString) {
    Method **methods = (Method**)cls->methods->data;
    for(int i=0; i<cls->methods->length; i++) {
        Method *m = methods[i];
        if(compare_string(m->name, name, isString) && compare_string(m->signature, signature, isString))
            return m;
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

void clInit(VM *vm, Class *cls) {
    if(!cls->initialized) {
        cls->initialized = 1;
        cls->instanceSize = 0;
        if(cls->superClass) {
            clInit(vm, cls->superClass);
            cls->instanceSize = cls->superClass->instanceSize;
        }
        
        Field** fields = (Field**)cls->fields->data;
        int globalCount = 0;
        for(int i=0; i<cls->fields->length; i++) {
            Field *f = fields[i];
            if(IS_STATIC(f)) {
                f->offset = globalCount++;
            } else {
                f->offset = cls->instanceSize++;
            }
        }
        if(globalCount > 0) cls->globals = (VAR*)malloc(sizeof(VAR) * globalCount);
        
        Method *clInit = find_method(cls, "<clinit>", "()V", 0);
        if(clInit) {
            call_java_V(vm, clInit, NULL);
        }
    }
}
Class *resolve_class(VM *vm, void *name, int isString) {
    Class *cls = find_class(vm, name, isString);
    if(cls) return cls;
    
    cls = load_class(vm, name, isString);
    if(cls) {
        if(cls->superName) {
            cls->superClass = resolve_class(vm, cls->superName, 1);
        }
        clInit(vm, cls);
    } else {
        printf("!!!!!!!! Class Not Found : %s\n", isString ? string2c((String*)name) : (char*)name);
    }
    return cls;
}

Method *resolve_method(VM *vm, void *clsName, void *name, void *signature, int isString) {
    Class *cls = resolve_class(vm, clsName, isString);
    if(cls) {
        return find_method(cls, name, signature, isString);
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
    if(cls) {
        return find_field(cls, name, isString);
    }
    return NULL;
}
Field *resolve_field_by_index(VM *vm,Class *cls, int index) {
    CPItem *cp = cls->cp;
    String *clsName = (String*)cp[cp[cp[index].index1].index1].value.O;
    String *name = (String*)cp[cp[cp[index].index2].index1].value.O;
    String *signature = (String*)cp[cp[cp[index].index2].index2].value.O;
    return resolve_field(vm, clsName, name, 1);
}

String* make_java_string(const char* chars) {
    String* str = malloc(sizeof(String));
    str->cls = &java_lang_String;
    str->chars = malloc(sizeof(Array));
    str->chars->cls = &java_lang_C1D;
    str->chars->length = (int)strlen(chars);
    str->chars->data = malloc(sizeof(jchar) * str->chars->length);
    jchar* target = str->chars->data;
    for(int i=0; i<str->chars->length; i++) target[i] = chars[i];
    str->start = 0;
    str->length = str->chars->length;
    
    return str;
}

ObjectPtr alloc_object(Class *cls) {
    int size = sizeof(Object) + sizeof(VAR) * cls->instanceSize;
    ObjectPtr o = (ObjectPtr)malloc(size);
    memset(o, 0, size);
    return o;
}

jlong mil() {
    struct timeval now;
    gettimeofday(&now, NULL);
    return now.tv_sec * 1000000LL + now.tv_usec;
}

extern int __call_vi(VM *vm, Method *method);

int val(double d, int v) { return (int)d+12+v; }
int nat() {
    int r = 0;
    for(int k=0; k<1000000; k++) r += val(1.4565,k);
    return r;
}
static VM* VMM = NULL;
VM *getVM() {
    VM *vm = VMM;
    if(!vm) {
        vm = malloc(sizeof(VM));
        memset(&_VM, 0, sizeof(VM));
        Class *prims[] = {&java_lang_B, &java_lang_Z, &java_lang_C, &java_lang_S, &java_lang_I,
                          &java_lang_F, &java_lang_J, &java_lang_D, &java_lang_V};
        const char *primNames[] = {"B", "Z", "C", "S", "I", "F", "J", "D", "V"};
        for (int i = 0; i < 9; i++) {
            Class *p = prims[i];
            memset(p, 0, sizeof(Class));
            p->cls = &java_lang_Class;
            p->superClass = &java_lang_Object;
            p->name = make_java_string(primNames[i]);
            p->listNext = vm->classes;
            vm->classes = p;
        }
        memset(&java_lang_C1D, 0, sizeof(Class));
        java_lang_C1D.cls = &java_lang_Class;
        java_lang_C1D.elementClass = &java_lang_C;
        java_lang_C1D.name = make_java_string("[C");

        vm->booting = 1;
        resolve_class(vm, "java/lang/Object", 0);
        resolve_class(vm, "java/lang/String", 0);
        resolve_class(vm, "java/lang/reflect/Field", 0);
        resolve_class(vm, "java/lang/reflect/Method", 0);
        vm->booting = 0;
        VMM = vm;
    }
    return vm;
}
int vm_test() {
    VM *vm = getVM();
    //Class *cls = resolve_class_c(vm, "com/digitoygames/compiler/Test");
    
    //Class *cls = parse_class(buffer, NULL);
    
    //resolve_class(vm, "com/digitoygames/compiler/Test", 0);
    Method *method =
    resolve_method(vm, "com/digitoygames/compiler/Test", "test", "()I", 0);
    //resolve_method(vm, "Main", "main", "()I", 0);
    if(!method) {
        printf("Method not found!!\n");
        return 0;
    }

    return ((JVM_CALL)(method->entry))(vm,method,NULL);
    //call_java_I(vm,method, NULL);
}


int vm_test2() {
    VM *vm = getVM();

    //Class *cls = resolve_class_c(vm, "com/digitoygames/compiler/Test");

    //Class *cls = parse_class(buffer, NULL);

    //resolve_class(vm, "com/digitoygames/compiler/Test", 0);
    Method *method =
            resolve_method(vm, "com/digitoygames/compiler/Test", "test", "()I", 0);
    //resolve_method(vm, "Main", "main", "()I", 0);
    if(!method) {
        printf("Method not found!!\n");
        return 0;
    }

    //for(int i=0; i<100; i++) ((JVM_CALL)(method->entry))(vm,method,NULL);
    return 0;
}