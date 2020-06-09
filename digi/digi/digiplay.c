//
//  digiplay.c
//  digi
//
//  Created by mustafa on 9.06.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#include "vm.h"

extern void digiplay_Platform_run(VM *vm, Object *method, VAR *args);

NativeMethodInfo digiplay_native_methods[] = {
    {"digiplay/Platform:run:()V", &digiplay_Platform_run},
    NULL
};
