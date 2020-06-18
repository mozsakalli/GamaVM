//
//  gamavm.c
//  digi
//
//  Created by mustafa on 7.06.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#include "vm.h"


VM* vm_init() {
    VM *gamaVM = vm_alloc(sizeof(VM));
    
    gamaVM->jlClass = vm_alloc(sizeof(Object));
    gamaVM->jlClass->gc.atomic = 1;
    Class *cls = gamaVM->jlClass->instance = vm_alloc(sizeof(Class));
    cls->instanceSize = sizeof(Class);
    
    gamaVM->jlObject = alloc_class(gamaVM);
    
    gamaVM->jlMethod = alloc_class(gamaVM);
    CLS(gamaVM->jlMethod, instanceSize) = sizeof(Method);
    
    gamaVM->jlField = alloc_class(gamaVM);
    CLS(gamaVM->jlField, instanceSize) = sizeof(Field);
    
    gamaVM->jlString = alloc_class(gamaVM);
    CLS(gamaVM->jlString, instanceSize) = sizeof(String);
    
    gamaVM->jlSTE = alloc_class(gamaVM);
    CLS(gamaVM->jlSTE, instanceSize) = sizeof(StackTraceElement);
    
    //Setup primitive classes
    char *primitiveNames[9] = {"C","B","Z","S","I","F","J","D","V"};
    int primitiveSizes[9] = {sizeof(JCHAR),sizeof(JBYTE),sizeof(JBOOL),sizeof(JSHORT),
        sizeof(JINT),sizeof(JFLOAT),sizeof(JLONG),sizeof(JDOUBLE),0
    };
    for(int i=0; i<9; i++) {
        gamaVM->primClasses[i] = alloc_class(gamaVM);
        CLS(gamaVM->primClasses[i], name) = alloc_string_ascii(gamaVM, primitiveNames[i], 1);
        CLS(gamaVM->primClasses[i], primitiveSize) = primitiveSizes[i];
        CLS(gamaVM->primClasses[i], linked) = 1;
        CLS(gamaVM->primClasses[i], next) = gamaVM->classes;
        gamaVM->classes = gamaVM->primClasses[i];
    }
    
    resolve_class(gamaVM, L"java/lang/Object", 16, 0, gamaVM->jlObject);
    resolve_class(gamaVM, L"java/lang/Class", 15, 0, gamaVM->jlClass);
    resolve_class(gamaVM, L"java/lang/reflect/Field", 23, 0, gamaVM->jlField);
    resolve_class(gamaVM, L"java/lang/reflect/Method", 24, 0, gamaVM->jlMethod);
    resolve_class(gamaVM, L"java/lang/StackTraceElement", 27, 0, gamaVM->jlSTE);
    resolve_class(gamaVM, L"java/lang/String", 16, 0, gamaVM->jlString);

    return gamaVM;
}

void vm_main(VM *vm, char *className, char *methodName, char *signature) {
    int clsLen;
    JCHAR *clName = char_to_jchar(className, &clsLen);
    int nameLen;
    JCHAR *name = char_to_jchar(methodName, &nameLen);
    int signLen;
    JCHAR *sign = char_to_jchar(signature, &signLen);
    
    vm->mainMethod = resolve_method(vm, clName, clsLen, name, nameLen, sign, signLen);
    if(!vm->mainMethod) {
        printf("Can't find main method: %s:%s:%s\n", className, methodName, signature);
        free(clName);
        free(name);
        free(sign);
        return;
    }
    jdwp_start(vm, "192.168.1.40", 8080);
    
    CALLVM_V(vm, vm->mainMethod, NULL);
    free(clName);
    free(name);
    free(sign);
}

void vm_destroy(VM *vm) {
#define F(m) if(m) free(m)
    while(vm->classes) {
        Object *clso = vm->classes;
        Class *cls = (Class*)clso->instance;
        F(cls->allParents);
        F(cls->cp);
        F(cls->global);
        F(cls->instanceOffsets);
        F(cls->itable);
        F(cls->vtable);
        if(cls->fields) {
            for(int i=0; i<cls->fields->length; i++) {
                Object *f = ARRAY_DATA_O(cls->fields)[i];
                F(f->instance);
                F(f);
            }
            F(cls->fields);
        }
        if(cls->methods) {
            for(int i=0; i<cls->methods->length; i++) {
                Object *mo = ARRAY_DATA_O(cls->methods)[i];
                Method *m = mo->instance;
                F(m->argMap);
                F(m->catchTable);
                F(m->code);
                F(m->compiled);
                F(m->lineNumberTable);
                F(m->localVarTable);
                F(mo->instance);
                F(mo);
            }
            F(cls->methods);
        }
        F(clso->instance);
        F(clso);
        vm->classes = CLS(vm->classes, next);
    }
    
    while(vm->strings) {
        Object *str = vm->strings;
        vm->strings = STR(vm->strings, next);
        F(STR(str,chars)->instance);
        F(STR(str,chars));
        F(str->instance);
        F(str);
    }
    
    while(vm->heap) {
        HeapBlock *h = vm->heap;
        vm->heap = vm->heap->next;
        for(int i=0; i<HEAP_OBJECTS_PER_BLOCK; i++) {
            if(!h->objects[i].gc.free)
                F(h->objects[i].instance);
        }
        F(h);
    }
    F(vm);
}
