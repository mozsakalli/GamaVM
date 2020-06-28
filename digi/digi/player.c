//
// Created by mustafa on 2020-06-28.
//


#include "vm.h"
#include "geom.h"
#ifdef __APPLE__
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#elif __ANDROID__
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

typedef struct Shader {
    int gpu, pos, color, uv, projection, model, texture;
} Shader;
int xgl_create_shader(const char *code, int isVertexShader) {
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

void xgl_create_program(Shader *shader, const char *code) {
    shader->gpu = -1;
    int vertex = xgl_create_shader(
            "attribute vec3 pos;\n"
            "attribute vec2 uv;\n"
            "attribute vec4 color;\n"
            "uniform mat4 projection;\n"
            "uniform mat4 model;\n"
            "varying vec4 vColor;\n"
            "varying vec2 vUv;\n"
            "varying vec3 vPos;\n"
            "void main()\n"
            "{"
            "   vColor = color;\n"
            "   vUv = uv;\n"
            "   vPos = pos;\n"
            //"   vec2 screen=vec2(960.0,-640.0);\n"
            //"   gl_Position = vec4(pos.xy * (vec2(2,2)/screen) - clamp(screen,-1.0,1.0), 0.0, 1.0);\n "
            "   gl_Position = projection * model * vec4(pos.xyz, 1.0);\n"
            "}",1);

    char tmp[1024];
    char *ptr = tmp;
    ptr += sprintf(ptr,
                   "#ifdef GL_ES\n"
                   "precision mediump float;\n"
                   "#endif\n"
                   "varying vec4 vColor;\n"
                   "varying vec2 vUv;\n"
                   "varying vec3 vPos;\n"
                   "uniform sampler2D texture;\n"
                   "uniform lowp vec4 userVec4;\n"
                   "void main(){\n");
    ptr += sprintf(ptr, "%s", code);
    ptr += sprintf(ptr,"}");

    int frag = xgl_create_shader(tmp, 0);
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
        }
    }
}

Shader shader;
#define MAX 5000
short quadibo[MAX*6];

void setup(int capacity) {
    xgl_create_program(&shader, "gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);");
    //short ibuf[capacity * 6];
    for(int i=0; i<capacity; i++) {
        quadibo[i * 6] = (short)(i * 4);
        quadibo[i * 6 + 1] = (short)(i * 4 + 1);
        quadibo[i * 6 + 2] = (short)(i * 4 + 2);

        quadibo[i * 6 + 3] = (short)(i * 4);
        quadibo[i * 6 + 4] = (short)(i * 4 + 2);
        quadibo[i * 6 + 5] = (short)(i * 4 + 3);
    }
    /*
    glGenBuffers(1, (GLuint*)&quadibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, capacity * 6 * sizeof(short), &ibuf[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);*/
}

void Gama_Player_playerstep(VM *vm, Object *method, VAR *args) {
    static int initialized = 0;
    if(!initialized) {
        setup(MAX);
        initialized = 1;
    }

    int width = args[1].I;
    int height = args[2].I;

    Mat4 projection;
    mat4_setup2d(&projection, width, height);

    Mat4 model;
    mat4_identity(&model);

    glUseProgram(shader.gpu);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glEnableVertexAttribArray(shader.pos);
    VERTEX quad[MAX * 4];
    float *ptr = &quad[0];
    glVertexAttribPointer(shader.pos, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX), ptr);
    glVertexAttribPointer(shader.uv, 2, GL_FLOAT, GL_FALSE, sizeof(VERTEX), ptr + 3);
    glVertexAttribPointer(shader.color, 4, GL_FLOAT, GL_TRUE, sizeof(VERTEX), ptr + 5);

    glUniformMatrix4fv(shader.projection, 1, GL_FALSE, &projection.vals[0]);

    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);

    short tri[6] = {0, 1, 2, 0, 2, 3};
    for(int i=0; i<MAX; i++) {
        int x = rand() % width;
        int y = rand() % height;
        int w = (rand() % 50) + 15;
        int h = (rand() % 50) + 15;

        int p = i * 4;
        quad[p+0].pos = (VEC3){x,y,0};
        quad[p+1].pos = (VEC3){x+w,y,0};
        quad[p+2].pos = (VEC3){x+w,y+h,0};
        quad[p+3].pos = (VEC3){x,y+h,0};

        int t = i*6;
        quadibo[t] = (short)(p);
        quadibo[t + 1] = (short)(p + 1);
        quadibo[t + 2] = (short)(p + 2);

        quadibo[t + 3] = (short)(p);
        quadibo[t + 4] = (short)(p + 2);
        quadibo[t + 5] = (short)(p + 3);


    }
    glUniformMatrix4fv(shader.model, 1, GL_FALSE, &model.vals[0]);

    glDrawElements(GL_TRIANGLES, MAX*6, GL_UNSIGNED_SHORT, &quadibo[0]);
}