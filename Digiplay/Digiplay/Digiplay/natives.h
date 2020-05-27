//
//  natives.h
//  Digiplay
//
//  Created by mustafa on 23.05.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#ifndef natives_h
#define natives_h

#include "jvm.h"

void java_lang_System_arraycopy(VM *vm, Object *method, VAR *args);
void java_lang_System_SystemOutStream_printImpl(VM *vm, Object *method, VAR *args);
void java_lang_System_currentTimeMillis(VM *vm, Object *method, VAR *args);

extern NativeMethodInfo NATIVES[];


#endif /* natives_h */
