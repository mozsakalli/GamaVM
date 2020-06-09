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
    MAT3D projection;
    MAT2D camera;
    GLShader *shader;
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

void digiplay_GL_freeQuadBatch(VM* vm, Method *method, VAR *args) {
    GLQuadBatch *b = (GLQuadBatch*)args[0].J;
    if(b) {
        if(b->vertices) free(b->vertices);
        free(b);
    }
}

void digiplay_GL_resetQuadBatch(VM* vm, Method *method, VAR *args) {
    GLQuadBatch *b = (GLQuadBatch*)args[0].J;
    b->vertPtr = b->triPtr = 0;
    glDisable(GL_BLEND);
    b->blendMode = 0;
    glDisable(GL_SCISSOR_TEST);
    b->texture = NULL;
    b->shader = NULL;
}

void digiplay_GL_drawQuadMesh(VM* vm, Method *method, VAR *args) {
    int color = args[3].I;
    float alpha = args[4].F;
    float a = ((color >> 24) & 0xff)/255.0;
    alpha *= a;
    if(alpha <= 0) return;
    COLOR col;
    col.r = ((color >> 16) & 0xff)*alpha;
    col.g = ((color >> 8) & 0xff)*alpha;
    col.b = ((color >> 0) & 0xff)*alpha;
    col.a = alpha * 255;

    GLQuadBatch *b = (GLQuadBatch*)args[0].J;
    MAT2D *mat = (MAT2D*)args[1].J;
    QuadMesh *m = (QuadMesh*)args[2].J;
    QuadMeshItem *q = &m->items[0];
    VERT2D *v = &b->vertices[b->vertPtr];
    

    if(m->version != mat->meshVersion) {
        float m00 = mat->m00;
        float m01 = mat->m01;
        float m02 = mat->m02;
        float m10 = mat->m10;
        float m11 = mat->m11;
        float m12 = mat->m12;
        for(int i=0; i<m->size; i++) {
            float xm00 = q->tl.x * m00;
            float xm10 = q->tl.x * m10;
            float x2m00 = q->br.x * m00;
            float x2m10 = q->br.x * m10;
            float ym01 = q->tl.y * m01;
            float ym11 = q->tl.y * m11;
            float y2m01 = q->br.y * m01;
            float y2m11 = q->br.y * m11;
            float ym01m02 = ym01 + m02;
            float ym11m12 = ym11 + m12;
            float y2m01m02 = y2m01 + m02;
            float y2m11m12 = y2m11 + m12;

            q->p1.x = xm00 + ym01m02;
            q->p1.y = xm10 + ym11m12;
            q->p2.x = x2m00 + ym01m02;
            q->p2.y = x2m10 + ym11m12;
            q->p3.x = x2m00 + y2m01m02;
            q->p3.y = x2m10 + y2m11m12;
            q->p4.x = xm00 + y2m01m02;
            q->p4.y = xm10 + y2m11m12;
            q++;
        }
        q = &m->items[0];
        m->version = mat->meshVersion;
    }
    
    for(int i=0; i<m->size; i++) {
        if(b->vertPtr == b->capacity) {
            //flush
            v = &b->vertices[0];
        }
        
        v->pos =  q->p1;
        v->uv = q->t1;
        v->color = col;
        v++;
        
        v->pos = q->p2;
        v->uv = q->t2;
        v->color = col;
        v++;
        
        v->pos = q->p3;
        v->uv = q->t3;
        v->color = col;
        v++;
        
        v->pos = q->p4;
        v->uv = q->t4;
        v->color = col;
        v++;
        q++;
    }
}

static QuadMesh *QUADCACHE = NULL;

void digiplay_GL_createQuadMesh(VM* vm, Method *method, VAR *args) {
    int size = args[0].I;
    QuadMesh *m = QUADCACHE;
    if(m) {
        QUADCACHE = QUADCACHE->next;
    } else {
        m = (QuadMesh*)vm_alloc(sizeof(QuadMesh));
    }
    if(m->capacity < size) {
        m->items = realloc(m->items, sizeof(QuadMeshItem) * size);
        m->capacity = size;
    }
    m->size = size;
    m->items = (QuadMeshItem*)malloc(m->capacity * sizeof(QuadMeshItem));
    RETURN_J(m);
}

void digiplay_GL_quadMeshSet(VM* vm, Method *method, VAR *args) {
    QuadMesh *m = (QuadMesh*)args[0].J;
    int index = args[1].I;
    if(index < 0 || index >= m->capacity) return;
    QuadMeshItem *q = &m->items[index];
    q->tl = (VEC2){args[2].F, args[3].F};
    q->br = (VEC2){args[4].F, args[5].F};
    q->t1 = (VEC2){args[6].F, args[7].F};
    q->t2 = (VEC2){args[8].F, args[9].F};
    q->t3 = (VEC2){args[10].F, args[11].F};
    q->t4 = (VEC2){args[12].F, args[13].F};
    m->version = -1;
}

void digiplay_GL_quadMeshFree(VM* vm, Method *method, VAR *args) {
    QuadMesh *m = (QuadMesh*)args[0].J;
    m->next = QUADCACHE;
    QUADCACHE = m;
}
