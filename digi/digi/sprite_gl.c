//
// Created by mustafa on 2020-06-28.
//

#include "sprite.h"
#ifdef __APPLE__
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#elif __ANDROID__
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif
/*
Texture *glBoundTexture = NULL;
int glBoundTextureMode = 0;
int glBoundBlendMode = 0;
int glBoundCulling = 0;
int glBoundDepthMode = 0;
int glBoundStencilMode = 0;
Shader *glBoundShader = NULL;

Shader *deviceShaders[8] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

Shader *deviceCurrentShader = NULL;
Shader *deviceDefaultShader = NULL;

int needsVertexBinding = 1;
void *lastVertexBuffer = NULL;

int render_create_shader(const char *code, int isVertexShader) {
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

void render_create_shader_program(Shader *shader, const char *code) {
    shader->gpu = -1;
    int vertex = render_create_shader(
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
                   "varying vec3 vPos;\n"
                   "uniform sampler2D texture;\n"
                   "uniform lowp vec4 userVec4;\n"
                   "void main(){\n");
    ptr += sprintf(ptr, "%s", code);
    ptr += sprintf(ptr,"}");

    int frag = render_create_shader(tmp, 0);
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
void render_clear_color(int color) {
    glClearColor(((color >> 16)&0xFF)/255.0f, ((color >> 8)&0xFF)/255.0f, ((color >> 0)&0xFF)/255.0f, ((color >> 24)&0xFF)/255.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void render_set_cliprect(float x, float y, float w, float h) {

}

void render_set_blendmode(int mode) {
    if(mode == 0)
        glDisable(GL_BLEND);
    else {
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, mode == 1 ? GL_ONE_MINUS_SRC_ALPHA : GL_DST_ALPHA);
    }
}

void render_viewport(int x, int y, int width, int height) {
    glViewport(x,y,width,height);
}
void render_useshader(Shader *shader) {
    if(!shader) {
        if(!deviceDefaultShader) {
            deviceDefaultShader = vm_alloc(sizeof(Shader));
            render_create_shader_program(deviceDefaultShader, "gl_FragColor = texture2D(texture, vUv.xy).xyzw * vColor.xyzw; ");
        }
        shader = deviceDefaultShader;
    }
    deviceCurrentShader = shader;
    if(shader)
        glUseProgram(shader->gpu);
    needsVertexBinding = 1;
}
void render_set_projection(Mat4 *projection) {
    if(deviceCurrentShader) {
        glUniformMatrix4fv(deviceCurrentShader->projection, 1, GL_FALSE, &projection->vals[0]);
    }
}
void render_prepare_draw(Texture *texture, int textureMode, int blendMode, int culling, int depth, int stencil) {
    if(texture != glBoundTexture) {
        glBoundTextureMode = -1;
    }
    
    if(textureMode != glBoundTextureMode) {
        
    }
    
    if(blendMode != glBoundBlendMode) {
        
    }
}

void render_draw_indexed(VERTEX *vertex, short *index, int count, int drawAsLines) {
    if(!deviceCurrentShader) return;
    if(needsVertexBinding || lastVertexBuffer != vertex) {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        float *ptr = vertex;
        glEnableVertexAttribArray(deviceCurrentShader->pos);
        glVertexAttribPointer(deviceCurrentShader->pos, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX), ptr);
        glEnableVertexAttribArray(deviceCurrentShader->uv);
        glVertexAttribPointer(deviceCurrentShader->uv, 2, GL_FLOAT, GL_FALSE, sizeof(VERTEX), ptr + 3);
        glEnableVertexAttribArray(deviceCurrentShader->color);
        glVertexAttribPointer(deviceCurrentShader->color, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VERTEX), ptr + 5);
        lastVertexBuffer = vertex;
        needsVertexBinding = 0;
    }

    glDrawElements(drawAsLines ? GL_LINE_STRIP : GL_TRIANGLES, count, GL_UNSIGNED_SHORT, index);
    int err = glGetError();
}

void render_upload_texture(Texture *tex, void *buffer) {
    GLuint texture = (GLuint)tex->gpu;
    glActiveTexture(GL_TEXTURE0);
    if(!texture) {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glPixelStorei( GL_UNPACK_ALIGNMENT,1 );
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 32,32,0, GL_RGBA,
                     GL_UNSIGNED_BYTE, 0);
    } else glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glPixelStorei( GL_UNPACK_ALIGNMENT,1 );
    glTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, tex->width, tex->height, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)buffer );
    tex->gpu = texture;
}

void render_set_texture(Texture *tex) {
    if(deviceCurrentShader) {
        glActiveTexture(GL_TEXTURE0);
        glUniform1i(deviceCurrentShader->texture, 0);
        glBindTexture(GL_TEXTURE_2D, tex ? (GLuint)tex->gpu : 0);
    }
}

void render_set_texture_mode(int mode) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void render_cull_mode(int mode) {

}
*/
