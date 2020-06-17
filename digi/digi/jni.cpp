//
// Created by mustafa on 2020-06-15.
//

#include <jni.h>
#include <android/log.h>
#include "vm.h"

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
    void* fieldOrMethod;
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

void jni_get_field(VM *vm, Object *method, VAR *args) {
    JNIEnv *env = getJNIEnv();
    Method *m = (Method*)method->instance;
    JNIMethodInfo *mi = (JNIMethodInfo*)m->externalData;
    VAR *ret = &vm->frames[vm->FP].ret;
    if(IS_STATIC(m->flags)) {
        jclass jcls = (jclass)CLS(m->declaringClass, externalData);
        if(!jcls) {
            throw_null(vm);
            return;
        }
        switch(mi->returnType) {
            case 'B': ret->I = env->GetStaticByteField(jcls, (jfieldID)mi->fieldOrMethod);break;
            case 'Z': ret->I = env->GetStaticBooleanField(jcls, (jfieldID)mi->fieldOrMethod);break;
            case 'C': ret->I = env->GetStaticCharField(jcls, (jfieldID)mi->fieldOrMethod);break;
            case 'S': ret->I = env->GetStaticShortField(jcls, (jfieldID)mi->fieldOrMethod);break;
            case 'I': ret->I = env->GetStaticIntField(jcls, (jfieldID)mi->fieldOrMethod);break;
            case 'F': ret->D = env->GetStaticFloatField(jcls, (jfieldID)mi->fieldOrMethod);break;
            case 'D': ret->D = env->GetStaticDoubleField(jcls, (jfieldID)mi->fieldOrMethod);break;
            case 'J': ret->J = env->GetStaticLongField(jcls, (jfieldID)mi->fieldOrMethod);break;
        }
    } else {
        if(!args[0].O) {
            throw_null(vm);
            return;
        }
        jobject javaObject = (jobject)*((JLONG**)args[0].O->instance);
        if(!javaObject) {
            throw_null(vm);
            return;
        }
        switch(mi->returnType) {
            case 'B': ret->I = env->GetByteField(javaObject, (jfieldID)mi->fieldOrMethod);break;
            case 'Z': ret->I = env->GetBooleanField(javaObject, (jfieldID)mi->fieldOrMethod);break;
            case 'C': ret->I = env->GetCharField(javaObject, (jfieldID)mi->fieldOrMethod);break;
            case 'S': ret->I = env->GetShortField(javaObject, (jfieldID)mi->fieldOrMethod);break;
            case 'I': ret->I = env->GetIntField(javaObject, (jfieldID)mi->fieldOrMethod);break;
            case 'F': ret->F = env->GetFloatField(javaObject, (jfieldID)mi->fieldOrMethod);break;
            case 'D': ret->D = env->GetDoubleField(javaObject, (jfieldID)mi->fieldOrMethod);break;
            case 'J': ret->J = env->GetLongField(javaObject, (jfieldID)mi->fieldOrMethod);break;
        }
    }
}

void jni_set_field(VM *vm, Object *method, VAR *args) {

}

void jni_invoke(VM *vm, Object *method, VAR *args) {
    Method *m = (Method*)method->instance;
    JNIMethodInfo *mi = (JNIMethodInfo*)m->externalData;
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
        jclass jcls = (jclass)CLS(m->declaringClass,externalData);
        jmethodID jm = (jmethodID)mi->fieldOrMethod;
        switch(mi->returnType) {
            case 'V':
                env->CallStaticVoidMethodA(jcls, jm, jvals);
                break;
            case 'B':
                ret->I = env->CallStaticByteMethodA(jcls, jm, jvals);
                break;
            case 'Z':
                ret->I = env->CallStaticBooleanMethodA(jcls, jm, jvals);
                break;
            case 'C':
                ret->I = env->CallStaticCharMethodA(jcls, jm, jvals);
                break;
            case 'S':
                ret->I = env->CallStaticShortMethodA(jcls, jm, jvals);
                break;
            case 'I':
                ret->I = env->CallStaticIntMethodA(jcls, jm, jvals);
                break;
            case 'F':
                ret->F = env->CallStaticFloatMethodA(jcls, jm, jvals);
                break;
            case 'J':
                ret->I = env->CallStaticLongMethodA(jcls, jm, jvals);
                break;
            case 'D':
                ret->I = env->CallStaticDoubleMethodA(jcls, jm, jvals);
                break;
            case JNIARRAY_B:
            case JNIARRAY_Z:
            case JNIARRAY_C:
            case JNIARRAY_S:
            case JNIARRAY_I:
            case JNIARRAY_F:
            case JNIARRAY_J:
            case JNIARRAY_D:
                jobject jresult = env->CallStaticObjectMethodA(jcls, jm, jvals);
                if(jresult) {
                    int len = env->GetArrayLength((jarray)jresult);
                    #define COPYARRAY(G,J,M) case JNIARRAY_##G : ret->O = alloc_array_##G(vm,len,0); env->M((J##Array)jresult, 0, len, (J*)ret->O->instance); break
                    switch(mi->returnType) {
                        COPYARRAY(B,jbyte,GetByteArrayRegion);
                        COPYARRAY(Z,jboolean,GetBooleanArrayRegion);
                        COPYARRAY(C,jchar,GetCharArrayRegion);
                        COPYARRAY(S,jshort,GetShortArrayRegion);
                        COPYARRAY(I,jint,GetIntArrayRegion);
                        COPYARRAY(F,jfloat,GetFloatArrayRegion);
                        COPYARRAY(D,jdouble,GetDoubleArrayRegion);
                        COPYARRAY(J,jlong,GetLongArrayRegion);
                    }
                } else ret->O = nullptr;
                break;


        }
    }
}


void jni_invoke_resolve(VM *vm, Object *method, VAR *args) {
    Method *m = (Method*)method->instance;
    jclass jcls = (jclass)CLS(m->declaringClass, externalData);
    JNIEnv *env = getJNIEnv();

    JNIMethodInfo *mi = new JNIMethodInfo;
    mi->argCount = 0;

    mi->fieldOrMethod = (jmethodID)m->externalData;

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

    m->externalData = mi;
    if(m->externalFlags & 2) {
        m->entry = (void*)(mi->returnType == 'V' ? &jni_set_field : &jni_get_field);
    } else {
        m->entry = (void*) &jni_invoke;
    }
    CALLVM_V(vm, method, args);
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
        env->ExceptionClear();
        return;
    }
    jcls = (jclass)env->NewGlobalRef(jcls);
    cls->externalData = jcls;

    if(cls->methods) {
        for(int i=0; i<cls->methods->length; i++) {
            Method *m = (Method*)ARRAY_DATA_O(cls->methods)[i]->instance;
            snprintf(namechars,127, "%s", string_to_ascii(m->externalName ? m->externalName : m->name));
            snprintf(signchars, 127, "%s", string_to_ascii(m->signature));
            if(m->externalFlags & 2) {
                jfieldID jf = IS_STATIC(m->flags) ? env->GetStaticFieldID(jcls, namechars, signchars) : env->GetFieldID(jcls, namechars, signchars);
                env->ExceptionClear();
                if (jf) {
                    m->externalData = jf;
                    m->entry = (void *) &jni_invoke_resolve;
                }
            } else {
                jmethodID jm = IS_STATIC(m->flags) ? env->GetStaticMethodID(jcls, namechars,signchars) : env->GetMethodID(jcls, namechars, signchars);
                env->ExceptionClear();
                if (jm) {
                    m->externalData = jm;
                    m->entry = (void *) &jni_invoke_resolve;
                }
            }
        }
    }
}