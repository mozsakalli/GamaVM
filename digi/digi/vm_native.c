//
//  vm_native.c
//  digi
//
//  Created by mustafa on 8.06.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#include "vm.h"
#include <sys/time.h>
#include <time.h>
#ifdef __APPLE__
#include <mach/mach_time.h>
#endif
#include <math.h>

void gamavm_VM_getClass(VM *vm, Object *method, VAR *args) {
    vm->frames[vm->FP].ret.O = args[0].O ? (Object*)args[0].O->cls : NULL;
}
void gamavm_VM_getAddress(VM *vm, Object *method, VAR *args) {
    vm->frames[vm->FP].ret.J = (JLONG)args[0].O;
}

void java_lang_Object_clone(VM *vm, Object *method, VAR *args) {
    Object *result = NULL;
    Object *o = args[0].O;
    
    if(o) {
        Class *cls = o->cls->instance;
        if(cls->elementClass) {
            result = alloc_array(vm, o->cls, o->length, 0);
            int size = CLS(cls->elementClass,primitiveSize);
            if(!size) size = sizeof(Object*);
            memcpy(result->instance, o->instance, size * result->length);
        } else {
            result = alloc_object(vm, o->cls, 0);
            if(result->instance)
                memcpy(result->instance, o->instance, cls->instanceSize);
        }
    } else throw_null(vm);
    
    vm->frames[vm->FP].ret.O = result;
}

/// java/lang/System
void java_lang_System_arraycopy(VM *vm, Object *method, VAR *args) {
    Object *src = args[0].O;
    JINT srcOffset = args[1].I;
    Object *dst = args[2].O;
    JINT dstOffset = args[3].I;
    JINT length = args[4].I;
    
    if(src == NULL || dst == NULL) {
 // || src->cls->elementClass == NULL || dst->cls->elementClass == NULL
        throw_null(vm);
        return;
    }
    
    if(srcOffset < 0 || srcOffset + length > src->length) {
        throw_arraybounds(vm, srcOffset, length);
        return;
    }
    
    if(dstOffset < 0 || dstOffset + length > dst->length) {
        throw_arraybounds(vm, dstOffset, length);
        return;
    }

    Class *srccls = src->cls->instance;
    Class *dstcls = dst->cls->instance;
    if(!srccls->elementClass || !dstcls->elementClass) {
        //both must be array
        return;
    }
    
    int itemsize = 0;
    //todo: check if compatible
    if(CLS(srccls->elementClass,primitiveSize) != 0 || CLS(srccls->elementClass,primitiveSize) != 0) {
        if(CLS(srccls->elementClass,primitiveSize) != CLS(dstcls->elementClass,primitiveSize)) {
            throw_null(vm);
            return;
        }
        itemsize = CLS(srccls->elementClass,primitiveSize);
    } else {
        itemsize = sizeof(Object*);
    }
    
    memmove(dst->instance+dstOffset, src->instance+srcOffset, itemsize * length);
}

void java_lang_System_currentTimeMillis(VM *vm, Object *method, VAR *args) {
    struct timeval now;
    gettimeofday(&now, NULL);
    
    vm->frames[vm->FP].ret.J = now.tv_sec * 1000LL + now.tv_usec / 1000;
}
void java_lang_System_nanoTime(VM *vm, Object *method, VAR *args) {
    long result = 0;
    #if defined(__APPLE__)
        mach_timebase_info_data_t info;
        mach_timebase_info(&info);
        uint64_t t = mach_absolute_time();
        t *= info.numer;
        t /= info.denom;
        vm->frames[vm->FP].ret.J = (JLONG)t;
    #else
        struct timespec now;
        clock_gettime(CLOCK_MONOTONIC, &now);
        vm->frames[vm->FP].ret.J = now.tv_sec * 1000000000LL + now.tv_nsec;
    #endif
}

void java_lang_System_gc(VM *vm, Object *method, VAR *args) {
    gc_step(vm);
}

void java_lang_Math_abs_D(VM *vm, Object *method, VAR *args) {
    JDOUBLE v = args[0].D;
    if(v < 0) v = -v;
    vm->frames[vm->FP].ret.D = v;
}
void java_lang_Math_abs_F(VM *vm, Object *method, VAR *args) {
    JFLOAT v = args[0].F;
    if(v < 0) v = -v;
    vm->frames[vm->FP].ret.F = v;
}
void java_lang_Math_tan_D(VM *vm, Object *method, VAR *args) {
    vm->frames[vm->FP].ret.D = tan(args[0].D);
}
void java_lang_Math_sin_D(VM *vm, Object *method, VAR *args) {
    vm->frames[vm->FP].ret.D = sin(args[0].D);
}
void java_lang_Math_cos_D(VM *vm, Object *method, VAR *args) {
    vm->frames[vm->FP].ret.D = cos(args[0].D);
}
void java_lang_Math_sqrt_D(VM *vm, Object *method, VAR *args) {
    vm->frames[vm->FP].ret.D = sqrt(args[0].D);
}

void java_lang_Double_toStringImpl(VM *vm, Object *method, VAR *args) {
    /*
    JDOUBLE d = args[0].D;
    JINT b = args[1].I;
    char s[32];
    if ( !b ){
        sprintf(s, "%lf", d);
    } else {
        sprintf(s, "%1.20E", d);
    }
    
    // We need to match the format of Java spec.  That includes:
    // No "+" for positive exponent.
    // No leading zeroes in positive exponents.
    // No trailing zeroes in decimal portion.
    int j=0;
    int i=32;
    char s2[32];
    JINT inside=0;
    while (i-->0){
        if (inside){
            if (s[i]=='.'){
                s2[j++]='0';
            }
            if (s[i]!='0'){
                inside=0;
                s2[j++]=s[i];
            }
            
        } else {
            if (s[i]=='E'){
                inside=1;
            }
            if (s[i]=='+'){
                // If a positive exponent, we don't need leading zeroes in
                // the exponent
                while (s2[--j]=='0'){
                    
                }
                j++;
                continue;
            }
            s2[j++]=s[i];
        }
    }
    i=0;
    while (j-->0){
        s[i++]=s2[j];
        if (s[i]=='\0'){
            break;
        }
    }
     */
    char buf[21];
    int length = snprintf(buf,20,"%g",args[0].D);
    vm->frames[vm->FP].ret.O = alloc_string_ascii(vm, buf, 0);
}

void java_lang_Float_toStringImpl(VM *vm, Object *method, VAR *args) {
    /*
    char s[33];
    JFLOAT d = args[0].F;
    JINT b = args[1].I;
    int len ;
    if ( !b ){
        len = snprintf(s, 32, "%f", d);
    } else {
        len = snprintf(s, 32, "%1.20E", d);
    }
    // We need to match the format of Java spec.  That includes:
    // No "+" for positive exponent.
    // No leading zeroes in positive exponents.
    // No trailing zeroes in decimal portion.
    int j=0;
    int i=len;
    char s2[33];
    JINT inside=0;
    while (i-->0){
        if (inside){
            if (s[i]=='.'){
                s2[j++]='0';
            }
            if (s[i]!='0'){
                inside=0;
                s2[j++]=s[i];
            }
            
        } else {
            if (s[i]=='E'){
                inside=1;
            }
            if (s[i]=='+'){
                // If a positive exponent, we don't need leading zeroes in
                // the exponent
                while (s2[--j]=='0'){
                    
                }
                j++;
                continue;
            }
            s2[j++]=s[i];
        }
    }
    i=0;
    while (j-->0){
        s[i++]=s2[j];
        if (s[i]=='\0'){
            break;
        }
    }
    */
    char buf[21];
    int length = snprintf(buf,20,"%g",args[0].F);
    vm->frames[vm->FP].ret.O = alloc_string_ascii(vm, buf, 0);
}

void java_lang_Float_intBitsToFloat(VM *vm, Object *method, VAR *args) {
    float *f = (float*)&args[0].I;
    vm->frames[vm->FP].ret.F = *f;
}


extern void java_lang_System_SystemOutStream_printImpl(VM *vm, Object *method, VAR *args);

NativeMethodInfo vm_native_methods[] = {
    {"gamavm/VM:getClass:(Ljava/lang/Object;)Ljava/lang/Class;", &gamavm_VM_getClass},
    {"gamavm/VM:getAddress:(Ljava/lang/Object;)J", &gamavm_VM_getAddress},

    {"java/lang/Object:clone:()Ljava/lang/Object;", &java_lang_Object_clone},
    
    {"java/lang/System:arraycopy:(Ljava/lang/Object;ILjava/lang/Object;II)V", &java_lang_System_arraycopy},
    {"java/lang/System$SystemOutStream:printImpl:(Ljava/lang/String;)V", &java_lang_System_SystemOutStream_printImpl},
    {"java/lang/System:gc:()V", &java_lang_System_gc},
    {"java/lang/System:nanoTime:()J", &java_lang_System_nanoTime},
    {"java/lang/System:currentTimeMillis:()J", &java_lang_System_currentTimeMillis},

    {"java/lang/Float:toStringImpl:(FZ)Ljava/lang/String;", &java_lang_Float_toStringImpl},

    {"java/lang/Double:toStringImpl:(DZ)Ljava/lang/String;", &java_lang_Double_toStringImpl},
    NULL
};
