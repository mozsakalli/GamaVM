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
#elif __ANDROID__
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

#define STBI_NO_THREAD_LOCALS
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


typedef struct GLShader {
    GLint handle;
    int apos, acolor, auv, uprojection, utexture, uvec4;
} GLShader;


typedef struct __attribute__ ((packed)) GLTexture {
    JLONG handle;
    JINT width, height, hwWidth, hwHeight;
} GLTextrue;

GLShader *glCurrentShader = NULL;
//void *glCurrentIndexBuffer = NULL;
void *glCurrentVertexBuffer = NULL;
//void *glCurrentTexture = NULL;
//int glCurrentTextureFlags = -1;

void gl_use_shader(GLShader *shader) {
    glUseProgram(shader->handle);
    glCurrentShader = shader;
    /*glCurrentIndexBuffer = */glCurrentVertexBuffer = NULL;
}

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

void Java_digiplay_GLShader2D_compile(VM* vm, Method *method, VAR *args) {
    if(!args[0].O) {
        throw_null(vm);
        return;
    }
    int vertex = gl_create_shader(
    "attribute vec3 pos;\n"
    "attribute vec2 uv;\n"
    "attribute vec4 color;\n"
    "uniform mat4 projection;\n"
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
    ptr += sprintf(ptr, "%s", string_to_ascii(args[0].O));
    ptr += sprintf(ptr,"}");
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
        glGetProgramiv(prg, GL_LINK_STATUS, &linked);
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
            shader->utexture = glGetUniformLocation(prg, "texture");
            shader->uprojection = glGetUniformLocation(prg, "projection");
            shader->uvec4 = glGetUniformLocation(prg, "userVec4");
            RETURN_J(shader);
        }
    }
}

void Java_digiplay_GLShader2D_finalize(VM* vm, Method *method, VAR *args) {
    if(args[0].O) {
        GLShader *b = (GLShader*)*FIELD_PTR_J(args[0].O, 0);
        glDeleteProgram(b->handle);
        free(b);
        free(b);
    }
}

typedef struct GLQuadBatch {
    int batchingQuads;
    int blendMode;
    int vertPtr, triangleCount;
    VERT2D *vertices;
    int capacity,end;
    int ibo;
    short *indices;
    GLTextrue *texture;
    int textureFlags;
    int textureDirty;
    int textureFlagsDirty;
    int projectionDirty;
    Mat3D projection;
    Mat3D camera;
    Mat3D combinedMatrix;
} GLQuadBatch;

void Java_digiplay_GLQuadBatch_create(VM* vm, Method *method, VAR *args) {
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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, b->capacity * 6 * sizeof(short), &ibuf[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    RETURN_J(b);
}

void Java_digiplay_GLQuadBatch_finalize(VM* vm, Method *method, VAR *args) {
    if(args[0].O) {
        GLQuadBatch *b = (GLQuadBatch*)*FIELD_PTR_J(args[0].O, 0);
        glDeleteBuffers(1, (GLuint*)&b->ibo);
        free(b->vertices);
        free(b->indices);
        free(b);
    }
}


void Java_digiplay_GLQuadBatch_begin(VM* vm, Method *method, VAR *args) {
    if(!args[0].O) {
        throw_null(vm);
        return;
    }
    GLQuadBatch *b = (GLQuadBatch*)*FIELD_PTR_J(args[0].O, 0);
    if(!b) {
        throw_null(vm);
        return;
    }
    int w = args[1].I;
    int h = args[2].I;
    glViewport(0, 0, w, h);

    b->blendMode = b->vertPtr = b->triangleCount = 0;
    glDisable(GL_BLEND);
    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_STENCIL_TEST);
    
    b->texture = NULL;
    b->textureFlags = 0;
    b->textureDirty = b->textureFlagsDirty = 0;
    b->batchingQuads = 1;

    mat3d_setup2d(&b->projection, w, h);
    mat3d_identity(&b->camera);
    b->projectionDirty = 1;
    glCurrentShader = NULL;
    /*glCurrentIndexBuffer = */glCurrentVertexBuffer = NULL;
    
    if(args[3].I) {
        unsigned int c = args[4].I;
        glClearColor(((c>>16)&0xff)/255.0, ((c>>8)&0xff)/255.0, (c&0xff)/255.0, ((c>>24)&0xff)/255.0);
        glClear(GL_COLOR_BUFFER_BIT);
    }
}


void digiplay_GL_freeQuadBatch(VM* vm, Method *method, VAR *args) {
    GLQuadBatch *b = (GLQuadBatch*)args[0].J;
    if(b) {
        if(b->vertices) free(b->vertices);
        free(b);
    }
}

void quad_batch_flush(GLQuadBatch *b) {
    if(b->triangleCount > 0 && glCurrentShader) {
        if(b->projectionDirty) {
            mat3d_multiply(&b->projection, &b->camera, &b->combinedMatrix);
            glUniformMatrix4fv(glCurrentShader->uprojection, 1, GL_FALSE, &b->combinedMatrix.vals[0]);
            b->projectionDirty = 0;
        }

        if(b->textureDirty) {
            b->textureDirty = 0;
            //if(glCurrentTexture != b->texture) {
                glActiveTexture(GL_TEXTURE0);
                glUniform1i(glCurrentShader->utexture, 0);
                glBindTexture(GL_TEXTURE_2D, b->texture ? (GLint)b->texture->handle : 0);
                //glCurrentTexture = b->texture;
                b->textureFlagsDirty = 1;
                //glCurrentTextureFlags = -1;
            //}
        }
        int err = glGetError();
        if(err) {
            printf("GL2: %d\n", err);
        }

        if(b->textureFlagsDirty) {
            b->textureFlagsDirty = 0;
            //if(glCurrentTextureFlags != b->textureFlags) {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                //glCurrentTextureFlags = b->textureFlags;
            //}
        }

        //if(b->ibo != (int)glCurrentIndexBuffer) {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, b->ibo);
            //glCurrentIndexBuffer = (void*)b->ibo;
        //}

        if(glCurrentVertexBuffer != b->vertices) {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            unsigned char *base = (unsigned char*)&b->vertices[0];
            glEnableVertexAttribArray(glCurrentShader->apos);
            glVertexAttribPointer(glCurrentShader->apos, 3, GL_FLOAT, GL_FALSE, sizeof(VERT2D), base);
            
            glEnableVertexAttribArray(glCurrentShader->acolor);
            glVertexAttribPointer(glCurrentShader->acolor, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VERT2D), base + 12);
            
            glEnableVertexAttribArray(glCurrentShader->auv);
            glVertexAttribPointer(glCurrentShader->auv, 2, GL_FLOAT, GL_FALSE, sizeof(VERT2D), base + 16);
            
            glCurrentVertexBuffer = b->vertices;
        }

        glDrawElements(GL_TRIANGLES, b->triangleCount, GL_UNSIGNED_SHORT, NULL);
    }
    b->triangleCount = b->vertPtr = 0;
}

// 1QuadMesh mesh,
// 2Mat2D mat,
// 3GLShader2D shader,
// 4GLTexture texture,
// 5int textureFlags,
// 6int color,
// 7float alpha,
// 8int blendMode
void Java_digiplay_GLQuadBatch_drawQuadMesh(VM* vm, Method *method, VAR *args) {
    if(!args[0].O || !args[1].O || !args[2].O || !args[3].O) {
        throw_null(vm);
        return;
    }
    float alpha = args[7].F;
    if(alpha <= 0) return;
    
    GLQuadBatch *b = (GLQuadBatch*)*FIELD_PTR_J(args[0].O, 0);
    QuadMesh *m = (QuadMesh*)*FIELD_PTR_J(args[1].O, 0);
    Mat2D *mat = (Mat2D*)*FIELD_PTR_J(args[2].O, 0);
    GLShader *shader = (GLShader*)*FIELD_PTR_J(args[3].O, 0);
    if(m->size <= 0) return;
    
    int color = args[6].I;
    int blendMode = args[8].I;
    if(alpha > 1) alpha = 1;
    COLOR col;
    col.r = ((color >> 16) & 0xff)*alpha;
    col.g = ((color >> 8) & 0xff)*alpha;
    col.b = ((color >> 0) & 0xff)*alpha;
    col.a = alpha * 255;

    if(shader != glCurrentShader) {
        quad_batch_flush(b);
        gl_use_shader(shader);
        b->projectionDirty = 1;
    }

    if(blendMode != b->blendMode) {
        quad_batch_flush(b);
        switch(blendMode) {
            case 0:
                glDisable(GL_BLEND);
                break;
                
            case 1:
                if(b->blendMode == 0) glEnable(GL_BLEND);
                glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
                break;
                
            case 2:
                if(b->blendMode == 0) glEnable(GL_BLEND);
                glBlendFunc(GL_ONE, GL_DST_ALPHA);
                break;
        }
        b->blendMode = blendMode;
    }

    GLTextrue *tex = args[4].O ? args[4].O->instance : NULL;
    int texFlags = args[5].I;

    if(tex != b->texture || texFlags != b->textureFlags) {
        quad_batch_flush(b);
        b->textureDirty = tex != b->texture;
        b->textureFlagsDirty = texFlags != b->textureFlags;
        b->texture = tex;
        b->textureFlags = texFlags;
    }

    if(!b->batchingQuads) {
        quad_batch_flush(b);
        b->batchingQuads = 1;
    }

    QuadMeshItem *q = &m->items[0];

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

            q->p1 = (VEC3){xm00 + ym01m02,xm10 + ym11m12,0};
            //q->p1.y = xm10 + ym11m12;
            q->p2 = (VEC3){x2m00 + ym01m02,x2m10 + ym11m12,0};
            //q->p2.y = x2m10 + ym11m12;
            q->p3 = (VEC3){x2m00 + y2m01m02,x2m10 + y2m11m12,0};
            //q->p3.y = x2m10 + y2m11m12;
            q->p4 = (VEC3){xm00 + y2m01m02, xm10 + y2m11m12, 0};
            //q->p4.y = xm10 + y2m11m12;
            /*
            q->p1 = (VEC3){q->tl.x, q->tl.y, 0};
            q->p2 = (VEC3){q->br.x, q->tl.y, 0};
            q->p3 = (VEC3){q->br.x, q->br.y, 0};
            q->p4 = (VEC3){q->tl.x, q->br.y, 0};*/
            q++;
        }
        q = &m->items[0];
        mat->meshVersion = m->version;
    }
    
    VERT2D *v = &b->vertices[b->vertPtr];
    for(int i=0; i<m->size; i++) {
        if(b->vertPtr == b->capacity*4) {
            quad_batch_flush(b);
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
        b->triangleCount += 6;
        b->vertPtr += 4;
    }
}

void Java_digiplay_GLQuadBatch_end(VM* vm, Method *method, VAR *args) {
    if(!args[0].O) {
        throw_null(vm);
        return;
    }
    GLQuadBatch *b = (GLQuadBatch*)*FIELD_PTR_J(args[0].O, 0);
    quad_batch_flush(b);
}

static QuadMesh *QUADCACHE = NULL;
void Java_digiplay_QuadMesh_create(VM* vm, Method *method, VAR *args) {
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
    RETURN_J(m);
}

void Java_digiplay_QuadMesh_set(VM* vm, Method *method, VAR *args) {
    if(!args[0].O) {
        throw_null(vm);
        return;
    }
    QuadMesh *m = (QuadMesh*)*FIELD_PTR_J(args[0].O, 0);
    int index = args[1].I;
    if(index < 0 || index >= m->capacity) {
        throw_arraybounds(vm, index, m->capacity);
        return;
    }
    QuadMeshItem *q = &m->items[index];
    q->tl = (VEC2){args[2].F, args[3].F};
    q->br = (VEC2){args[4].F, args[5].F};
    q->t1 = (VEC2){args[6].F, args[7].F};
    q->t2 = (VEC2){args[8].F, args[9].F};
    q->t3 = (VEC2){args[10].F, args[11].F};
    q->t4 = (VEC2){args[12].F, args[13].F};
    
    m->version++;
}

void Java_digiplay_QuadMesh_finalize(VM* vm, Method *method, VAR *args) {
    if(args[0].O) {
        QuadMesh *m = (QuadMesh*)*FIELD_PTR_J(args[0].O, 0);
        m->next = QUADCACHE;
        QUADCACHE = m;
    }
}


void Java_digiplay_GLTexture_upload(VM *vm, Object *method, VAR *args) {
    if(!args[0].O || !args[1].O) {
        throw_null(vm);
        return;
    }

    GLTextrue *tex = (GLTextrue*)args[0].O->instance;
    Object *array = args[1].O;

    int comp = 0;
    stbi_uc* pix = stbi_load_from_memory((stbi_uc *)array->instance, array->length, &tex->width, &tex->height, &comp, 4);
    if(pix) {
        //
        struct RGBA { unsigned char r; unsigned char g; unsigned char b; unsigned char a; };
        struct RGBA * ptr = (struct RGBA * ) pix;
        int len = tex->width * tex->height;
        for (int i = 0; i < len; i++) {
            float a = ptr[i].a / 255.0f;
            ptr[i].r *= a;
            ptr[i].g *= a;
            ptr[i].b *= a;
        }

        tex->hwWidth = tex->width; //glWidth = npot ? width : pow2_size(width);");
        tex->hwHeight = tex->height; // npot ? height : pow2_size(height);");
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture( GL_TEXTURE_2D,texture );
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, tex->hwWidth, tex->hwHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
        glPixelStorei( GL_UNPACK_ALIGNMENT,1 );
        glTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, tex->width, tex->height, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)pix );
        free(pix);
        tex->handle = texture;
        vm->frames[vm->FP].ret.I = 1;
    } else
        vm->frames[vm->FP].ret.I = 1;
}

typedef struct GLTriangleBatch {

} GLTriangleBatch;

NativeMethodInfo digiplay_gl_methods[] = {
    {"digiplay/GLShader2D:compile:(Ljava/lang/String;)J", &Java_digiplay_GLShader2D_compile},
    {"digiplay/GLShader2D:finalize:()V", &Java_digiplay_GLShader2D_finalize},

    {"digiplay/GLQuadBatch:create:(I)J", &Java_digiplay_GLQuadBatch_create},
    {"digiplay/GLQuadBatch:begin:(IIZI)V", &Java_digiplay_GLQuadBatch_begin},
    {"digiplay/GLQuadBatch:drawQuadMesh:(Ldigiplay/QuadMesh;Ldigiplay/Mat2D;Ldigiplay/GLShader2D;Ldigiplay/GLTexture;IIFI)V", &Java_digiplay_GLQuadBatch_drawQuadMesh},
    {"digiplay/GLQuadBatch:end:()V", &Java_digiplay_GLQuadBatch_end},
    {"digiplay/GLQuadBatch:finalize:()V", &Java_digiplay_GLQuadBatch_finalize},

    {"digiplay/QuadMesh:create:(I)J", &Java_digiplay_QuadMesh_create},
    {"digiplay/QuadMesh:set:(IFFFFFFFFFFFF)V", &Java_digiplay_QuadMesh_set},
    {"digiplay/QuadMesh:finalize:()V", &Java_digiplay_QuadMesh_finalize},

    {"digiplay/GLTexture:upload:([B)V", &Java_digiplay_GLTexture_upload},

    NULL
};
