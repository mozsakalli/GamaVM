//
// Created by mustafa on 2020-06-15.
//

#include <jni.h>
#include <android/log.h>
#include "vm.h"
#include "../../../../Library/Android/sdk/ndk/21.3.6528147/toolchains/llvm/prebuilt/darwin-x86_64/sysroot/usr/include/android/log.h"

extern JNIEnv *getJNIEnv();
extern VM *gamaVM;

#define JNIARRAY_B  0
#define JNIARRAY_Z  1
#define JNIARRAY_C  2
#define JNIARRAY_S  3
#define JNIARRAY_I  4
#define JNIARRAY_F  5
#define JNIARRAY_J  6
#define JNIARRAY_D  7

typedef struct JNIMethodInfo {
    jmethodID jmethod;
    int argCount;
    char argTypes[32];
    Object *argClasses[32];

    char returnType;
    Object *returnClass;
} JNIMethodInfo;

int jni_parse_signature(VM *vm, JCHAR *sign, int ptr, char *type, Object **cls) {
    *type = sign[ptr++];
    if(*type == 'L') {
        int start = ptr;
        while(sign[ptr] != ';') ptr++;
        *cls = resolve_class(vm, sign + start, ptr - start, 1, nullptr);
        ptr++;
        if(vm->exception) return 0;
    } else if(*type == '[') {
        if(sign[ptr] == '[' || sign[ptr] == 'L') {
            //todo: support multi dimensional arrays
            throw_null(vm);
            return 0;
        }
        switch (sign[ptr]) {
            case 'B': *type = JNIARRAY_B; *cls = get_arrayclass_of(vm, vm->primClasses[PRIM_B]); break;
            case 'Z': *type = JNIARRAY_Z; *cls = get_arrayclass_of(vm, vm->primClasses[PRIM_Z]); break;
            case 'C': *type = JNIARRAY_C; *cls = get_arrayclass_of(vm, vm->primClasses[PRIM_C]); break;
            case 'S': *type = JNIARRAY_S; *cls = get_arrayclass_of(vm, vm->primClasses[PRIM_S]); break;
            case 'I': *type = JNIARRAY_I; *cls = get_arrayclass_of(vm, vm->primClasses[PRIM_I]); break;
            case 'F': *type = JNIARRAY_F; *cls = get_arrayclass_of(vm, vm->primClasses[PRIM_F]); break;
            case 'J': *type = JNIARRAY_J; *cls = get_arrayclass_of(vm, vm->primClasses[PRIM_J]); break;
            case 'D': *type = JNIARRAY_D; *cls = get_arrayclass_of(vm, vm->primClasses[PRIM_D]); break;
        }
        ptr++;
    }

    return ptr;
}

void gama_to_jni(VM *vm, JNIEnv *env, char type, Object *cls, VAR *a, jvalue *j) {
    switch (type) {
        case 'B': j->b = a->I; break;
        case 'Z': j->z = a->I; break;
        case 'C': j->c = a->I; break;
        case 'S': j->s = a->I; break;
        case 'I': j->i = a->I; break;
        case 'F': j->f = a->F; break;
        case 'J': j->j = a->J; break;
        case 'D': j->d = a->D; break;
        case 'L': {
            if(cls == vm->jlString) {
                __android_log_print(ANDROID_LOG_INFO, "GamaVM", "%s", string_to_ascii(a->O));
                if(a->O)
                    j->l = env->NewString(STRCHARS(a->O), STRLEN(a->O));
            } else {

            }
        } break;
    }
}

void jni_to_gama(VM *vm, JNIEnv *env, char type, Object *cls, VAR *a, jvalue *j) {
    switch (type) {

    }
}

void jni_invoke(VM *vm, Object *method, VAR *args) {
    Method *m = (Method*)method->instance;
    JNIMethodInfo *mi = (JNIMethodInfo*)m->native;
    JNIEnv *env = getJNIEnv();
    VAR *a = args;

    int isStatic = IS_STATIC(m->flags);
    if(!isStatic) a++;
    jvalue jvals[32];
    for(int i=0; i<mi->argCount; i++) {
        gama_to_jni(vm, env, mi->argTypes[i], mi->argClasses[i], a, &jvals[i]);
        a++;
    }

    VAR *ret = &vm->frames[vm->FP].ret;
    jvalue jret;
    if(isStatic) {
        jclass jcls = (jclass)CLS(m->declaringClass,native);
        switch(mi->returnType) {
            case 'B':
                ret->I = env->CallStaticByteMethodA(jcls, mi->jmethod, jvals);
                break;
            case 'Z':
                ret->I = env->CallStaticBooleanMethodA(jcls, mi->jmethod, jvals);
                break;
            case 'C':
                ret->I = env->CallStaticCharMethodA(jcls, mi->jmethod, jvals);
                break;
            case 'S':
                ret->I = env->CallStaticShortMethodA(jcls, mi->jmethod, jvals);
                break;
            case 'I':
                ret->I = env->CallStaticIntMethodA(jcls, mi->jmethod, jvals);
                break;
            case 'F':
                ret->F = env->CallStaticFloatMethodA(jcls, mi->jmethod, jvals);
                break;
            case 'J':
                ret->I = env->CallStaticLongMethodA(jcls, mi->jmethod, jvals);
                break;
            case 'D':
                ret->I = env->CallStaticDoubleMethodA(jcls, mi->jmethod, jvals);
                break;
            case JNIARRAY_B:
            case JNIARRAY_Z:
            case JNIARRAY_C:
            case JNIARRAY_S:
            case JNIARRAY_I:
            case JNIARRAY_F:
            case JNIARRAY_J:
            case JNIARRAY_D:
                jobject jresult = env->CallStaticObjectMethodA(jcls, mi->jmethod, jvals);
                if(jresult) {
                    int len = env->GetArrayLength((jarray)jresult);
                    switch(mi->returnType) {
                        case JNIARRAY_B:
                            ret->O = alloc_array_B(vm, len, 0);
                            env->GetByteArrayRegion((jbyteArray)jresult, 0, len, (jbyte*)ret->O->instance);
                            break;
                    }
                } else ret->O = nullptr;
                break;


        }
    }
}


void jni_invoke_resolve(VM *vm, Object *method, VAR *args) {
    Method *m = (Method*)method->instance;
    jclass jcls = (jclass)CLS(m->declaringClass, native);
    JNIEnv *env = getJNIEnv();

    JNIMethodInfo *mi = new JNIMethodInfo;
    mi->argCount = 0;

    mi->jmethod = (jmethodID)m->native;

    JCHAR *sign = STRCHARS(m->signature);
    int ptr = 1;
    while(sign[ptr] != ')') {
        ptr = jni_parse_signature(vm, sign, ptr, &mi->argTypes[mi->argCount], &mi->argClasses[mi->argCount]);
        if(vm->exception)
            return;
        mi->argCount++;
    }
    ptr++;
    jni_parse_signature(vm, sign, ptr, &mi->returnType, &mi->returnClass);

    m->entry = (void*)&jni_invoke;
    m->native = mi;
    jni_invoke(vm, method, args);
}

extern "C" void vm_link_external_class(VM *vm, Object *clsObject) {
    JNIEnv *env = getJNIEnv();
    Class *cls = (Class*)clsObject->instance;
    char namechars[128];
    char signchars[128];
    snprintf(namechars,127,"%s", string_to_ascii(cls->name));
    jclass jcls = env->FindClass(namechars);
    if(!jcls) {
        //todo: throw
        return;
    }
    jcls = (jclass)env->NewGlobalRef(jcls);
    cls->native = jcls;

    if(cls->methods) {
        for(int i=0; i<cls->methods->length; i++) {
            Method *m = (Method*)ARRAY_DATA_O(cls->methods)[i]->instance;
            snprintf(namechars,127, "%s", string_to_ascii(m->name));
            snprintf(signchars, 127, "%s", string_to_ascii(m->signature));
            jmethodID jm = IS_STATIC(m->flags) ? env->GetStaticMethodID(jcls, namechars, signchars) : env->GetMethodID(jcls, namechars, signchars);
            if(jm) {
                m->native = jm;
                m->entry = (void*)&jni_invoke_resolve;
            }
        }
    }
}