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

int ogl_compile_shader(const char *code, int type) {
    int shader = glCreateShader(type);
    glShaderSource(shader, 1, &code, 0);
    glCompileShader(shader);
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE) {
        glDeleteShader(shader);
        shader = 0;
    }
    return shader;
}

void ogl_digiplay_GL_compileProgram(VM *vm, Object *method, VAR *args) {
    long ret = 0;
    if(args[0].O && args[1].O) {
        int vertex = ogl_compile_shader(string2c(args[0].O), GL_VERTEX_SHADER);
        int frag = ogl_compile_shader(string2c(args[1].O), GL_FRAGMENT_SHADER);
        if(!vertex || !frag) {
            ret = !vertex ? -1 : -2;
            glDeleteShader(vertex);
            glDeleteShader(frag);
        } else {
            int prog = glCreateProgram();
            glAttachShader(prog, vertex);
            glAttachShader(prog, frag);
            glLinkProgram(prog);
            glValidateProgram(prog);
            int linked;
            glGetProgramiv(prog, GL_LINK_STATUS, &linked);
            if (linked == GL_FALSE) {
                glDeleteProgram(prog);
                glDeleteShader(vertex);
                glDeleteShader(frag);
            } else ret = prog;
        }
    }
    vm->frames[vm->FP].retVal.J = ret;
}

void ogl_digiplay_GL_attribLocation(VM *vm, Object *method, VAR *args) {
    vm->frames[vm->FP].retVal.J = args[1].O ? glGetAttribLocation(args[0].J, string2c(args[1].O)) : 0;
}
void ogl_digiplay_GL_uniformLocation(VM *vm, Object *method, VAR *args) {
    vm->frames[vm->FP].retVal.J = args[1].O ? glGetUniformLocation(args[0].J, string2c(args[1].O)) : 0;
}
void ogl_digiplay_GL_createVertexBuffer(VM *vm, Object *method, VAR *args) {
    GLuint buf;
    glGenBuffers(1, &buf);
    vm->frames[vm->FP].retVal.J = buf;
}
void ogl_digiplay_GL_bufferVertexData(VM *vm, Object *method, VAR *args) {
    if(args[0].J && args[1].O) {
        int alen = args[1].O->length;
        int start = args[2].I;
        if(start >= alen) return;
        jlong vbo = args[0].J;
        GLvoid *buffer = args[1].O->instance;
        int len = args[3].I;
        if(len == 0) len = alen;
        if(start < 0) start = 0;
        int end = start + len;
        if(end > alen) end = alen;
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, (end - start) * sizeof(float), buffer, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}

void ogl_digiplay_GL_bufferIndexData(VM *vm, Object *method, VAR *args) {
    if(args[0].J && args[1].O) {
        int alen = args[1].O->length;
        int start = args[2].I;
        if(start >= alen) return;
        jlong ibo = args[0].J;
        GLvoid *buffer = args[1].O->instance;
        int len = args[3].I;
        if(len == 0) len = alen;
        if(start < 0) start = 0;
        int end = start + len;
        if(end > alen) end = alen;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (end - start) * sizeof(short), buffer, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}

void ogl_digiplay_GL_useProgram(VM *vm, Object *method, VAR *args) {
    glUseProgram(args[0].J);
}
void ogl_digiplay_GL_enableVertexAttribArray(VM *vm, Object *method, VAR *args) {
    glEnableVertexAttribArray(args[0].J);
}
void ogl_digiplay_GL_disableVertexAttribArray(VM *vm, Object *method, VAR *args) {
    glDisableVertexAttribArray(args[0].J);
}
void ogl_digiplay_GL_vertexAttribPointer(VM *vm, Object *method, VAR *args) {
    glVertexAttribPointer(args[0].J, args[1].I, args[2].I, args[3].I, args[4].I, args[5].I);
}

#define GL "digiplay/GL"
NativeMethodInfo digiplay_GL_NATIVES[] = {
    {.cls = GL, .name = "viewport", .sign = "(IIII)V", .handle = &ogl_digiplay_GL_viewport},
    {.cls = GL, .name = "clearColor", .sign = "(FFFF)V", .handle = &ogl_digiplay_GL_clearColor},
    {.cls = GL, .name = "clear", .sign = "(I)V", .handle = &ogl_digiplay_GL_clear},
    {.cls = GL, .name = "compileProgram", .sign = "(Ljava/lang/String;Ljava/lang/String;)J", .handle = &ogl_digiplay_GL_compileProgram},
    {.cls = GL, .name = "attribLocation", .sign = "(JLjava/lang/String;)J", .handle = &ogl_digiplay_GL_attribLocation},
    {.cls = GL, .name = "uniformLocation", .sign = "(JLjava/lang/String;)J", .handle = &ogl_digiplay_GL_uniformLocation},
    {.cls = GL, .name = "createVertexBuffer", .sign = "()J", .handle = &ogl_digiplay_GL_createVertexBuffer},
    {.cls = GL, .name = "createIndexBuffer", .sign = "()J", .handle = &ogl_digiplay_GL_createVertexBuffer},
    {.cls = GL, .name = "bufferVertexData", .sign = "(J[FII)V", .handle = &ogl_digiplay_GL_bufferVertexData},
    {.cls = GL, .name = "bufferIndexData", .sign = "(J[SII)V", .handle = &ogl_digiplay_GL_bufferIndexData},
    {.cls = GL, .name = "useProgram", .sign = "(J)V", .handle = &ogl_digiplay_GL_useProgram},
    {.cls = GL, .name = "enableVertexAttribArray", .sign = "(J)V", .handle = &ogl_digiplay_GL_enableVertexAttribArray},
    {.cls = GL, .name = "disableVertexAttribArray", .sign = "(J)V", .handle = &ogl_digiplay_GL_disableVertexAttribArray},
    {.cls = GL, .name = "vertexAttribPointer", .sign = "(JIIZII)V", .handle = &ogl_digiplay_GL_vertexAttribPointer},

    {.cls = NULL}
};
