//
//  natives.c
//  Digiplay
//
//  Created by mustafa on 23.05.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#include "natives.h"
#import <UIKit/UIKit.h>
#include <sys/time.h>
#include <time.h>
#ifdef __APPLE__
#include <mach/mach_time.h>
#endif
#import <objc/runtime.h>
#import <Metal/Metal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

void java_lang_Object_clone(VM *vm, Object *method, VAR *args) {
    void *result = NULL;
    
    Object *o = args[0].O;
    if(o) {
        ClassFields *cls = o->cls->instance;
        if(cls->elementClass) {
            Object *arr = o;
            if(CLS_FIELD(cls->elementClass,primitiveType)) {
                Object *na = alloc_prim_array(vm, o->cls, arr->length);
                memcpy(na->instance, arr->instance, arr->length * CLS_FIELD(cls->elementClass,instanceSize));
                result = na;
            } else {
                Object *na = alloc_object_array(vm, o->cls, arr->length);
                memcpy(na->instance, arr->instance, arr->length * sizeof(Object*));
                result = na;
            }
        } else {
            Object *or = alloc_object(vm, o->cls);
            if(or->instance)
                memcpy(or->instance, o->instance, cls->instanceSize);
            result = or;
        }
    }
    
    vm->frames[vm->FP].retVal.O = result;
}

void java_lang_System_arraycopy(VM *vm, Object *method, VAR *args) {
    Object *src = args[0].O;
    jint srcOffset = args[1].I;
    Object *dst = args[2].O;
    jint dstOffset = args[3].I;
    jint length = args[4].I;
    
    if(src == NULL || dst == NULL) {
 // || src->cls->elementClass == NULL || dst->cls->elementClass == NULL
        throw_nullpointerexception(vm);
        return;
    }
    
    if(srcOffset < 0 || dstOffset < 0 || srcOffset + length > src->length || dstOffset + length > dst->length) {
        throw_arrayboundsexception(vm, srcOffset, length);
        return;
    }

    ClassFields *srccls = src->cls->instance;
    ClassFields *dstcls = dst->cls->instance;
    if(!srccls->elementClass || !dstcls->elementClass) {
        //both must be array
        return;
    }
    //todo: check if compatible
    if(CLS_FIELD(srccls->elementClass,primitiveType) != 0 || CLS_FIELD(srccls->elementClass,primitiveType) != 0) {
        if(CLS_FIELD(srccls->elementClass,primitiveType) != CLS_FIELD(dstcls->elementClass,primitiveType)) {
            throw_nullpointerexception(vm);
            return;
        }
        memmove(dst->instance, src->instance, length * CLS_FIELD(srccls->elementClass,instanceSize));
    } else {
        memmove(dst->instance, src->instance, length * sizeof(ObjectPtr));
    }
}

void java_lang_System_currentTimeMillis(VM *vm, Object *method, VAR *args) {
    struct timeval now;
    gettimeofday(&now, NULL);
    
    vm->frames[vm->FP].retVal.J = now.tv_sec * 1000LL + now.tv_usec / 1000;
}

extern void gc_step(VM *vm);
void java_lang_System_gc(VM *vm, Object *method, VAR *args) {
    gc_step(vm);
}

void java_lang_System_SystemOutStream_printImpl(VM *vm, Object *method, VAR *args) {
    Object *stro = args[0].O;
    if(!stro) return;
    
    StringFields *str = stro->instance;
    NSString *ns = str->__native;
    if(!ns) {
        jchar *chars = (jchar*)str->chars->instance + str->start;
        ns = [[NSString alloc] initWithCharacters:chars length:str->length];
    }
    NSLog(@"%@", ns);
    if(!str->__native)
        [ns dealloc];
}

void java_lang_System_nanoTime(VM *vm, Object *method, VAR *args) {
    long result = 0;
    #if defined(__APPLE__)
        mach_timebase_info_data_t info;
        mach_timebase_info(&info);
        uint64_t t = mach_absolute_time();
        t *= info.numer;
        t /= info.denom;
        vm->frames[vm->FP].retVal.J = (jlong)t;
    #else
        struct timespec now;\n
        clock_gettime(CLOCK_MONOTONIC, &now);
        vm->frames[vm->FP].retVal.J = now.tv_sec * 1000000000LL + now.tv_nsec;
    #endif
}

void gamavm_VM_getClass(VM *vm, Object *method, VAR *args) {
    vm->frames[vm->FP].retVal.O = args[0].O ? (Object*)args[0].O->cls : NULL;
}
void gamavm_VM_getAddress(VM *vm, Object *method, VAR *args) {
    vm->frames[vm->FP].retVal.J = (jlong)args[0].O;
}

void java_lang_Math_abs_D(VM *vm, Object *method, VAR *args) {
    jdouble v = args[0].D;
    if(v < 0) v = -v;
    vm->frames[vm->FP].retVal.D = v;
}
void java_lang_Math_abs_F(VM *vm, Object *method, VAR *args) {
    jfloat v = args[0].F;
    if(v < 0) v = -v;
    vm->frames[vm->FP].retVal.F = v;
}

void java_lang_Double_toStringImpl(VM *vm, Object *method, VAR *args) {
    jdouble d = args[0].D;
    jint b = args[1].I;
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
    jint inside=0;
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
    vm->frames[vm->FP].retVal.O = (Object*)alloc_string(vm, s);
}

void java_lang_Float_toStringImpl(VM *vm, Object *method, VAR *args) {
    char s[32];
    jfloat d = args[0].F;
    jint b = args[1].I;
    if ( !b ){
        sprintf(s, "%f", d);
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
    jint inside=0;
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
    
    vm->frames[vm->FP].retVal.O = (Object*)alloc_string(vm, s);
}

jlong get_nsobject_handle(VM *vm, Object *o) {
    static int handle_field_offset = -1;
    if(handle_field_offset == -1) {
        Object *field = resolve_field(vm, "gamavm/apple/NSObject", "handle", 0);
        if(vm->exception || !field) return 0;
        handle_field_offset = ((FieldFields*)field->instance)->offset;
    }
    
    return *FIELD_PTR_J(o, handle_field_offset);
}
void set_nsobject_handle(VM *vm, Object *o, jlong value) {
    static int handle_field_offset = -1;
    if(handle_field_offset == -1) {
        Object *field = resolve_field(vm, "gamavm/apple/NSObject", "handle", 0);
        if(vm->exception || !field) return;
        handle_field_offset = ((FieldFields*)field->instance)->offset;
    }
    
    *FIELD_PTR_J(o, handle_field_offset) = value;
}

void gamavm_apple_ObjC_sel_registerName(VM *vm, Object *method, VAR *args) {
    jlong ret = 0;
    if(args[0].O) {
        SEL sel = sel_registerName((const char*)string2c(args[0].O));
        ret = (jlong)(__bridge void *)(sel);
    }
    vm->frames[vm->FP].retVal.J = ret;
}

void gamavm_apple_ObjC_objc_getClass(VM *vm, Object *method, VAR *args) {
    jlong ret = 0;
    if(args[0].O) {
        id cls = objc_getClass((const char*)string2c(args[0].O));
        ret = (jlong)(__bridge void *)(cls);
    }
    vm->frames[vm->FP].retVal.J = ret;
}

#define HANDLENUMBERTYPES(F, index)            \
F('c', char, numberWithChar, charValue, index); \
F('i', int, numberWithInt, intValue, index); \
F('s', short, numberWithShort, shortValue, index); \
F('l', long, numberWithLong, longValue, index); \
F('q', long long, numberWithLongLong, longLongValue, index); \
F('C', unsigned char, numberWithUnsignedChar, unsignedCharValue, index); \
F('I', unsigned int, numberWithUnsignedInt, unsignedIntValue, index); \
F('S', unsigned short, numberWithUnsignedShort, unsignedShortValue, index); \
F('L', unsigned long, numberWithUnsignedLong, unsignedLongValue, index); \
F('Q', unsigned long long, numberWithUnsignedLongLong, unsignedLongLongValue, index); \
F('f', float, numberWithFloat, floatValue, index); \
F('d', double, numberWithDouble, doubleValue, index); \
F('B', _Bool, numberWithBool, boolValue, index)

void objc_to_java(VM *vm, const char *type, void *buffer, VAR *result, int is_long) {
    switch(type[0]) {
        case '@': // An object (whether statically typed or typed id)
        {
            id x = (__bridge id)*((void **)buffer);
            //            NSLog(@"stack %@", stack);
            if (x) {
                if(is_long) result->J = (jlong)x;
            } else {
                if(is_long) result->J = 0; else result->D = 0;
            }
        }
        break;
            
        default:
            printf("!!!!!!!! Unknown OBJC Type: %c !!!!!!!!!\n", type[0]);
            break;
    }
#define CNVBUF(type) type x = *(type*)buffer
#define PUSHNUMBERTYPE(ch, type, nummethod, valmethod, index) \
case ch: \
    { \
        CNVBUF(type); \
        [stack addObject:[NSNumber nummethod:x]]; \
    } \
    break
}

//https://github.com/torus/Lua-Objective-C-Bridge/blob/master/LuaBridge.m
void gamavm_apple_ObjC_callObject(VM *vm, Object *method, VAR *args) {
    if(!args[0].O || !args[1].O || !args[2].O) {
        throw_nullpointerexception(vm);
        return;
    }
    id target = (id)get_nsobject_handle(vm,args[0].O);
    if(vm->exception) return;

    SEL sel = (SEL)get_nsobject_handle(vm,args[1].O);
    if(vm->exception) return;
    
    NSMethodSignature *sig = [target methodSignatureForSelector:sel];
    NSInvocation *inv = [NSInvocation invocationWithMethodSignature:sig];
    [inv retainArguments];
    NSUInteger numarg = [sig numberOfArguments] - 2;
    
    Object *params = args[3].O;
    if(!params || params->length != numarg) {
        throw_nullpointerexception(vm);
        //[inv dealloc];
        //[sig dealloc];
        return;
    }
    
    for (int i = 0; i < numarg; i++) {
        const char *t = [sig getArgumentTypeAtIndex:i+2];
    }
    
    [inv setTarget:target];
    [inv setSelector:sel];
    [inv invoke];
    
    const char *rettype = [sig methodReturnType];
    if(rettype[0] == '@') {
        NSUInteger len = [[inv methodSignature] methodReturnLength];
        void *buffer = malloc(len);
        [inv getReturnValue:buffer];
        jlong handle = 0;
        id x = (__bridge id)*((void **)buffer);
        if (x) handle = (jlong)x;
        free(buffer);
        
        if(handle != 0) {
            Object *ret = alloc_object(vm, args[2].O);
            set_nsobject_handle(vm, ret, handle);
            vm->frames[vm->FP].retVal.O = ret;
        } else {
            vm->frames[vm->FP].retVal.O = NULL;
        }
    } else {
        throw_nullpointerexception(vm);
    }
    //[inv dealloc];
    //[sig dealloc];
}


extern void digiplay_ios_IosPlatform_run(VM *vm, Object *method, VAR *args);

NativeMethodInfo gamavm_natives[] = {
    //java/lang/Object
    {.cls = "java/lang/Object", .name = "clone", .sign = "()Ljava/lang/Object;", .handle = &java_lang_Object_clone},

    //java/lang/System
    {.cls = "java/lang/System", .name = "arraycopy", .sign = "(Ljava/lang/Object;ILjava/lang/Object;II)V", .handle = &java_lang_System_arraycopy},
    {.cls = "java/lang/System", .name = "currentTimeMillis", .sign = "()J", .handle = &java_lang_System_currentTimeMillis},
    {.cls = "java/lang/System", .name = "nanoTime", .sign = "()J", .handle = &java_lang_System_nanoTime},
    {.cls = "java/lang/System", .name = "gc", .sign = "()V", .handle = &java_lang_System_gc},
    {.cls = "java/lang/System$SystemOutStream", .name = "printImpl", .sign = "(Ljava/lang/String;)V", .handle = &java_lang_System_SystemOutStream_printImpl},

    //gamavm/VM
    {.cls = "gamavm/VM", .name = "getClass", .sign = "(Ljava/lang/Object;)Ljava/lang/Class;", .handle = &gamavm_VM_getClass},
    {.cls = "gamavm/VM", .name = "getAddress", .sign = "(Ljava/lang/Object;)J", .handle = &gamavm_VM_getAddress},

    //java/lang/Math
    {.cls = "java/lang/Math", .name = "abs", .sign = "(D)D", .handle = &java_lang_Math_abs_D},
    {.cls = "java/lang/Math", .name = "abs", .sign = "(F)F", .handle = &java_lang_Math_abs_F},

    //java/lang/Double
    {.cls = "java/lang/Double", .name = "toStringImpl", .sign = "(DZ)Ljava/lang/String;", .handle = &java_lang_Double_toStringImpl},

    //java/lang/Float
    {.cls = "java/lang/Float", .name = "toStringImpl", .sign = "(FZ)Ljava/lang/String;", .handle = &java_lang_Float_toStringImpl},

    {.cls = "gamavm/apple/ObjC", .name = "objc_getClass", .sign = "(Ljava/lang/String;)J", .handle = &gamavm_apple_ObjC_objc_getClass},
    {.cls = "gamavm/apple/ObjC", .name = "sel_registerName", .sign = "(Ljava/lang/String;)J", .handle = &gamavm_apple_ObjC_sel_registerName},
    {.cls = "gamavm/apple/ObjC", .name = "callObject", .sign = "(Lgamavm/apple/NSObject;Lgamavm/apple/Selector;Ljava/lang/Class;[Ljava/lang/Object;)Lgamavm/apple/NSObject;", .handle = &gamavm_apple_ObjC_callObject},

    //{.cls = "gamavm/apple/uikit/UIApplication", .name = "main", .sign = "(Lgamavm/apple/uikit/UIApplicationDelegate;)V", .handle = &gamavm_apple_uikit_UIApplication_main},
    {.cls = "digiplay/ios/IosPlatform", .name = "run", .sign = "()V", .handle = &digiplay_ios_IosPlatform_run},

    {.cls = NULL}
};

extern NativeMethodInfo digiplay_GL_NATIVES[];

void* find_native_method(NativeMethodInfo *ptr, Object *cls, Object *name, Object *sign) {
    while (ptr && ptr->cls) {
        if(compare_string_cstring(cls, ptr->cls) &&
           compare_string_cstring(name, ptr->name) &&
           compare_string_cstring(sign, ptr->sign)) {
            return ptr->handle;
        }
        ptr++;
    }
    return NULL;
}

void* resolve_native_method(VM *vm, Object *method) {
    Object *name = MTH_FIELD(method, name);
    Object *sign = MTH_FIELD(method, signature);
    Object *cls = CLS_FIELD(MTH_FIELD(method, declaringClass), name);
    void *ret = find_native_method(&gamavm_natives[0], cls, name, sign);
    if(ret) return ret;
    ret = find_native_method(&digiplay_GL_NATIVES[0], cls, name, sign);
    if(ret) return ret;

    return NULL;
}


