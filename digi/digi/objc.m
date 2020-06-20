//
//  objc.m
//  digi
//
//  Created by mustafa on 20.06.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//
#import <Foundation/Foundation.h>
#include "vm.h"

#define JNIARRAY_B  0
#define JNIARRAY_Z  1
#define JNIARRAY_C  2
#define JNIARRAY_S  3
#define JNIARRAY_I  4
#define JNIARRAY_F  5
#define JNIARRAY_J  6
#define JNIARRAY_D  7

typedef struct JNIMethodInfo {
    SEL selector;
    Class objcClass;
    
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
        *cls = resolve_class(vm, sign + start, ptr - start, 1, nil);
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

Class getObjcClass(VMClass *cls) {
    char namechars[256];
    int len = snprintf(namechars,255,"%s", string_to_ascii(cls->name));
    for(int i=0; i<len; i++) if(namechars[i] == '/' || namechars[i] == '.') namechars[i] = '_';
    return NSClassFromString([[NSString alloc] initWithUTF8String:namechars]);
}

void gama_to_objc(VM *vm, char type, Object *cls, VAR *a, void **j) {
    /*
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
    }*/
}
void vm_invoke_objc(VM *vm, Object *method, VAR *args) {
    Method *m = (Method*)method->instance;
    JNIMethodInfo *mi = (JNIMethodInfo*)m->externalData;
    VAR *a = args;
    id target = nil;

    int isStatic = IS_STATIC(m->flags);
    if(!isStatic) {
        a++;
    } else {
        target = mi->objcClass;
    }
    
    
    NSMethodSignature *sig = [target methodSignatureForSelector:mi->selector];
    NSInvocation *inv = [NSInvocation invocationWithMethodSignature:sig];
    [inv retainArguments];
    NSUInteger numarg = [sig numberOfArguments];
    for (int i = 2; i < numarg; i++) {
        const char *t = [sig getArgumentTypeAtIndex:i];
        switch(t[0]) {
            case '@': {
                if(!a->O) {
                    id n = nil;
                    [inv setArgument:&n atIndex:i];
                } else {
                    NSString *str = [[NSString alloc] initWithCharacters:STRCHARS(a->O) length:STRLEN(a->O)];
                    [inv setArgument:&str atIndex:i];
                }
            } break;
            default:
                printf("!!!!!!!!!!!!!!!!!!! Unknown objc type: %c\n", t[0]);
        }
    }
    
    [inv setTarget:target];
    [inv setSelector:mi->selector];
    [inv invoke];
    
    VAR *ret = &vm->frames[vm->FP].ret;
    void *buffer = NULL;
    const char *rettype = [sig methodReturnType];
    if (rettype[0] != 'v') { // don't get return value from void function
        NSUInteger len = [[inv methodSignature] methodReturnLength];
        buffer = malloc(len);
        [inv getReturnValue:buffer];
    }
    switch(mi->returnType) {
        case 'I': ret->I = *(int*)buffer; free(buffer); break;
        case JNIARRAY_B: {
            NSData *x = (__bridge id)*((void **)buffer);
            if(x) {
                ret->O = alloc_array_B(vm, (int)[x length], 0);
                memcpy(ret->O->instance, [x bytes], [x length]);
                [x release];
            } else ret->O = nil;
        } break;
    }
    
    
    /*
    jvalue jvals[32];
    for(int i=0; i<mi->argCount; i++) {
        gama_to_jni(vm, env, mi->argTypes[i], mi->argClasses[i], a, &jvals[i]);
        a++;
    }*/

}

JNIMethodInfo *vm_build_external_method(VM *vm, Object *method, SEL sel) {
    Method *m = method->instance;
    JNIMethodInfo *mi = (JNIMethodInfo*)malloc(sizeof(JNIMethodInfo));
    mi->selector = sel;
    mi->argCount = 0;
    JCHAR *sign = STRCHARS(m->signature);
    int ptr = 1;
    while(sign[ptr] != ')') {
        ptr = jni_parse_signature(vm, sign, ptr, &mi->argTypes[mi->argCount], &mi->argClasses[mi->argCount]);
        if(vm->exception) {
            free(mi);
            return NULL;
        }
        mi->argCount++;
    }
    ptr++;
    jni_parse_signature(vm, sign, ptr, &mi->returnType, &mi->returnClass);

    return mi;
}
void vm_resolve_objc(VM *vm, Object *method, VAR *args) {
    Method *m = method->instance;
    VMClass *cls = m->declaringClass->instance;
    Class objcClass = getObjcClass(cls);
    char selname[256];
    char *sptr = selname;
    sptr += sprintf(selname, "%s", string_to_ascii(m->name));
    if(m->argCount > 0) sptr += sprintf(sptr, ":");
    SEL sel = NSSelectorFromString([[NSString alloc] initWithUTF8String:selname]);
    if(!sel) {
        return;
    }
    
    if(IS_STATIC(m->flags)) {
        if([objcClass respondsToSelector:sel]) {
            JNIMethodInfo *mi = vm_build_external_method(vm, method, sel);
            mi->objcClass = objcClass;
            m->externalData = mi;
            m->entry = &vm_invoke_objc;
            vm_invoke_objc(vm, method, args);
        }
    }
}

void vm_link_external_class(VM *vm, Object *clsObject) {
    VMClass *cls = (VMClass*)clsObject->instance;
    Class objcClass = getObjcClass(cls);
    if(!objcClass) {
        return;
    }
    if(cls->methods) {
        for(int i=0; i<cls->methods->length; i++) {
            Method *m = (Method*)ARRAY_DATA_O(cls->methods)[i]->instance;
            if(IS_NATIVE(m->flags) && m->externalFlags != 0) m->entry = &vm_resolve_objc;
        }
    }
    /*
    VMClass *cls = (VMClass*)clsObject->instance;
    char namechars[256];
    char signchars[256];
    int len = snprintf(namechars,255,"%s", string_to_ascii(cls->name));
    for(int i=0; i<len; i++) if(namechars[i] == '/' || namechars[i] == '.') namechars[i] = '_';
    Class objcClass = NSClassFromString([[NSString alloc] initWithUTF8String:namechars]);
    if(!objcClass) {
        return;
    }
    
    if(cls->methods) {
        JNIMethodInfo *mi = malloc(sizeof(JNIMethodInfo));
        memset(mi, 0, sizeof(JNIMethodInfo));
        
        for(int i=0; i<cls->methods->length; i++) {
            Method *m = (Method*)ARRAY_DATA_O(cls->methods)[i]->instance;
            char *ptr = namechars;
            ptr += sprintf(ptr, "%s", string_to_ascii(m->name));
            for(int i=0; i<m->argCount; i++) {
                ptr += sprintf(ptr, ":%s")
            }
            //snprintf(ptr, 255, "%s", )
        }
    }
    //NSSelectorFromString(<#NSString * _Nonnull aSelectorName#>)
    /*
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
    }*/
}
