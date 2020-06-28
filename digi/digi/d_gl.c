//
// Created by mustafa on 2020-06-27.
//

#include "d.h"
#ifdef __APPLE__
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#elif __ANDROID__
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

typedef struct GLShader {
    GLuint gpu;
    int pos, color, uv, texture, projection, model, user0, user1, user2, user3;
} GLShader;

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

void gl_create_shader(GLShader *shader, const char *vcode, const char *fcode) {
    int vertex = gl_create_shader(vcode, 1);
    int frag = gl_create_shader(fcode, 0);
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
        glGetProgramiv(prg, GL_LINK_STATUS, &linked);
        if (linked == GL_FALSE) {
            glDeleteProgram(prg);
            glDeleteShader(vertex);
            glDeleteShader(frag);
        } else {
            shader->gpu = prg;
            shader->pos = glGetAttribLocation(prg, "pos");
            shader->color = glGetAttribLocation(prg, "color");
            shader->uv = glGetAttribLocation(prg, "uv");
            shader->texture = glGetUniformLocation(prg, "texture");
            shader->projection = glGetUniformLocation(prg, "projection");
            shader->model = glGetUniformLocation(prg, "model");
            shader->user0 = glGetUniformLocation(prg, "user0");
            shader->user1 = glGetUniformLocation(prg, "user1");
            shader->user2 = glGetUniformLocation(prg, "user2");
            shader->user3 = glGetUniformLocation(prg, "user3");
        }
    }
}

#define MAX_SHADER  8
GLuint BatchQuadIBO;
extern int CurrentMaterial;
int CurrentShader;
int CurrentTexture;
GLShader glShaders[MAX_SHADER];

void gl_render_init() {
    //setup quad index buffer
    short ibuf[MAX_QUAD * 6];
    for(int i=0; i<MAX_QUAD; i++) {
        ibuf[i * 6] = (short)(i * 4);
        ibuf[i * 6 + 1] = (short)(i * 4 + 1);
        ibuf[i * 6 + 2] = (short)(i * 4 + 2);

        ibuf[i * 6 + 3] = (short)(i * 4);
        ibuf[i * 6 + 4] = (short)(i * 4 + 2);
        ibuf[i * 6 + 5] = (short)(i * 4 + 3);
    }
    glGenBuffers(1, &BatchQuadIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BatchQuadIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, MAX_QUAD * 6 * sizeof(short), &ibuf[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void gl_render_setup_material(int material) {
    Material *m = &material;
    Material *c = &CurrentMaterial;

    if(m->shader != c->shader) {
        //switch shader
    }

    if(m->blendmode != c->blendmode) {
        switch (m->blendmode) {
            case BLEND_NONE:
                if(c->blendmode != BLEND_NONE) glDisable(GL_BLEND);
                break;

            case BLEND_NORMAL:
                if(c->blendmode == BLEND_NONE) glEnable(GL_BLEND);
                glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
                break;

            case BLEND_ADD:
                if(c->blendmode == BLEND_NONE) glEnable(GL_BLEND);
                glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
                break;
        }
    }

    if(m->depthwrite != c->depthwrite) {
        if(m->depthwrite) glEnable(GL_DEPTH_WRITEMASK); else glDisable(GL_DEPTH_WRITEMASK);
    }

    if(m->depthtest != c->depthtest) {
        glDisable(GL_DEPTH_TEST); //todo
    }

    if(m->colorwrite != c->colorwrite) {
        glColorMask(m->colorwrite&(1<<3), m->colorwrite&(1<<2), m->colorwrite&(1<<1), m->colorwrite&(1));
    }
    CurrentMaterial = material;

}

