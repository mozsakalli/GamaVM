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

struct Class;

#define OBJECT_HEADER \
struct Class *cls;

#define GC_LIVE_STACK(o) if(o) o->gc_mark.live = 1;
#define GC_DEAD_STACK(o) if(o) o->gc_mark.live = 0;

typedef char jbyte;
typedef char jbool;
typedef unsigned short jchar;
typedef short jshort;
typedef short jushort;
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
    OBJECT_HEADER;
} Object;
typedef Object* ObjectPtr;

typedef struct Array {
    OBJECT_HEADER;
    jint length;
    char data[0];
} Array;

typedef struct __attribute__ ((packed)) String {
    OBJECT_HEADER;
    Array *chars;
    jint start;
    jint length;
    jint hashcode;
    void *__native;
} String;

typedef union VAR {
    jint I;
    jfloat F;
    jlong J;
    jdouble D;
    Object *O;
} VAR;

typedef struct __attribute__ ((packed)) Field {
    OBJECT_HEADER;
    jint accessFlags;
    jint nameIndex;
    jint signatureIndex;
    struct Class *declaringClass;
    String *name;
    String *signature;
    jint offset;
} Field;

typedef struct LocalVarInfo {
    jint start;
    jint length;
    String *name;
    String *signature;
    jint index;
} LocalVarInfo;

typedef struct LineNumberInfo {
    unsigned short pc;
    unsigned short line;
} LineNumberInfo;

typedef struct CatchInfo {
    jint start;
    jint end;
    jint pc;
    jint type;
    void *label;
} CatchInfo;

typedef struct __attribute__ ((packed)) Method {
    OBJECT_HEADER;
    jint accessFlags;
    jint nameIndex;
    jint signatureIndex;
    jint maxStack;
    jint maxLocals;
    struct Class *declaringClass;
    String *name;
    String *signature;
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
} Method;

typedef struct CPItem {
    VAR value;
    jint index1;
    jint index2;
    jint type;
} CPItem;

typedef struct __attribute__ ((packed)) Class {
    OBJECT_HEADER;
    jint accessFlags;
    jint nameIndex;
    jint superIndex;
    jint *interfaceDefs;
    Array* fields;
    Array* methods;
    Array* interfaces;
    struct Class *listNext;
    String *name;
    String *superName;
    struct Class *superClass;
    struct Class *elementClass;
    jint primitiveType;
    
    CPItem *cp;
    jint initialized;
    jint instanceSize;
    void *globals;
    
    jint iofVersion;
    jint iofCount;
    struct Class **iofTable;
    
    jint maxMethodIndex;
    
    jint vTableSize;
    Method **vtable;
    
    jint iTableSize;
    Method **itable;
    
    Method *finalizer;
    String *source_file;
} Class;

typedef struct Frame {
    Method *method;
    jint pc;
    VAR *stack;
    VAR *local;
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

typedef struct ClassLoader {
    OBJECT_HEADER;
    struct ClassLoader *parent;
} ClassLoader;

#define MAX_FRAMES  2048
#define MAX_STACK  4096

typedef struct StringPool {
    String *str;
    struct StringPool *next;
} StringPool;


typedef struct __attribute__ ((packed)) Throwable {
    OBJECT_HEADER;
    jint FP;
    Array *stack_trace;
    String *msg;
    Object *cause;
} Throwable;

typedef struct __attribute__ ((packed)) StackTraceElement {
    OBJECT_HEADER;
    String *declaringClass;
    String *method_name;
    String *file_name;
    jint line_number;
} StackTraceElement;

typedef struct VM {
    Frame frames[MAX_FRAMES];
    jint FP;
    VAR stack[MAX_STACK];
    jint SP;
    Class *classes;
    
    Object **exception;
    jint exceptionFP;
    jint vtable_counter;
    jint itable_counter;
    
    StringPool *strings;
    
    int gc_mark;
    Object *gc_objects;
    
    struct {
        int R;
        int W;
        int S;
        int C;
        Object** Q;
    } markQueue;
} VM;

typedef struct NativeMethodInfo {
    const char *cls;
    const char *name;
    const char *sign;
    void *handle;
} NativeMethodInfo;


#define GLOBAL_PTR(f,t) *((t*)(f->declaringClass->globals+f->offset))

typedef void (*JVM_CALL)(VM*,Method*,VAR*);

extern void interpreter_compile(VM *vm, Method *method, char *buf, int size);
extern void interpreter_execute_direct(VM *vm, Method *method, VAR *args);
extern Class *resolve_class(VM *vm, void *name, int isString);
extern Class *resolve_class_by_index(VM *vm, Class *cls, int index);
extern Class *resolve_array_class_by_index(VM *vm, Class *cls, int index);
extern Method *resolve_method_by_index(VM *vm, Class *cls, int index);
extern Field *resolve_field_by_index(VM *vm,Class *cls, int index);

extern void gc_init(VM *vm);
extern void gc_register_current_thread();
extern void gc_unregister_current_thread();
extern void *gc_alloc(VM *vm, int size);
extern void *gc_alloc_global(VM *vm, int size);
extern void *gc_alloc_atomic(VM *vm, int size);
extern ObjectPtr alloc_object(VM *vm,Class *cls);
extern ObjectPtr alloc_object_array(VM *vm, Class *cls, int length);
extern ObjectPtr alloc_prim_array(VM *vm, Class *cls, int length);
extern String* alloc_string(VM *vm, char *chars);

extern jint is_class_son_of(Class *son, Class *of);
extern jint check_cast(VM *vm, Object *object, Class *cls);

extern int get_line_number(Method *method, int pc);

jint call_java_I(VM *vm, Method *method, VAR *args);
ObjectPtr call_java_O(VM *vm, Method *method, VAR *args);
void call_java_V(VM *vm, Method *method, VAR *args);


void throw_exception(VM *vm, Object *exception);
void throw_nullpointerexception(VM *vm);
void throw_classnotfoundexception(VM *vm, Object *name);
void throw_arrayboundsexception(VM *vm, int index, int length);
void throw_castexception(VM *vm, Class *son, Class *of);

CatchInfo *find_catch_block(VM *vm, Method *method, Object *exception, int pc);

extern Class java_lang_String;
extern Class java_lang_C1D;

void print_stack_trace(VM *vm);

#endif /* jvm_h */
