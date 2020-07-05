//
//  render.c
//  digi
//
//  Created by mustafa on 5.07.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#include "vm.h"
#include "sprite.h"

#ifdef __APPLE__
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#elif __ANDROID__
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

#define SOKOL_IMPL
#define SOKOL_GLES2
#include "sokol_gfx.h"

static sg_pass_action default_pass = {
    .colors[0] = { .action = SG_ACTION_CLEAR, .val = { 0.0f, 0.0f, 0.0f, 1.0f } },
    .depth = {.action = SG_ACTION_CLEAR, .val = 0},
    .stencil = {.action = SG_ACTION_CLEAR, .val = 0}
};

typedef struct GfxState {
    Texture *tex;
    int texMode;
    Mat4 *proj;
    int projDirty;
} GfxState;

static GfxState gfxstate;

void render_begin(int width, int height, int bgcolor) {
    gfxstate.tex = NULL;
    gfxstate.texMode = -1;
    
    default_pass.colors[0].val[0] = ((bgcolor>>16)&0xff)/255.0;
    default_pass.colors[0].val[1] = ((bgcolor>>8)&0xff)/255.0;
    default_pass.colors[0].val[2] = ((bgcolor>>0)&0xff)/255.0;
    default_pass.colors[0].val[3] = ((bgcolor>>24)&0xff)/255.0;
    
    sg_begin_default_pass(&default_pass, width, height);
}

void render_set_projection(Mat4 *mat) {
    gfxstate.proj = mat;
    gfxstate.projDirty = 1;
}

void render_mesh(Mesh *mesh, Mat4 *mat, Texture *texture, int textureMode, int blendMode, int color, float alpha, int alphaMask) {
    
}

