//
//  jvm.h
//  Digiplay
//
//  Created by mustafa on 9.05.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#ifndef jvm_h
#define jvm_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include "opcodes.h"


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
#define IS_STATIC(m) ((m->accessFlags&ACC_STATIC) != 0)
#define IS_NATIVE(m) ((m->accessFlags&ACC_NATIVE) != 0)
#define IS_INTERFACE(m) ((m->accessFlags&ACC_INTERFACE) != 0)
#define IS_ABSTRACT(m) ((m->accessFlags&ACC_ABSTRACT) != 0)
#define IS_FINAL(m) ((m->accessFlags&ACC_FINAL) != 0)

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
    struct Object *cls;
    int length;
    void *instance;
    struct {
        int free   : 8;
        int atomic : 8;
        int version: 16;
    } gc;
    //int gc_version;
} Object;

typedef Object* ObjectPtr;

typedef struct __attribute__ ((packed)) StringFields {
    Object *chars;
    jint start;
    jint length;
    jint hashcode;
    void *__native;
} StringFields;

typedef union VAR {
    jint I;
    jfloat F;
    jlong J;
    jdouble D;
    Object *O;
} VAR;

typedef struct __attribute__ ((packed)) FieldFields {
    jint accessFlags;
    struct Object *declaringClass;
    Object *name;
    Object *signature;
    jint offset;
    struct Object *type;
} FieldFields;

typedef struct LocalVarInfo {
    jint start;
    jint length;
    Object *name;
    Object *signature;
    jint index;
} LocalVarInfo;

typedef struct LineNumberInfo {
    unsigned short pc;
    unsigned short line;
    unsigned short breakpoint;
} LineNumberInfo;

typedef struct CatchInfo {
    jint start;
    jint end;
    jint pc;
    jint type;
    void *label;
} CatchInfo;

typedef struct __attribute__ ((packed)) MethodFields {
    jint accessFlags;
    jint maxStack;
    jint maxLocals;
    struct Object *declaringClass;
    Object *name;
    Object *signature;
    Object *returnType;

    jint localVarTableSize;
    LocalVarInfo *localVarTable;
    jint argCount;
    jint *argMap;
    jint iTableIndex;
    jint vTableIndex;
    
    jint lineNumberTableSize;
    LineNumberInfo *lineNumberTable;
    jint catchTableSize;
    CatchInfo *catchTable;
    
    void *entry;
    
    //interpreter
    void *code;
    jint codeSize;
    void *compiled;
    
    jint breakpoint;
} MethodFields;

typedef struct CPItem {
    VAR value;
    jint index1;
    jint index2;
    jint type;
} CPItem;

#define CLS_FIELD(o,name) (((ClassFields*)((Object*)o)->instance)->name)
#define MTH_FIELD(o,name) (((MethodFields*)((Object*)o)->instance)->name)
#define FLD_FIELD(o,name) (((FieldFields*)((Object*)o)->instance)->name)

#define CLASS_HAS_REF           (1 << 30)
#define CLASS_HAS_GLOBAL_REF    (1 << 29)

typedef struct __attribute__ ((packed)) ClassFields {
    jint accessFlags;
    Object* fields;
    Object* methods;
    Object* interfaces;
    struct Object *listNext;
    Object *name;
    struct Object *superClass;
    struct Object *elementClass;
    jint primitiveType;
    jint superIndex;
    
    CPItem *cp;
    jint initialized;
    jint instanceSize;
    void *globals;
    
    jint iofVersion;
    jint iofCount;
    struct Object **iofTable;
    
    jint maxMethodIndex;
    
    jint vTableSize;
    Object **vtable;
    
    jint iTableSize;
    Object **itable;
    
    Object *finalizer;
    Object *source_file;
} ClassFields;

typedef struct Frame {
    Object *method;
    jint line;
    VAR *sp;
    //VAR *stack;
    //VAR *local;
    VAR retVal;
} Frame;

typedef struct OpHandler {
    void *handler;
    VAR operand;
    jint index;
    jint pc;
} OpHandler;

typedef struct AOTClassData {
    const char *name;
    const unsigned char *data;
    const void **methods;
} AOTClassData;

#define MAX_FRAMES  2048
#define MAX_STACK  4096

typedef struct StringPool {
    Object *str;
    struct StringPool *next;
} StringPool;


typedef struct __attribute__ ((packed)) ThrowableFields {
    jint FP;
    Object *stack_trace;
    Object *msg;
    Object *cause;
} ThrowableFields;

typedef struct __attribute__ ((packed)) StackTraceElementFields {
    Object *declaringClass;
    Object *method_name;
    Object *file_name;
    jint line_number;
} StackTraceElementFields;

typedef struct VM {
    Frame frames[MAX_FRAMES];
    jint FP;
    VAR stack[MAX_STACK];
    jint SP;
    Object *classes;
    
    Object *exception;
    jint exceptionFP;
    jint vtable_counter;
    jint itable_counter;
    
    StringPool *strings;
    Object *jdwpTick;
    
    struct {
        int R;
        int W;
        int S;
        int C;
        Object** Q;
    } markQueue;
    
    void *heap;
    int gc_version;
    int gc_step;
    void *gc_ptr;
    int gc_blockptr;
} VM;

typedef struct NativeMethodInfo {
    const char *cls;
    const char *name;
    const char *sign;
    void *handle;
} NativeMethodInfo;

//#define FIELD_PTR(object,offset) (((void*)object)+sizeof(Object)+offset)
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
#define FIELD_PTR_O(object,offset) FIELD_PTR_TYPE(object,offset,ObjectPtr)

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
#define ARRAY_DATA_O(object) ARRAY_DATA_TYPE(object,ObjectPtr)

#define GLOBAL_PTR(f,t) *((t*)(f->declaringClass->globals+f->offset))

typedef void (*JVM_CALL)(VM*,Object*,VAR*);
#ifdef __cplusplus
extern "C" {
#endif
    
//extern void interpreter_compile(VM *vm, Method *method, char *buf, int size);
//extern void interpreter_execute_direct(VM *vm, Method *method, VAR *args);
extern Object *resolve_class(VM *vm, void *name, int isString);
extern Object *resolve_class_by_index(VM *vm, Object *cls, int index);
extern Object *resolve_class_by_signature(VM *vm, void *name, int isString);
extern Object *resolve_array_class_by_index(VM *vm, Object *cls, int index);
extern Object *resolve_method(VM *vm, void *clsName, void *name, void *signature, int isString);
extern Object *resolve_method_by_index(VM *vm, Object *cls, int index);
extern Object *find_method_recursive(Object *clso, void *name, void *signature, int isString);
extern Object *resolve_field(VM *vm, void *clsName, void *name, int isString);
extern Object *resolve_field_by_index(VM *vm,Object *cls, int index);
extern void* resolve_native_method(VM *vm, Object *method);

extern void alloc_init(VM *vm);
extern ObjectPtr alloc_object(VM *vm,Object *cls);
extern ObjectPtr alloc_object_array(VM *vm, Object *cls, int length);
extern ObjectPtr alloc_prim_array(VM *vm, Object *cls, int length);
extern Object* alloc_string(VM *vm, char *chars);
extern Object* alloc_string_utf(VM *vm, jchar *chars, jint len);

extern Object* alloc_string_utf_nogc(VM *vm, jchar *chars, jint len);
extern Object* alloc_string_nogc(VM *vm, char *chars);
extern ObjectPtr alloc_object_array_nogc(VM *vm, Object *cls, int length);
extern ObjectPtr alloc_object_nogc(VM *vm,Object *clso);
extern void gc_pause();
extern void gc_resume();

extern jint is_class_son_of(Object *son, Object *of);
extern jint check_cast(VM *vm, Object *object, Object *cls);

extern int get_line_number(MethodFields *method, int pc);
/*
jint call_java_I(VM *vm, Method *method, VAR *args);
ObjectPtr call_java_O(VM *vm, Method *method, VAR *args);
void call_java_V(VM *vm, Method *method, VAR *args);
*/

#define CALL_JVM_V(vm,method,args) ((JVM_CALL)((MethodFields*)method->instance)->entry)(vm, method, args)
extern void vm_interpret_method(VM *vm, Object *method, VAR *args);

void throw_exception(VM *vm, Object *exception);
void throw_nullpointerexception(VM *vm);
void throw_classnotfoundexception(VM *vm, Object *name);
void throw_arrayboundsexception(VM *vm, int index, int length);
void throw_castexception(VM *vm, Object *son, Object *of);
void throw_unsatisfiedlinkerror(VM *vm, Object *method);

CatchInfo *find_catch_block(VM *vm, Object *method, Object *exception, int pc);

extern inline void call_void_method(VM *vm, Object *method, VAR *args);
extern inline jbool call_boolean_method(VM *vm, Object *method, VAR *args);

extern Object java_lang_String;
extern Object java_lang_C1D;
extern Object java_lang_Class;
extern Object java_lang_reflect_Method;
extern Object java_lang_reflect_Field;

//void print_stack_trace(VM *vm);

extern char *string2c(Object *jstr);
extern Object* parse_utf8(VM *vm, char *data, int length, int intern);
extern jint compare_string(void *str1, void *str2, int isString);
extern jint compare_string_cstring(Object* jstr1, const char *str2);
extern jint string_startswith_c(Object* jstr1, const char *str2, int reqlen);
extern jint string_startswith(Object *vstr1, Object *vstr2, int len);


#ifdef __cplusplus
}
#endif

#endif /* jvm_h */
