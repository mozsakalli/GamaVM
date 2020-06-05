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












void checkError() {
    int err = glGetError();
    if (err != 0) printf("!! GLERR: %d\n", err);
}



void ogl_digiplay_GL_viewport(VM *vm, Object *method, VAR *args) {
    glViewport(args[0].I, args[1].I, args[2].I, args[3].I);
    checkError();
}

void ogl_digiplay_GL_clearColor(VM *vm, Object *method, VAR *args) {
    glClearColor(args[0].F, args[1].F, args[2].F, args[3].F);
    checkError();
}

void ogl_digiplay_GL_clear(VM *vm, Object *method, VAR *args) {
    glClear(args[0].I);
    checkError();
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
    checkError();
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
    } else throw_nullpointerexception(vm);
    checkError();
    vm->frames[vm->FP].retVal.J = ret;
}

void ogl_digiplay_GL_attribLocation(VM *vm, Object *method, VAR *args) {
    if(!args[1].O) throw_nullpointerexception(vm);
    else vm->frames[vm->FP].retVal.J = glGetAttribLocation(args[0].J, string2c(args[1].O));
    checkError();
}
void ogl_digiplay_GL_uniformLocation(VM *vm, Object *method, VAR *args) {
    if(!args[1].O) throw_nullpointerexception(vm);
    else vm->frames[vm->FP].retVal.J = glGetUniformLocation(args[0].J, string2c(args[1].O));
    checkError();
}
void ogl_digiplay_GL_createVertexBuffer(VM *vm, Object *method, VAR *args) {
    GLuint buf;
    glGenBuffers(1, &buf);
    vm->frames[vm->FP].retVal.J = buf;
    checkError();
}
void ogl_digiplay_GL_bufferVertexData(VM *vm, Object *method, VAR *args) {
    if(!args[1].O) throw_nullpointerexception(vm);
    else {
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
        checkError();
        glBufferData(GL_ARRAY_BUFFER, (end - start) * sizeof(float), buffer, GL_DYNAMIC_DRAW);
        checkError();
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        checkError();
    }
}

void ogl_digiplay_GL_bufferIndexData(VM *vm, Object *method, VAR *args) {
    if(!args[1].O) throw_nullpointerexception(vm);
    else {
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
        checkError();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (end - start) * sizeof(short), buffer, GL_DYNAMIC_DRAW);
        checkError();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        checkError();
    }
}
void ogl_digiplay_GL_bindVertexBuffer(VM *vm, Object *method, VAR *args) {
    glBindBuffer(GL_ARRAY_BUFFER, args[0].J);
    checkError();
}

void ogl_digiplay_GL_bindIndexBuffer(VM *vm, Object *method, VAR *args) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, args[0].J);
    checkError();
}

void ogl_digiplay_GL_enable(VM *vm, Object *method, VAR *args) {
    glEnable(args[0].I);
    checkError();
}
void ogl_digiplay_GL_disable(VM *vm, Object *method, VAR *args) {
    glDisable(args[0].I);
    checkError();
}
void ogl_digiplay_GL_useProgram(VM *vm, Object *method, VAR *args) {
    glUseProgram(args[0].J);
    checkError();
}
void ogl_digiplay_GL_enableVertexAttribArray(VM *vm, Object *method, VAR *args) {
    glEnableVertexAttribArray(args[0].J);
    checkError();
}
void ogl_digiplay_GL_disableVertexAttribArray(VM *vm, Object *method, VAR *args) {
    glDisableVertexAttribArray(args[0].J);
    checkError();
}
void ogl_digiplay_GL_vertexAttribPointer(VM *vm, Object *method, VAR *args) {
    glVertexAttribPointer(args[0].J, args[1].I, args[2].I, args[3].I, args[4].I, args[5].I);
    checkError();
}
void ogl_digiplay_GL_uniformMatrix4f(VM *vm, Object *method, VAR *args) {
    if(!args[1].O) throw_nullpointerexception(vm);
    else
        glUniformMatrix4fv(args[0].J, 1, args[2].I ? GL_TRUE : GL_FALSE, (GLfloat*)args[1].O->instance);
    
    checkError();
}
void ogl_digiplay_GL_drawElements(VM *vm, Object *method, VAR *args) {
    glDrawElements(args[0].I, args[1].I, GL_UNSIGNED_SHORT, args[2].I);
    checkError();
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
    {.cls = GL, .name = "bindVertexBuffer", .sign = "(J)V", .handle = &ogl_digiplay_GL_bindVertexBuffer},
    {.cls = GL, .name = "bufferIndexData", .sign = "(J[SII)V", .handle = &ogl_digiplay_GL_bufferIndexData},
    {.cls = GL, .name = "bindIndexBuffer", .sign = "(J)V", .handle = &ogl_digiplay_GL_bindIndexBuffer},
    {.cls = GL, .name = "useProgram", .sign = "(J)V", .handle = &ogl_digiplay_GL_useProgram},
    {.cls = GL, .name = "enableVertexAttribArray", .sign = "(J)V", .handle = &ogl_digiplay_GL_enableVertexAttribArray},
    {.cls = GL, .name = "disableVertexAttribArray", .sign = "(J)V", .handle = &ogl_digiplay_GL_disableVertexAttribArray},
    {.cls = GL, .name = "vertexAttribPointer", .sign = "(JIIZII)V", .handle = &ogl_digiplay_GL_vertexAttribPointer},
    {.cls = GL, .name = "uniformMatrix4f", .sign = "(J[FZ)V", .handle = &ogl_digiplay_GL_uniformMatrix4f},
    {.cls = GL, .name = "drawElements", .sign = "(III)V", .handle = &ogl_digiplay_GL_drawElements},
    {.cls = GL, .name = "enable", .sign = "(I)V", .handle = &ogl_digiplay_GL_enable},
    {.cls = GL, .name = "disable", .sign = "(I)V", .handle = &ogl_digiplay_GL_disable},

    {.cls = NULL}
};
