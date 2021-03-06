//
//  gamavm.h
//  digi
//
//  Created by mustafa on 7.06.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#ifndef gamavm_h
#define gamavm_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef signed char JBYTE;
typedef unsigned char JBOOL;
typedef unsigned short JCHAR;
typedef signed short JSHORT;
typedef unsigned short JUSHORT;
typedef signed int JINT;
typedef float JFLOAT;
typedef long long JLONG;
typedef double JDOUBLE;
typedef unsigned int JUINT;
typedef unsigned long long JULONG;

enum {
    ACC_PUBLIC = 0x0001,
    ACC_PRIVATE = 0x0002,
    ACC_PROTECTED = 0x0004,
    ACC_STATIC = 0x0008,
    ACC_FINAL = 0x0010,
    ACC_SYNCHRONIZED = 0x0020,
    ACC_VOLATILE = 0x0040,
    ACC_TRANSIENT = 0x0080,
    ACC_NATIVE = 0x0100,
    ACC_INTERFACE = 0x0200,
    ACC_ABSTRACT = 0x0400,
    ACC_STRICT = 0x0800,
};
#define IS_STATIC(m) (((m)&ACC_STATIC) != 0)
#define IS_NATIVE(m) (((m)&ACC_NATIVE) != 0)
#define IS_INTERFACE(m) (((m)&ACC_INTERFACE) != 0)
#define IS_ABSTRACT(m) (((m)&ACC_ABSTRACT) != 0)
#define IS_FINAL(m) (((m)&ACC_FINAL) != 0)

inline static void *vm_alloc(size_t size) {
    void *mem = malloc(size);
    memset(mem, 0, size);
    return mem;
}

inline static int compare_chars(JCHAR *c1, JCHAR *c2, int len) {
    for(int i=0; i<len; i++)
        if(c1[i] != c2[i]) return 0;
    return 1;
}


typedef union _Short2Char {
    union {
        JSHORT s;
        JUSHORT us;
    };
    struct {
        JBYTE c0;
        JBYTE c1;
    };
} Short2Char;

typedef union _Int2Float {
    JINT i;
    JFLOAT f;
    struct {
        JBYTE c0;
        JBYTE c1;
        JBYTE c2;
        JBYTE c3;
    };
} Int2Float;

typedef union _Long2Double {
    JDOUBLE d;
    union {
        JLONG l;
        struct {
            JINT i0;
            JINT i1;
        } i2l;
    };
    struct {
        JBYTE c0;
        JBYTE c1;
        JBYTE c2;
        JBYTE c3;
        JBYTE c4;
        JBYTE c5;
        JBYTE c6;
        JBYTE c7;
    };
} Long2Double;

typedef struct __attribute__ ((packed)) Object {
    struct Object* cls;
    void *instance;
    int length;
    struct {
        char free       : 1;
        char atomic     : 1;
        char isClass    : 1;
        char version    : 5;
    } gc;
} Object;

typedef union VAR {
    JINT I;
    JFLOAT F;
    JLONG J;
    JDOUBLE D;
    Object *O;
} VAR;

typedef struct __attribute__ ((packed)) StackTraceElement {
    Object *declaringClass;
    Object *methodName;
    Object *fileName;
    JINT lineNumber;
} StackTraceElement;

typedef struct __attribute__ ((packed)) Throwable {
    Object *stackTrace;
    Object *msg;
    Object *cause;
} Throwable;

#define FLD(o,f) ((Field*)o->instance)->f
typedef struct __attribute__ ((packed)) Field {
    Object *name;
    Object *signature;
    Object *declaringClass;
    JINT flags;
    void* offset;
    VAR *constantValue;
} Field;

typedef struct LocalVarInfo {
    JINT start;
    JINT length;
    Object *name;
    Object *signature;
    JINT index;
} LocalVarInfo;

typedef struct LineNumberInfo {
    JINT pc;
    JINT line;
    JINT breakpoint;
} LineNumberInfo;

typedef struct CatchInfo {
    JINT start;
    JINT end;
    JINT pc;
    JINT type;
    void *label;
} CatchInfo;

typedef struct MethodArg {
    int localIndex;
    int sign;
} MethodArg;

#define MTH(o,f) ((Method*)o->instance)->f
#define MTH_LOADER(method) CLS(MTH(method, declaringClass),clsLoader)
typedef struct __attribute__ ((packed)) Method {
    Object *name;
    Object *signature;
    Object *declaringClass;
    JINT flags;
    MethodArg *argMap;
    JINT argCount;
    JINT maxStack;
    JINT maxLocals;
    JINT codeSize;
    void *code;
    JINT lineNumberTableSize;
    LineNumberInfo *lineNumberTable;
    JINT catchTableSize;
    CatchInfo *catchTable;
    JINT localVarTableSize;
    LocalVarInfo *localVarTable;
    JINT iTableIndex;
    JINT vTableIndex;
    void *entry;
    void *compiled;
    JINT compiledSize;
    JINT breakpoint;
    int externalFlags;
    Object *externalName;
    void *externalData;
    int returnSign;
} Method;

typedef struct CPItem {
    VAR value;
    JINT index1;
    JINT index2;
    JINT type;
} CPItem;

typedef struct __attribute__ ((packed)) ClassLoader {
    Object *parent;
    Object *classes;
    Object *strings;
} ClassLoader;

#define CLS(o,f) ((VMClass*)o->instance)->f
#define CLS_PRIM(o) CLS(o,primitiveSize)
typedef struct __attribute__ ((packed)) Class {
    Object *name;
    Object *superClass;
    Object *interfaces;
    Object *elementClass;
    JINT flags;
    Object *next;
    Object *fields;
    Object *methods;
    Object *sourceFile;
    void *global;
    JINT instanceSize;
    JINT primitiveSize;
    Object *arrayClass;
    CPItem *cp;
    JINT linked;
    Object *finalizer;
    JINT instanceOffsetCount;
    JINT *instanceOffsets;  //for fast marking
    JINT maxMethodIndex;
    JINT vTableSize;
    Object **vtable;
    
    JINT iTableSize;
    Object **itable;
    
    JINT allParentCount;
    Object **allParents;
    Object *clsLoader;
    int externalFlags;
    Object *externalName;
    void *externalData;
    int isClassLoader;
} VMClass;

#define STR(o,f) ((String*)o->instance)->f
#define STRLEN(o) (STR(o,length))
#define STRCHARS(o) ((JCHAR*)((JCHAR*)(STR(o,chars)->instance) + STR(o,offset)))
typedef struct __attribute__ ((packed)) String {
    Object *chars;
    JINT offset;
    JINT length;
    JINT hashCode;
    Object *next;
} String;

#define HEAP_OBJECTS_PER_BLOCK    32768
typedef struct HeapBlock {
    Object objects[HEAP_OBJECTS_PER_BLOCK];
    struct HeapBlock *next;
    Object *free;
    int used;
} HeapBlock;

typedef struct Frame {
    Object *method;
    JINT line;
    JINT pc;
    VAR ret;
    VAR *SP;
} Frame;

#define MAX_FRAMES  2048
#define MAX_STACK  4096

#define PRIM_C  0
#define PRIM_B  1
#define PRIM_Z  2
#define PRIM_S  3
#define PRIM_I  4
#define PRIM_F  5
#define PRIM_J  6
#define PRIM_D  7
#define PRIM_V  8
typedef struct VM {
    HeapBlock *heap;
    //Object *classes, *strings;
    Object *sysClassLoader;
    Object *jlObject, *jlClass, *jlMethod, *jlField, *jlString, *jlSTE, *jlClassLoader;
    Object *primClasses[9];
    Object *exception;
    Frame frames[MAX_FRAMES];
    VAR stack[MAX_STACK];
    int FP,SP;
    int iTableCounter;
    int vTableCounter;
    Object *mainMethod;
    
    int gcVersion, gcStep, gcTick;
    void *gcPtr;
    int gcBlockPtr;
    struct {
        int R;
        int W;
        int S;
        int C;
        Object** Q;
    } markQueue;
    Object **gcRoots;
    int gcRootCount, gcRootCapacity;
    Object *sweepClasses, *sweepStrings;
} VM;

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*VM_CALL)(VM*,Object*,VAR*);
inline static void CALLVM_V(VM *vm, Object *method, VAR *args) {
    ((VM_CALL)((Method*)method->instance)->entry)(vm, method, args);
}
#define CALL_JVM_V(vm,method,args) ((JVM_CALL)((MethodFields*)method->instance)->entry)(vm, method, args)

/// ALLOC
extern Object *alloc_object(VM *vm, Object *cls, int atomic);
extern Object *alloc_class(VM *vm);
extern Object *alloc_array(VM *vm, Object *cls, int length, int atomic);
extern Object *alloc_string_ascii(VM *vm, char *chars, int atomic);
extern Object *alloc_string_java(VM *vm, JCHAR *chars, int len, int atomic);
extern Object *alloc_string_utf8(VM *vm, char *chars, int datalen, int atomic);
extern void gc_step(VM *vm);
extern void gc_pause();
extern void gc_resume();
extern void gc_protect(VM *vm, Object *o);
extern void gc_unprotect(VM *vm,Object *o);

/// CLASS
extern Object *get_arrayclass_of(VM *vm, Object *cls);
extern Object *resolve_class(VM *vm, Object *cloader, JCHAR *name, JINT len, int link, Object *target);
extern void link_class(VM *vm, Object *clsObject);
extern Object *resolve_class_by_index(VM *vm, Object *cls, int index);
extern Object *find_class(VM *vm, Object *cloader, JCHAR *name, JINT len);
extern Object *find_class_method(VM *vm, Object *cls, JCHAR *name, JINT nlen, JCHAR *sign, int slen);
extern Object *find_method(VM *vm, Object *cls, JCHAR *name, JINT nlen, JCHAR *sign, int slen);
extern Object *resolve_method(VM *vm, Object *cloader, JCHAR *clsName, int clslen, JCHAR *name, int nlen, JCHAR *signature, int slen);
extern Object *resolve_method_by_index(VM *vm,Object *cls, int index);
extern Object *find_class_field(VM *vm, Object *cls, JCHAR *name, JINT nlen, JCHAR *sign, int slen);
extern Object *find_field(VM *vm, Object *cls, JCHAR *name, JINT nlen, JCHAR *sign, int slen);
extern Object *resolve_field(VM *vm, Object *cloader, JCHAR *clsName, int clslen, JCHAR *name, int namelen, JCHAR *sign, int slen);
extern Object *resolve_field_by_index(VM *vm,Object *cls, int index);
extern JINT is_class_child_of(VM *vm, Object *json, Object *jof);
inline static JINT check_cast(VM *vm, Object *object, Object *cls) {
    if(!object) return 1;
    return is_class_child_of(vm, object->cls, cls);
}

/// PARSE
extern int parse_class(VM *vm, Object *cloader, char *data, Object *clsObject);
extern int get_line_number(Method *method, int pc);
/// UTF
extern int get_utf8_length(char *data, int length);
extern void decode_utf8(char *data, int length, JCHAR* buf);
extern int get_utf8_encode_length(JCHAR *chars, int srcLen);
extern void encode_utf8(JCHAR *chars, int srcLen, char *buf);
extern char *jchar_to_ascii(JCHAR *chars, int len);
extern char *string_to_ascii(Object *str);
extern JCHAR *char_to_jchar(char *ch, int *len);

/// EXCEPTION
extern void throw_exception(VM *vm, Object *exception);
extern void throw_classnotfound(VM *vm, JCHAR *name, int len);
extern void throw_null(VM *vm);
extern void throw_arraybounds(VM *vm, int index, int length);
extern void throw_cast(VM *vm, Object *son, Object *of);
extern void throw_unsatisfiedlink(VM *vm, Object *method);
extern void throw_nosuchmethod(VM *vm, JCHAR *clsName, int clsLen, JCHAR *name, int nameLen, JCHAR *sign, int signLen);
extern void throw_abstractmethod(VM *vm, JCHAR *clsName, int clsLen, JCHAR *name, int nameLen, JCHAR *sign, int signLen);

/// NATIVE
typedef struct NativeMethodInfo {
    const char *signature;
    void *method;
} NativeMethodInfo;
extern void *resolve_native_method(VM *vm, Object *method);

/// VM
extern VM *vm_init();
extern void vm_destroy(VM *vm);
extern void vm_main(VM *vm, char *className, char *methodName, char *signature);
extern void vm_interpret_exec(VM *vm, Object *omethod, VAR *args);
extern void vm_native_exec(VM *vm, Object *omethod, VAR *args);

extern void invoke_interface_v(VM* vm, Object *method, VAR *args);

inline static Object *alloc_array_B(VM *vm, int length, int atomic) {
    return alloc_array(vm, get_arrayclass_of(vm, vm->primClasses[PRIM_B]), length, atomic);
}
inline static Object *alloc_array_Z(VM *vm, int length, int atomic) {
    return alloc_array(vm, get_arrayclass_of(vm, vm->primClasses[PRIM_Z]), length, atomic);
}
inline static Object *alloc_array_C(VM *vm, int length, int atomic) {
    return alloc_array(vm, get_arrayclass_of(vm, vm->primClasses[PRIM_C]), length, atomic);
}
inline static Object *alloc_array_S(VM *vm, int length, int atomic) {
    return alloc_array(vm, get_arrayclass_of(vm, vm->primClasses[PRIM_S]), length, atomic);
}
inline static Object *alloc_array_I(VM *vm, int length, int atomic) {
    return alloc_array(vm, get_arrayclass_of(vm, vm->primClasses[PRIM_I]), length, atomic);
}
inline static Object *alloc_array_F(VM *vm, int length, int atomic) {
    return alloc_array(vm, get_arrayclass_of(vm, vm->primClasses[PRIM_F]), length, atomic);
}
inline static Object *alloc_array_J(VM *vm, int length, int atomic) {
    return alloc_array(vm, get_arrayclass_of(vm, vm->primClasses[PRIM_J]), length, atomic);
}
inline static Object *alloc_array_D(VM *vm, int length, int atomic) {
    return alloc_array(vm, get_arrayclass_of(vm, vm->primClasses[PRIM_D]), length, atomic);
}
inline static Object *alloc_array_O(VM *vm, Object *cls, int length, int atomic) {
    return alloc_array(vm, get_arrayclass_of(vm, cls), length, atomic);
}


extern void *read_class_file(JCHAR *name, int len);

#ifdef PLAYERMODE
    extern void jdwp_tick(VM *vm, Object *method, int pc, int line, int lineChanged);
    extern void jdwp_start(VM *vm, char *host, int port);
    extern int jdwp_send_classload_event(VM *vm, Object *cls);
#else
    #define jdwp_tick
    #define jdwp_start
    #define jdwp_send_classload_event
#endif

#ifdef __cplusplus
}
#endif

#define FIELD_PTR(object,offset) ((object)->instance+(int)(offset))
#define FIELD_PTR_TYPE(object,offset,type) ((type*)FIELD_PTR(object,offset))
#define FIELD_PTR_B(object,offset) FIELD_PTR_TYPE(object,offset,JBYTE)
#define FIELD_PTR_Z(object,offset) FIELD_PTR_TYPE(object,offset,JBOOL)
#define FIELD_PTR_C(object,offset) FIELD_PTR_TYPE(object,offset,JCHAR)
#define FIELD_PTR_S(object,offset) FIELD_PTR_TYPE(object,offset,JSHORT)
#define FIELD_PTR_I(object,offset) FIELD_PTR_TYPE(object,offset,JINT)
#define FIELD_PTR_F(object,offset) FIELD_PTR_TYPE(object,offset,JFLOAT)
#define FIELD_PTR_J(object,offset) FIELD_PTR_TYPE(object,offset,JLONG)
#define FIELD_PTR_D(object,offset) FIELD_PTR_TYPE(object,offset,JDOUBLE)
#define FIELD_PTR_O(object,offset) FIELD_PTR_TYPE(object,offset,Object*)

#define ARRAY_DATA(object) (((Object*)object)->instance)
#define ARRAY_DATA_TYPE(object,type) ((type*)ARRAY_DATA(object))
#define ARRAY_DATA_B(object) ARRAY_DATA_TYPE(object,JBYTE)
#define ARRAY_DATA_Z(object) ARRAY_DATA_TYPE(object,JBOOL)
#define ARRAY_DATA_C(object) ARRAY_DATA_TYPE(object,JCHAR)
#define ARRAY_DATA_S(object) ARRAY_DATA_TYPE(object,JSHORT)
#define ARRAY_DATA_I(object) ARRAY_DATA_TYPE(object,JINT)
#define ARRAY_DATA_F(object) ARRAY_DATA_TYPE(object,JFLOAT)
#define ARRAY_DATA_J(object) ARRAY_DATA_TYPE(object,JLONG)
#define ARRAY_DATA_D(object) ARRAY_DATA_TYPE(object,JDOUBLE)
#define ARRAY_DATA_O(object) ARRAY_DATA_TYPE(object,Object*)

#define RETURN_J(v) vm->frames[vm->FP].ret.J = (JLONG)(v);

#define AOTCLASS(var,name) \
if(!var) { \
	var = resolve_class(vm,STRCHARS(aot_strings[name]), STRLEN(aot_strings[name]), 1, NULL); \
}

#define AOTFIELD(var,cls,name,sign) \
if(!var) { \
	Object *field = resolve_field(vm, STRCHARS(aot_strings[cls]), STRLEN(aot_strings[cls]), \
	STRCHARS(aot_strings[name]), STRLEN(aot_strings[name]), \
	STRCHARS(aot_strings[sign]), STRLEN(aot_strings[sign])); \
	var = field->instance; \
	if(!var) goto __EXCEPTION; \
}

#define AOTVMETHOD(var,cls,name,sign,table) \
if(!var) { \
	Object *mth = resolve_method(vm, STRCHARS(aot_strings[cls]), STRLEN(aot_strings[cls]), \
	STRCHARS(aot_strings[name]), STRLEN(aot_strings[name]), \
	STRCHARS(aot_strings[sign]), STRLEN(aot_strings[sign])); \
	var = MTH(mth, table); \
	if(!var) goto __EXCEPTION; \
}

#define AOTMETHOD(var,cls,name,sign) \
if(!var) { \
	var = resolve_method(vm, STRCHARS(aot_strings[cls]), STRLEN(aot_strings[cls]), \
	STRCHARS(aot_strings[name]), STRLEN(aot_strings[name]), \
	STRCHARS(aot_strings[sign]), STRLEN(aot_strings[sign])); \
	if(!var) goto __EXCEPTION; \
}

#ifdef __ANDROID__
#include <android/log.h>
#define GLOG(...) __android_log_print(ANDROID_LOG_ERROR, "GamaVM", __VA_ARGS__)
#else
#define GLOG(...) printf( __VA_ARGS__)
#endif

#endif /* gamavm_h */
