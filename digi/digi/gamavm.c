//
//  gamavm.c
//  digi
//
//  Created by mustafa on 7.06.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#include "gamavm.h"

VM *gamaVM = NULL;


void gamavm_main(char *className, char *methodName, char *signature) {
    gamaVM = vm_alloc(sizeof(VM));
    
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
    int primitiveSizes[9] = {sizeof(jchar),sizeof(jbyte),sizeof(jbool),sizeof(jshort),
        sizeof(jint),sizeof(jfloat),sizeof(jlong),sizeof(jdouble),0
    };
    for(int i=0; i<9; i++) {
        gamaVM->primClasses[i] = alloc_class(gamaVM);
        CLS(gamaVM->primClasses[i], name) = alloc_string_ascii(gamaVM, primitiveNames[i], 1);
        CLS(gamaVM->primClasses[i], primitiveSize) = primitiveSizes[i];
        CLS(gamaVM->primClasses[i], linked) = 1;
        CLS(gamaVM->primClasses[i], next) = gamaVM->classes;
        gamaVM->classes = CLS(gamaVM->primClasses[i], next);
    }
    
    resolve_class(gamaVM, L"java/lang/Object", 16, 0, gamaVM->jlObject);
    resolve_class(gamaVM, L"java/lang/Class", 15, 0, gamaVM->jlClass);
    resolve_class(gamaVM, L"java/lang/reflect/Field", 23, 0, gamaVM->jlField);
    resolve_class(gamaVM, L"java/lang/reflect/Method", 24, 0, gamaVM->jlMethod);
    resolve_class(gamaVM, L"java/lang/StackTraceElement", 27, 0, gamaVM->jlSTE);
    resolve_class(gamaVM, L"java/lang/String", 16, 0, gamaVM->jlString);
    
    int clsLen;
    jchar *clName = char_to_jchar(className, &clsLen);
    int nameLen;
    jchar *name = char_to_jchar(methodName, &nameLen);
    int signLen;
    jchar *sign = char_to_jchar(signature, &signLen);
    
    gamaVM->mainMethod = resolve_method(gamaVM, clName, clsLen, name, nameLen, sign, signLen);
    if(!gamaVM->mainMethod) {
        printf("Can't find main method: %s:%s:%s\n", className, methodName, signature);
        return;
    }
    
    CALLVM_V(gamaVM, gamaVM->mainMethod, NULL);
}
