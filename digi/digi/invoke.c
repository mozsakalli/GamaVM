//
//  invoke.c
//  digi
//
//  Created by mustafa on 10.06.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#include "vm.h"

void invoke_interface_v(VM* vm, Object *method, VAR *args) {
    if(!method) {
        throw_null(vm);
        return;
    }
    Method *m = method->instance;
    Object *object = args[0].O;
    if(!object) {
        throw_null(vm);
        return;
    }
    Object *imethod = CLS(object->cls,itable)[m->iTableIndex];
    if(!imethod) {
        printf("Invalid interface call!!!\n");
        return;
    }
    ((VM_CALL)((Method*)imethod->instance)->entry)(vm, imethod, args);
}
