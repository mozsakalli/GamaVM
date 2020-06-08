//
//  digiplay_gl.c
//  digi
//
//  Created by mustafa on 9.06.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#include "vm.h"
#include "digiplay.h"

#ifdef __APPLE__
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#endif


typedef struct GLShader {
    GLint handle;
    int apos, acolor, auv, uprojection, uvec4;
} GLShader;

typedef struct GLTexture {
    GLint handle;
} GLTextrue;

typedef struct GLState {
    
} GLState;


int gl_create_shader(const char *code, int isVertexShader) {
    int shader = glCreateShader(isVertexShader ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
    glShaderSource(shader, 1, &code, 0);
    glCompileShader(shader);
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE) {
        glDeleteShader(shader);
        shader = -1;
    }
    return shader;
}

void digiplay_GL_create2DShader(VM* vm, Method *method, VAR *args) {
    if(!args[0].O) {
        throw_null(vm);
        return;
    }
    int vertex = gl_create_shader(
    "attribute vec4 pos;\n"
    "attribute vec2 uv;\n"
    "attribute vec4 color;\n"
    "uniform mat4 projection;\n"
    "varying vec4 vColor;\n"
    "varying vec2 vUv;\n"
    "varying vec4 vPos;\n"
    "void main()\n"
    "{"
    "   vColor = color;\n"
    "   vUv = uv;\n"
    "   vPos = pos;\n"
    "   gl_Position = projection * vec4(pos.xyz, 1.0);\n"
    "}",1);

    char tmp[1024];
    char *ptr = tmp;
    ptr += sprintf(ptr,
    "#ifdef GL_ES\n"
    "precision mediump float;\n"
    "#endif\n"
    "varying vec4 vColor;\n"
    "varying vec2 vUv;\n"
    "varying vec4 vPos;\n"
    "uniform sampler2D texture;\n"
    "uniform lowp vec4 userVec4;\n");
    
    ptr += sprintf(ptr, string_to_ascii(args[0].O));
    ptr += sprintf(ptr,
    "void main()\n"
    "{\n"
    "    mainImage(texture);\n"
    "}");
    RETURN_J(0);
    int frag = gl_create_shader(tmp, 0);
    if(vertex == -1 || frag == -1) {
        glDeleteShader(vertex);
        glDeleteShader(frag);
        return;
    } else {
        int prg = glCreateProgram();
        glAttachShader(prg, vertex);
        glAttachShader(prg, frag);

        glLinkProgram(prg);
        glValidateProgram(prg);
        int linked;
        glGetProgramiv(prg, GL_LINK_STATUS, & linked);
        if (linked == GL_FALSE) {
            glDeleteProgram(prg);
            glDeleteShader(vertex);
            glDeleteShader(frag);
        } else {
            GLShader *shader = (GLShader*)malloc(sizeof(GLShader));
            shader->handle = prg;
            shader->apos = glGetAttribLocation(prg, "pos");
            shader->acolor = glGetAttribLocation(prg, "color");
            shader->auv = glGetAttribLocation(prg, "uv");
            shader->uprojection = glGetUniformLocation(prg, "projection");
            shader->uvec4 = glGetUniformLocation(prg, "userVec4");
            RETURN_J(shader);
        }
    }
}

void digiplay_GL_useShader(VM* vm, Method *method, VAR *args) {
    if(args[0].J == 0) {
        throw_null(vm);
        return;
    }
    GLShader *shader = (GLShader*)args[0].J;
    glUseProgram(shader->handle);
    
}

typedef struct GLQuadBatch {
    int blendMode;
    int vertPtr, triPtr;
    VERT2D *vertices;
    int capacity,end;
    int ibo;
    GLTextrue *texture;
    int projectionDirty;
} GLQuadBatch;

void digiplay_GL_createQuadBatch(VM* vm, Method *method, VAR *args) {
    GLQuadBatch *b = (GLQuadBatch*)vm_alloc(sizeof(GLQuadBatch));
    b->capacity = args[0].I;
    b->vertices = (VERT2D*)malloc(sizeof(VERT2D) * b->capacity * 4);
    
    short ibuf[b->capacity * 6];
    for(int i=0; i<b->capacity; i++) {
        ibuf[i * 6] = (short)(i * 4);
        ibuf[i * 6 + 1] = (short)(i * 4 + 1);
        ibuf[i * 6 + 2] = (short)(i * 4 + 2);

        ibuf[i * 6 + 3] = (short)(i * 4);
        ibuf[i * 6 + 4] = (short)(i * 4 + 2);
        ibuf[i * 6 + 5] = (short)(i * 4 + 3);
    }
    glGenBuffers(1, (GLuint*)&b->ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, b->ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, b->capacity * 6 * sizeof(short), ibuf, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    RETURN_J(b);
}

void digiplay_GL_resetQuadBatch(VM* vm, Method *method, VAR *args) {
    GLQuadBatch *b = (GLQuadBatch*)args[0].J;
    b->vertPtr = b->triPtr = 0;
    glDisable(GL_BLEND);
    b->blendMode = 0;
    glDisable(GL_SCISSOR_TEST);
    b->texture = NULL;
}

void digiplay_GL_quad(VM* vm, Method *method, VAR *args) {
    GLQuadBatch *b = (GLQuadBatch*)args[0].J;
    MAT2D *mat = (MAT2D*)args[1].J;
    if(b->vertPtr+1 >= b->capacity) {
        //flush
    }
    
    VERT2D *v = &b->vertices[b->vertPtr];
    v->pos = (VEC3){args[2].F,args[3].F,args[4].F};
    v->uv = (VEC2){args[5].F,args[6].F};
    v++;
    
    v->pos = (VEC3){args[7].F,args[8].F,args[9].F};
    v->uv = (VEC2){args[10].F,args[11].F};
    v++;
    
    v->pos = (VEC3){args[12].F,args[13].F,args[14].F};
    v->uv = (VEC2){args[15].F,args[16].F};
    v++;
    
    v->pos = (VEC3){args[17].F,args[18].F,args[19].F};
    v->uv = (VEC2){args[20].F,args[21].F};
    v++;
    
}
