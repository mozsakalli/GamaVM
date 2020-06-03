//
//  digiplay_opengl.c
//  Digiplay
//
//  Created by mustafa on 3.06.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#include <stdio.h>
#include "jvm.h"

#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

void ogl_digiplay_GL_viewport(VM *vm, Object *method, VAR *args) {
    glViewport(args[0].I, args[1].I, args[2].I, args[3].I);
}

void ogl_digiplay_GL_clearColor(VM *vm, Object *method, VAR *args) {
    glClearColor(args[0].F, args[1].F, args[2].F, args[3].F);
}

void ogl_digiplay_GL_clear(VM *vm, Object *method, VAR *args) {
    glClear(args[0].I);
}

#define GL "digiplay/GL"
NativeMethodInfo digiplay_GL_NATIVES[] = {
    {.cls = GL, .name = "viewport", .sign = "(IIII)V", .handle = &ogl_digiplay_GL_viewport},
    {.cls = GL, .name = "clearColor", .sign = "(FFFF)V", .handle = &ogl_digiplay_GL_clearColor},
    {.cls = GL, .name = "clear", .sign = "(I)V", .handle = &ogl_digiplay_GL_clear},

    {.cls = NULL}
};
