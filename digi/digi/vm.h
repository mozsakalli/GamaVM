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

typedef signed char jbyte;
typedef unsigned char jbool;
typedef unsigned short jchar;
typedef short jshort;
typedef unsigned short jushort;
typedef int jint;
typedef float jfloat;
typedef long long jlong;
typedef double jdouble;

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

inline static int compare_chars(jchar *c1, jchar *c2, int len) {
    for(int i=0; i<len; i++)
        if(c1[i] != c2[i]) return 0;
    return 1;
}


typedef union _Short2Char {
    union {
        jshort s;
        jushort us;
    };
    struct {
        jbyte c0;
        jbyte c1;
    };
} Short2Char;

typedef union _Int2Float {
    jint i;
    jfloat f;
    struct {
        jbyte c0;
        jbyte c1;
        jbyte c2;
        jbyte c3;
    };
} Int2Float;

typedef union _Long2Double {
    jdouble d;
    union {
        jlong l;
        struct {
            jint i0;
            jint i1;
        } i2l;
    };
    struct {
        jbyte c0;
        jbyte c1;
        jbyte c2;
        jbyte c3;
        jbyte c4;
        jbyte c5;
        jbyte c6;
        jbyte c7;
    };
} Long2Double;

typedef struct __attribute__ ((packed)) Object {
    struct Object* cls;
    void *instance;
    int length;
    struct {
        char free       : 1;
        char atomic     : 1;
        char version    : 6;
    } gc;
} Object;

typedef union VAR {
    jint I;
    jfloat F;
    jlong J;
    jdouble D;
    Object *O;
} VAR;

typedef struct __attribute__ ((packed)) StackTraceElement {
    Object *declaringClass;
    Object *methodName;
    Object *fileName;
    jint lineNumber;
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
    jint flags;
    jint offset;
    VAR *constantValue;
} Field;

typedef struct LocalVarInfo {
    jint start;
    jint length;
    Object *name;
    Object *signature;
    jint index;
} LocalVarInfo;

typedef struct LineNumberInfo {
    jint pc;
    jint line;
    jint breakpoint;
} LineNumberInfo;

typedef struct CatchInfo {
    jint start;
    jint end;
    jint pc;
    jint type;
    void *label;
} CatchInfo;

#define MTH(o,f) ((Method*)o->instance)->f
typedef struct __attribute__ ((packed)) Method {
    Object *name;
    Object *signature;
    Object *declaringClass;
    jint flags;
    jint *argMap;
    jint argCount;
    jint maxStack;
    jint maxLocals;
    jint codeSize;
    void *code;
    jint lineNumberTableSize;
    LineNumberInfo *lineNumberTable;
    jint catchTableSize;
    CatchInfo *catchTable;
    jint localVarTableSize;
    LocalVarInfo *localVarTable;
    jint iTableIndex;
    jint vTableIndex;
    void *entry;
    void *compiled;
    jint breakpoint;
} Method;

typedef struct CPItem {
    VAR value;
    jint index1;
    jint index2;
    jint type;
} CPItem;

#define CLS(o,f) ((Class*)o->instance)->f
#define CLS_PRIM(o) CLS(o,primitiveSize)
typedef struct __attribute__ ((packed)) Class {
    Object *name;
    Object *superClass;
    Object *interfaces;
    Object *elementClass;
    jint flags;
    Object *next;
    Object *fields;
    Object *methods;
    Object *sourceFile;
    void *global;
    jint instanceSize;
    jint primitiveSize;
    Object *arrayClass;
    CPItem *cp;
    jint linked;
    Object *finalizer;
    jint instanceOffsetCount;
    jint *instanceOffsets;  //for fast marking
    jint maxMethodIndex;
    jint vTableSize;
    Object **vtable;
    
    jint iTableSize;
    Object **itable;
    
    jint allParentCount;
    Object **allParents;
    struct VM *vm;
} Class;

typedef Class VMClass;

#define STR(o,f) ((String*)o->instance)->f
#define STRLEN(o) (STR(o,length))
#define STRCHARS(o) ((jchar*)((jchar*)(STR(o,chars)->instance) + STR(o,offset)))
typedef struct __attribute__ ((packed)) String {
    Object *chars;
    jint offset;
    jint length;
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
    jint line;
    jint pc;
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
    Object *classes, *strings;
    Object *jlObject, *jlClass, *jlMethod, *jlField, *jlString, *jlSTE;
    Object *primClasses[9];
    Object *exception;
    Frame frames[MAX_FRAMES];
    VAR stack[MAX_STACK];
    int FP,SP;
    int iTableCounter;
    int vTableCounter;
    Object *mainMethod;
    
    int gcVersion, gcStep;
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
extern Object *alloc_string_java(VM *vm, jchar *chars, int len, int atomic);
extern Object *alloc_string_utf8(VM *vm, char *chars, int datalen, int atomic);
extern void gc_step(VM *vm);
extern void gc_pause();
extern void gc_resume();
extern void gc_protect(VM *vm, Object *o);
extern void gc_unprotect(VM *vm,Object *o);

/// CLASS
extern Object *get_arrayclass_of(VM *vm, Object *cls);
extern Object *resolve_class(VM *vm, jchar *name, jint len, int link, Object *target);
extern Object *resolve_class_by_index(VM *vm, Object *cls, int index);
extern Object *find_class(VM *vm, jchar *name, jint len);
extern Object *find_class_method(VM *vm, Object *cls, jchar *name, jint nlen, jchar *sign, int slen);
extern Object *find_method(VM *vm, Object *cls, jchar *name, jint nlen, jchar *sign, int slen);
extern Object *resolve_method(VM *vm, jchar *clsName, int clslen, jchar *name, int nlen, jchar *signature, int slen);
extern Object *resolve_method_by_index(VM *vm,Object *cls, int index);
extern Object *find_class_field(VM *vm, Object *cls, jchar *name, jint nlen, jchar *sign, int slen);
extern Object *find_field(VM *vm, Object *cls, jchar *name, jint nlen, jchar *sign, int slen);
extern Object *resolve_field(VM *vm, jchar *clsName, int clslen, jchar *name, int namelen, jchar *sign, int slen);
extern Object *resolve_field_by_index(VM *vm,Object *cls, int index);
extern jint is_class_child_of(VM *vm, Object *json, Object *jof);
inline static jint check_cast(VM *vm, Object *object, Object *cls) {
    if(!object) return 1;
    return is_class_child_of(vm, object->cls, cls);
}

/// PARSE
extern int parse_class(VM *vm, char *data, Object *clsObject);
extern int get_line_number(Method *method, int pc);
/// UTF
extern int get_utf8_length(char *data, int length);
extern void decode_utf8(char *data, int length, jchar* buf);
extern char *jchar_to_ascii(jchar *chars, int len);
extern char *string_to_ascii(Object *str);
extern jchar *char_to_jchar(char *ch, int *len);

/// EXCEPTION
extern void throw_exception(VM *vm, Object *exception);
extern void throw_classnotfound(VM *vm, jchar *name, int len);
extern void throw_null(VM *vm);
extern void throw_arraybounds(VM *vm, int index, int length);
extern void throw_cast(VM *vm, Object *son, Object *of);
extern void throw_unsatisfiedlink(VM *vm, Object *method);

/// NATIVE
typedef struct NativeMethodInfo {
    const char *signature;
    void *method;
} NativeMethodInfo;
extern void *resolve_native_method(VM *vm, Object *method);

/// VM
extern VM *vm_init();
extern void vm_destroy();
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


extern void *read_class_file(jchar *name, int len);

#ifdef JDWP_ENABLED
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

#define FIELD_PTR(object,offset) ((object)->instance+offset)
#define FIELD_PTR_TYPE(object,offset,type) ((type*)FIELD_PTR(object,offset))
#define FIELD_PTR_B(object,offset) FIELD_PTR_TYPE(object,offset,jbyte)
#define FIELD_PTR_Z(object,offset) FIELD_PTR_TYPE(object,offset,jbool)
#define FIELD_PTR_C(object,offset) FIELD_PTR_TYPE(object,offset,jchar)
#define FIELD_PTR_S(object,offset) FIELD_PTR_TYPE(object,offset,jshort)
#define FIELD_PTR_I(object,offset) FIELD_PTR_TYPE(object,offset,jint)
#define FIELD_PTR_F(object,offset) FIELD_PTR_TYPE(object,offset,jfloat)
#define FIELD_PTR_J(object,offset) FIELD_PTR_TYPE(object,offset,jlong)
#define FIELD_PTR_D(object,offset) FIELD_PTR_TYPE(object,offset,jdouble)
#define FIELD_PTR_O(object,offset) FIELD_PTR_TYPE(object,offset,Object*)

#define ARRAY_DATA(object) (((Object*)object)->instance)
#define ARRAY_DATA_TYPE(object,type) ((type*)ARRAY_DATA(object))
#define ARRAY_DATA_B(object) ARRAY_DATA_TYPE(object,jbyte)
#define ARRAY_DATA_Z(object) ARRAY_DATA_TYPE(object,jbool)
#define ARRAY_DATA_C(object) ARRAY_DATA_TYPE(object,jchar)
#define ARRAY_DATA_S(object) ARRAY_DATA_TYPE(object,jshort)
#define ARRAY_DATA_I(object) ARRAY_DATA_TYPE(object,jint)
#define ARRAY_DATA_F(object) ARRAY_DATA_TYPE(object,jfloat)
#define ARRAY_DATA_J(object) ARRAY_DATA_TYPE(object,jlong)
#define ARRAY_DATA_D(object) ARRAY_DATA_TYPE(object,jdouble)
#define ARRAY_DATA_O(object) ARRAY_DATA_TYPE(object,Object*)

#define RETURN_J(v) vm->frames[vm->FP].ret.J = (jlong)(v);

#endif /* gamavm_h */
