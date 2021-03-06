//
//  natives.c
//  digi
//
//  Created by mustafa on 8.06.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#include "vm.h"

void vm_native_exec(VM *vm, Object *method, VAR *args) {
    void *handler = resolve_native_method(vm, method);
    if(handler) {
        Method *m = method->instance;
        m->entry = handler;
        ((VM_CALL)handler)(vm, method, args);
        return;
    }

    throw_unsatisfiedlink(vm, method);
}

extern NativeMethodInfo vm_native_methods[];
extern NativeMethodInfo digiplay_native_methods[];
extern NativeMethodInfo digiplay_gl_methods[];
extern NativeMethodInfo aot_native_methods[];
extern NativeMethodInfo digiplay_sprite_methods[];

/// EXTRAEXTERNS

void *search_native(NativeMethodInfo* ptr, char *signature) {
    while(ptr && ptr->signature) {
        if(!strcmp(signature, ptr->signature)) return ptr->method;
        ptr++;
    }
    return NULL;
}

void *resolve_native_method0(VM *vm, char *signature) {
    void *result = NULL;
    result = search_native(&vm_native_methods[0], signature); if(result) return result;
    result = search_native(&digiplay_native_methods[0], signature); if(result) return result;
    result = search_native(&digiplay_gl_methods[0], signature); if(result) return result;
    result = search_native(&digiplay_sprite_methods[0], signature); if(result) return result;
    //result = search_native(&aot_native_methods[0], signature); if(result) return result;
    /*
    result = search_native(&aot_native_methods0[0], signature); if(result) return result;
    result = search_native(&aot_native_methods1[0], signature); if(result) return result;
    result = search_native(&aot_native_methods2[0], signature); if(result) return result;
    result = search_native(&aot_native_methods3[0], signature); if(result) return result;
    */
    /// EXTRASEARCH
    return NULL;
}
extern void aot_init(VM *vm);
void *resolve_native_method(VM *vm, Object *method) {
    char tmp[512];
    char *ptr = tmp;
    Method *m = method->instance;
    ptr += sprintf(tmp, "%s:", string_to_ascii(CLS(m->declaringClass, name)));
    ptr += sprintf(ptr, "%s:", string_to_ascii(m->name));
    ptr += sprintf(ptr, "%s", string_to_ascii(m->signature));
    //aot_init(vm);
    return resolve_native_method0(vm, tmp);
}
