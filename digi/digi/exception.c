//
//  exception.c
//  digi
//
//  Created by mustafa on 7.06.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#include "vm.h"
#ifdef __ANDROID__

#include <android/log.h>

#endif

void throw_exception(VM *vm, Object *exception) {
    int fp = vm->FP;
    vm->exception = exception;
    if(exception) {
        Throwable *thr = exception->instance;
        if(!thr->cause) thr->cause = exception;
        char tmp[4096];
        char *ptr = tmp;
        ptr += sprintf(tmp,"%s\n",string_to_ascii(CLS(exception->cls, name)));
        if(fp > 0) {
            Object *arr = alloc_array(vm, get_arrayclass_of(vm, vm->jlSTE), fp, 0);
            for(int i=1; i<=fp; i++) {
                Frame *f = &vm->frames[i];
                Object *seo = alloc_object(vm, vm->jlSTE, 0);
                StackTraceElement *se = (StackTraceElement*)seo->instance;
                Method *mth = f->method->instance;
                ptr += sprintf(ptr, "%s", string_to_ascii(CLS(mth->declaringClass,name)));
                ptr += sprintf(ptr, ":%s at %d\n", string_to_ascii(mth->name), f->line);
                se->declaringClass = CLS(mth->declaringClass,name);
                se->fileName = CLS(mth->declaringClass,sourceFile);
                se->methodName = mth->name;
                se->lineNumber = f->line;
                ((Object**)arr->instance)[fp - i] = seo;
            }
            thr->stackTrace = arr;
        }
        //__android_log_print(ANDROID_LOG_ERROR, "GamaVM", "%s", tmp);
    }
}

void throw_null(VM *vm) {
    static Object *npe = NULL;
    static Object *mth = NULL;
    if(!npe) {
        npe = resolve_class(vm, vm->sysClassLoader, (JCHAR*)L"java/lang/NullPointerException", 30, 1, NULL);
        if(!npe) return;
        
        mth = find_method(vm, npe, (JCHAR*)L"<init>", 6, (JCHAR*)L"()V", 3);
    }
    Object *exp = alloc_object(vm, npe, 0);
    if(mth) {
        VAR args[1] = {{ .O = exp }};
        CALLVM_V(vm, mth, &args[0]);
    }
    throw_exception(vm, exp);
}

void throw_classnotfound(VM *vm, JCHAR *name, int len) {
    static Object *npe = NULL;
    static Object *mth = NULL;
    if(!npe) {
        npe = resolve_class(vm, vm->sysClassLoader, (JCHAR*)L"java/lang/ClassNotFoundException", 32, 1, NULL);
        if(!npe) return;
        
        mth = find_method(vm, npe, (JCHAR*)L"<init>", 6, (JCHAR*)L"(Ljava/lang/String;)V", 21);
    }
    Object *exp = alloc_object(vm, npe, 0);
    if(mth) {
        VAR args[2] = {{ .O = exp }, { .O = alloc_string_java(vm, name, len, 0) }};
        CALLVM_V(vm, mth, &args[0]);
    }
    
    printf("Class Not Found! : %s\n", jchar_to_ascii(name, len));
    throw_exception(vm, exp);
}

void throw_arraybounds(VM *vm, int index, int length) {
    static Object *npe = NULL;
    static Object *mth = NULL;
    if(!npe) {
        npe = resolve_class(vm, vm->sysClassLoader, (JCHAR*)L"java/lang/ArrayIndexOutOfBoundsException", 40, 1, NULL);
        if(!npe) return;
        
        mth = find_method(vm, npe, (JCHAR*)L"<init>", 6, (JCHAR*)L"(Ljava/lang/String;)V", 21);
    }
    Object *exp = alloc_object(vm, npe, 0);
    if(mth) {
        char tmp[128];
        sprintf(tmp, "%d of %d", index, length);
        VAR args[2] = {{ .O = exp }, { .O = alloc_string_ascii(vm, tmp, 0) }};
        CALLVM_V(vm, mth, &args[0]);
    }
    throw_exception(vm, exp);
}

void throw_cast(VM *vm, Object *son, Object *of) {
    static Object *npe = NULL;
    static Object *mth = NULL;
    if(!npe) {
        npe = resolve_class(vm, vm->sysClassLoader, (JCHAR*)L"java/lang/ClassCastException", 28, 1, NULL);
        if(!npe) return;
        
        mth = find_method(vm, npe, (JCHAR*)L"<init>",6, (JCHAR*)L"(Ljava/lang/String;)V", 21);
    }
    Object *exp = alloc_object(vm, npe, 0);
    if(mth) {
        char tmp[512];
        char *ptr = tmp;
        ptr += sprintf(tmp, "%s", string_to_ascii(CLS(son,name)));
        ptr += sprintf(ptr, " can't cast to ");
        ptr += sprintf(ptr, "%s", string_to_ascii(CLS(of, name)));
        VAR args[2] = {{ .O = exp }, { .O = alloc_string_ascii(vm, tmp, 0) }};
        CALLVM_V(vm, mth, &args[0]);
    }
    throw_exception(vm, exp);
}

void throw_unsatisfiedlink(VM *vm, Object *method) {
    static Object *npe = NULL;
    static Object *mth = NULL;
    if(!npe) {
        npe = resolve_class(vm, vm->sysClassLoader, (JCHAR*)L"java/lang/UnsatisfiedLinkError", 30, 1, NULL);
        if(!npe) return;
        
        mth = find_method(vm, npe, (JCHAR*)L"<init>",6, (JCHAR*)L"(Ljava/lang/String;)V", 21);
    }
    Object *exp = alloc_object(vm, npe, 0);
    if(mth) {
        char tmp[256];
        char *ptr = &tmp[0];
        Object *dc = ((Method*)method->instance)->declaringClass;
        Object *clsName = CLS(dc, name);
        ptr += sprintf(tmp,"%s",string_to_ascii(clsName));
        ptr += sprintf(ptr,":%s",string_to_ascii(MTH(method,name)));
        ptr += sprintf(ptr,":%s",string_to_ascii(MTH(method,signature)));

        VAR args[2] = {{ .O = exp }, { .O = alloc_string_ascii(vm, tmp, 0) }};
        CALLVM_V(vm, mth, &args[0]);

        GLOG("%s", tmp);
    }
    
    throw_exception(vm, exp);
}

void throw_nosuchmethod(VM *vm, JCHAR *clsName, int clsLen, JCHAR *name, int nameLen, JCHAR *sign, int signLen) {
    static Object *npe = NULL;
    static Object *mth = NULL;
    if(!npe) {
        npe = resolve_class(vm, vm->sysClassLoader, (JCHAR*)L"java/lang/NoSuchMethodException", 31, 1, NULL);
        if(!npe) return;
        
        mth = find_method(vm, npe, (JCHAR*)L"<init>",6, (JCHAR*)L"(Ljava/lang/String;)V", 21);
    }
    Object *exp = alloc_object(vm, npe, 0);
    if(mth) {
        char tmp[256];
        char *ptr = &tmp[0];
        //Object *dc = ((Method*)method->instance)->declaringClass;
        //Object *clsName = CLS(dc, name);
        ptr += sprintf(tmp,"%s",jchar_to_ascii(clsName, clsLen));
        ptr += sprintf(ptr,":%s",jchar_to_ascii(name, nameLen));
        ptr += sprintf(ptr,":%s",jchar_to_ascii(sign, signLen));

        VAR args[2] = {{ .O = exp }, { .O = alloc_string_ascii(vm, tmp, 0) }};
        CALLVM_V(vm, mth, &args[0]);
    }
    
    throw_exception(vm, exp);
}

void throw_abstractmethod(VM *vm, JCHAR *clsName, int clsLen, JCHAR *name, int nameLen, JCHAR *sign, int signLen) {
    static Object *npe = NULL;
    static Object *mth = NULL;
    if(!npe) {
        npe = resolve_class(vm, vm->sysClassLoader, (JCHAR*)L"java/lang/AbstractMethodError", 29, 1, NULL);
        if(!npe) return;

        mth = find_method(vm, npe, (JCHAR*)L"<init>",6, (JCHAR*)L"(Ljava/lang/String;)V", 21);
    }
    Object *exp = alloc_object(vm, npe, 0);
    if(mth) {
        char tmp[256];
        char *ptr = &tmp[0];
        //Object *dc = ((Method*)method->instance)->declaringClass;
        //Object *clsName = CLS(dc, name);
        ptr += sprintf(tmp,"%s",jchar_to_ascii(clsName, clsLen));
        ptr += sprintf(ptr,":%s",jchar_to_ascii(name, nameLen));
        ptr += sprintf(ptr,":%s",jchar_to_ascii(sign, signLen));

        VAR args[2] = {{ .O = exp }, { .O = alloc_string_ascii(vm, tmp, 0) }};
        CALLVM_V(vm, mth, &args[0]);
    }

    throw_exception(vm, exp);
}