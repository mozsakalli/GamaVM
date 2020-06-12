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

typedef struct Object {
    OBJECT_HEADER;
} Object;
typedef Object* ObjectPtr;

typedef struct Array {
    OBJECT_HEADER;
    jint length;
    void* data;
} Array;

typedef struct String {
    OBJECT_HEADER;
    Array *chars;
    jint start;
    jint length;
    jint hashcode;
} String;

typedef union VAR {
    jbyte B;
    jbool Z;
    jchar C;
    jshort S;
    jint I;
    jfloat F;
    jlong J;
    jdouble D;
    Object *O;
} VAR;

typedef struct Field {
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
    jint calculatedIndex;
} LocalVarInfo;

typedef struct Method {
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

typedef struct Class {
    OBJECT_HEADER;
    jint accessFlags;
    jint nameIndex;
    jint superIndex;
    CPItem **interfaces;
    Array* fields;
    Array* methods;
    struct Class *listNext;
    String *name;
    String *superName;
    struct Class *superClass;
    struct Class *elementClass;
    CPItem *cp;
    jint initialized;
    jint instanceSize;
    VAR *globals;
} Class;

typedef struct Frame {
    Method *method;
    jint pc;
    VAR *stack;
    VAR *local;
    VAR retVal;
    jint *sp;
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
#define MAX_LOCALS  4096

typedef struct VM {
    Frame frames[MAX_FRAMES];
    jint fp;
    VAR localStack[MAX_LOCALS];
    Class *classes;
    Object *exception;
    int booting;
} VM;

typedef jint (*JVM_CALL)(VM*,Method*,VAR*);

extern void interpreter_compile(VM *vm, Method *method, char *buf, int size);
extern void interpreter_execute_direct(VM *vm, Method *method, VAR *args);
extern Method *resolve_method_by_index(VM *vm, Class *cls, int index);
extern Field *resolve_field_by_index(VM *vm,Class *cls, int index);

inline jint call_java_I(VM *vm, Method *method, VAR *args);
ObjectPtr call_java_O(VM *vm, Method *method, VAR *args);
void call_java_V(VM *vm, Method *method, VAR *args);

#endif /* jvm_h */
