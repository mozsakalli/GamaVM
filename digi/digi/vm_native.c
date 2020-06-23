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
#include "miniz.h"

void gamavm_VM_getClass(VM *vm, Object *method, VAR *args) {
    vm->frames[vm->FP].ret.O = args[0].O ? (Object*)args[0].O->cls : NULL;
}
void gamavm_VM_getAddress(VM *vm, Object *method, VAR *args) {
    vm->frames[vm->FP].ret.J = (JLONG)args[0].O;
}
void gamavm_VM_allocObject(VM *vm, Object *method, VAR *args) {
    if(!args[0].O) {
        throw_null(vm);
        return;
    }
    
    vm->frames[vm->FP].ret.O = alloc_object(vm, args[0].O, 0);
}
void gamavm_VM_wrapBytes(VM *vm, Object *method, VAR *args) {
    Object *arr = NULL;
    if(args[0].J && args[1].I >= 0) {
        arr = alloc_object(vm, get_arrayclass_of(vm, vm->primClasses[PRIM_B]), 0);
        arr->length = args[1].I;
        arr->instance = (void*)args[0].J;
    }
    vm->frames[vm->FP].ret.O = arr;
}
void gamavm_VM_freeMem(VM *vm, Object *method, VAR *args) {
    if(args[0].J) free((void*)args[0].J);
}
void gamavm_VM_extractZip(VM *vm, Object *method, VAR *args) {
    Object *path = args[0].O;
    Object *array = args[1].O;
    JINT offset = args[2].I;
    if(!path || !array) {
        throw_null(vm);
        return;
    }
    if(offset < 0 || offset >= array->length) {
        throw_arraybounds(vm, offset, array->length);
        return;
    }
    
    vm->frames[vm->FP].ret.O = NULL;
    
    mz_zip_archive zip = {0};
    if(mz_zip_reader_init_mem(&zip, array->instance+offset, array->length-offset, 0) == MZ_FALSE) {
        return;
    }

    char tmp[512];
    sprintf(tmp, "%s", string_to_ascii(path));
    int file_index = mz_zip_reader_locate_file(&zip, tmp, NULL, 0);//
    mz_zip_archive_file_stat file_stat = {0};
    if (!mz_zip_reader_file_stat(&zip, file_index, &file_stat)) {
        return;
    }
    size_t uncompressed_size = (size_t) file_stat.m_uncomp_size;
    void *p = mz_zip_reader_extract_file_to_heap(&zip, file_stat.m_filename, &uncompressed_size, 0);
    if (!p) {
        return;
    } else {
        Object *result = alloc_array_B(vm, (int)uncompressed_size, 0);
        memcpy(result->instance, p, uncompressed_size);
        mz_free(p);
        vm->frames[vm->FP].ret.O = result;
    }
}
void gamavm_VM_getSystemClassLoader(VM *vm, Object *method, VAR *args) {
    vm->frames[vm->FP].ret.O = vm->sysClassLoader;
}

void java_lang_Object_clone(VM *vm, Object *method, VAR *args) {
    Object *result = NULL;
    Object *o = args[0].O;
    
    if(o) {
        VMClass *cls = o->cls->instance;
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

    VMClass *srccls = src->cls->instance;
    VMClass *dstcls = dst->cls->instance;
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
void java_lang_Math_random_D(VM *vm, Object *method, VAR *args) {
    vm->frames[vm->FP].ret.D = rand() / (double)RAND_MAX;
}

void java_lang_Double_toStringImpl(VM *vm, Object *method, VAR *args) {
    char buf[21];
    int length = snprintf(buf,20,"%g",args[0].D);
    vm->frames[vm->FP].ret.O = alloc_string_ascii(vm, buf, 0);
}

void java_lang_Float_toStringImpl(VM *vm, Object *method, VAR *args) {
    char buf[21];
    int length = snprintf(buf,20,"%g",args[0].F);
    vm->frames[vm->FP].ret.O = alloc_string_ascii(vm, buf, 0);
}

void java_lang_Float_intBitsToFloat(VM *vm, Object *method, VAR *args) {
    float *f = (float*)&args[0].I;
    vm->frames[vm->FP].ret.F = *f;
}

void java_lang_ClassLoader_defineClass(VM *vm, Object *method, VAR *args) {
    Object *loader = args[0].O;
    Object *name = args[1].O;
    Object *array = args[2].O;
    JINT offset = args[3].I;
    JINT len = args[4].I;
    
    vm->frames[vm->FP].ret.O = NULL;
    
    if(!loader || !name || !array) {
        throw_null(vm);
        return;
    }
    
    if(offset < 0 || offset >= array->length) {
        throw_arraybounds(vm, offset, array->length);
        return;
    }
    
    Object *cls = alloc_class(vm);
    if(!parse_class(vm, loader, array->instance+offset, cls)) {
        throw_classnotfound(vm, STRCHARS(name), STRLEN(name));
        return;
    }
    
    CLS(cls, clsLoader) = loader;
    ClassLoader *cl = loader->instance;
    CLS(cls, next) = cl->classes;
    cl->classes = cls;
    
    link_class(vm, cls);
    
    vm->frames[vm->FP].ret.O = cls;
}

void java_lang_reflect_Method_invoke(VM *vm, Object *method, VAR *args) {
    Object *mo = args[0].O;
    Method *m = mo->instance;
    int argCount = m->argCount;
    
    Object *base = args[1].O;
    VAR rargs[argCount];
    int ptr = 0;
    if(!IS_STATIC(m->flags)) {
        if(!base) {
            throw_null(vm);
            return;
        }
        rargs[ptr++].O = base;
    }
    
    Object *arr = args[2].O;
    
    if(arr) {
        Object **vals = arr->instance;
        for(int i=0; i<arr->length; i++) {
            switch(m->argMap[i].sign) {
                case 'B': rargs[ptr].I = vals[i] ? *FIELD_PTR_B(vals[i], 0) : 0;break;
                case 'Z': rargs[ptr].I = vals[i] ? *FIELD_PTR_Z(vals[i], 0) : 0;break;
                case 'C': rargs[ptr].I = vals[i] ? *FIELD_PTR_C(vals[i], 0) : 0;break;
                case 'S': rargs[ptr].I = vals[i] ? *FIELD_PTR_S(vals[i], 0) : 0;break;
                case 'I': rargs[ptr].I = vals[i] ? *FIELD_PTR_I(vals[i], 0) : 0;break;
                case 'F': rargs[ptr].F = vals[i] ? *FIELD_PTR_F(vals[i], 0) : 0;break;
                case 'J': rargs[ptr].J = vals[i] ? *FIELD_PTR_J(vals[i], 0) : 0;break;
                case 'D': rargs[ptr].D = vals[i] ? *FIELD_PTR_D(vals[i], 0) : 0;break;
                default: rargs[ptr].O = vals[i];
            }
            ptr++;
        }
    }
    
    CALLVM_V(vm, mo, &rargs[0]);
    if(!vm->exception) {
        static Object **box_classes = NULL;
        if(!box_classes) {
            box_classes = malloc(sizeof(Object*) * 8);
            box_classes[0] = resolve_class(vm, vm->sysClassLoader, L"java/lang/Byte", 14, 1, NULL);
            box_classes[1] = resolve_class(vm, vm->sysClassLoader, L"java/lang/Boolean", 17, 1, NULL);
            box_classes[2] = resolve_class(vm, vm->sysClassLoader, L"java/lang/Character", 19, 1, NULL);
            box_classes[3] = resolve_class(vm, vm->sysClassLoader, L"java/lang/Short", 15, 1, NULL);
            box_classes[4] = resolve_class(vm, vm->sysClassLoader, L"java/lang/Integer", 17, 1, NULL);
            box_classes[5] = resolve_class(vm, vm->sysClassLoader, L"java/lang/Float", 15, 1, NULL);
            box_classes[6] = resolve_class(vm, vm->sysClassLoader, L"java/lang/Long", 14, 1, NULL);
            box_classes[7] = resolve_class(vm, vm->sysClassLoader, L"java/lang/Double", 16, 1, NULL);
            if(vm->exception) {
                free(box_classes);
                return;
            }
        }
        Object *ret = vm->frames[vm->FP].ret.O;
        switch(m->returnSign) {
            case 'B': ret = alloc_object(vm, box_classes[0], 0); *FIELD_PTR_B(ret, 0) = vm->frames[vm->FP].ret.I;break;
            case 'Z': ret = alloc_object(vm, box_classes[1], 0); *FIELD_PTR_Z(ret, 0) = vm->frames[vm->FP].ret.I;break;
            case 'C': ret = alloc_object(vm, box_classes[2], 0); *FIELD_PTR_C(ret, 0) = vm->frames[vm->FP].ret.I;break;
            case 'S': ret = alloc_object(vm, box_classes[3], 0); *FIELD_PTR_S(ret, 0) = vm->frames[vm->FP].ret.I;break;
            case 'I': ret = alloc_object(vm, box_classes[4], 0); *FIELD_PTR_I(ret, 0) = vm->frames[vm->FP].ret.I;break;
            case 'F': ret = alloc_object(vm, box_classes[5], 0); *FIELD_PTR_F(ret, 0) = vm->frames[vm->FP].ret.F;break;
            case 'J': ret = alloc_object(vm, box_classes[6], 0); *FIELD_PTR_J(ret, 0) = vm->frames[vm->FP].ret.J;break;
            case 'D': ret = alloc_object(vm, box_classes[7], 0); *FIELD_PTR_D(ret, 0) = vm->frames[vm->FP].ret.D;break;
        }
        
        vm->frames[vm->FP].ret.O = ret;
    }
}

extern void java_lang_System_SystemOutStream_printImpl(VM *vm, Object *method, VAR *args);

NativeMethodInfo vm_native_methods[] = {
    {"gamavm/VM:getClass:(Ljava/lang/Object;)Ljava/lang/Class;", &gamavm_VM_getClass},
    {"gamavm/VM:getAddress:(Ljava/lang/Object;)J", &gamavm_VM_getAddress},
    {"gamavm/VM:allocObject:(Ljava/lang/Class;)Ljava/lang/Object;", &gamavm_VM_allocObject},
    {"gamavm/VM:wrapBytes:(JI)[B", &gamavm_VM_wrapBytes},
    {"gamavm/VM:freeMem:(J)V", &gamavm_VM_freeMem},
    {"gamavm/VM:extractZip:(Ljava/lang/String;[BI)[B", &gamavm_VM_extractZip},
    {"gamavm/VM:getSystemClassLoader:()Ljava/lang/ClassLoader;", &gamavm_VM_getSystemClassLoader},

    {"java/lang/Object:clone:()Ljava/lang/Object;", &java_lang_Object_clone},
    
    {"java/lang/System:arraycopy:(Ljava/lang/Object;ILjava/lang/Object;II)V", &java_lang_System_arraycopy},
    {"java/lang/System$SystemOutStream:printImpl:(Ljava/lang/String;)V", &java_lang_System_SystemOutStream_printImpl},
    {"java/lang/System:gc:()V", &java_lang_System_gc},
    {"java/lang/System:nanoTime:()J", &java_lang_System_nanoTime},
    {"java/lang/System:currentTimeMillis:()J", &java_lang_System_currentTimeMillis},

    {"java/lang/Float:toStringImpl:(FZ)Ljava/lang/String;", &java_lang_Float_toStringImpl},

    {"java/lang/Double:toStringImpl:(DZ)Ljava/lang/String;", &java_lang_Double_toStringImpl},

    {"java/lang/Math:random:()D", &java_lang_Math_random_D},

    {"java/lang/ClassLoader:defineClass:(Ljava/lang/String;[BII)Ljava/lang/Class;", &java_lang_ClassLoader_defineClass},

    {"java/lang/reflect/Method:invoke:(Ljava/lang/Object;[Ljava/lang/Object;)Ljava/lang/Object;", &java_lang_reflect_Method_invoke},
    NULL
};
