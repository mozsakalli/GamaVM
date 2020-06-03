//
//  digiplay_metal.m
//  Digiplay
//
//  Created by mustafa on 30.05.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#include "jvm.h"
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <Metal/Metal.h>

#define DEPTH_BUFFER_BIT  0x00000100
#define STENCIL_BUFFER_BIT 0x00000400
#define COLOR_BUFFER_BIT 0x00004000

extern CAMetalLayer* MetalLayer;
extern id<MTLDevice> MetalDevice;

extern id<CAMetalDrawable> MetalDrawable;
extern id<MTLTexture> MetalDepth;
extern id<MTLTexture> MetalStencil;
extern MTLRenderPassDescriptor *MetalFramebuffer;

id<MTLCommandQueue> metal_cmdQueue = nil;
id<MTLCommandBuffer> metal_cmdBuffer = nil;
id<MTLRenderCommandEncoder> metal_cmdEncoder = nil;
MTLRenderPipelineDescriptor* metal_pipelineDesc;

int metal_clear_flags = 0;
MTLViewport metal_vp;

void metal_close_encoder() {
    if(metal_cmdEncoder) {
        [metal_cmdEncoder endEncoding];
        [metal_cmdEncoder release];
        metal_cmdEncoder = nil;
    }
}

void metal_begin_frame() {
    if(!metal_cmdQueue) {
        metal_cmdQueue = [MetalDevice newCommandQueue];
        [metal_cmdQueue retain];
    }
    metal_cmdBuffer = [metal_cmdQueue commandBuffer];
    [metal_cmdBuffer retain];
}
void metal_end_frame() {
    metal_close_encoder();
    [metal_cmdBuffer presentDrawable:MetalDrawable];
    [metal_cmdBuffer commit];
    [metal_cmdBuffer release];
    metal_cmdBuffer = nil;
}

id<MTLRenderCommandEncoder> metal_get_encoder() {
    if (metal_cmdEncoder == nil) {
        int creq=metal_clear_flags;
        MTLRenderPassDescriptor *rp=MetalFramebuffer;
        /*if (currentBuffer)
        {
            rp=((metalShaderBuffer *)currentBuffer)->mrpd;
            creq=((metalShaderBuffer *)currentBuffer)->clearReq;
            ((metalShaderBuffer *)currentBuffer)->clearReq=0;
        }
        else
            clearReq=0;*/
        metal_clear_flags = 0;
        rp.colorAttachments[0].loadAction=(creq&COLOR_BUFFER_BIT)?MTLLoadActionClear:MTLLoadActionLoad;
        rp.depthAttachment.loadAction=(creq&DEPTH_BUFFER_BIT)?MTLLoadActionClear:MTLLoadActionLoad;
        rp.stencilAttachment.loadAction=(creq&STENCIL_BUFFER_BIT)?MTLLoadActionClear:MTLLoadActionLoad;
        metal_cmdEncoder=[metal_cmdBuffer renderCommandEncoderWithDescriptor:rp];
        [metal_cmdEncoder retain];
        //metalShaderProgram::resetAll();
        [metal_cmdEncoder setViewport:metal_vp];
        //todo: [mrce setScissorRect:sr_];
    }
    return metal_cmdEncoder;
}

MTLRenderPassDescriptor *metal_get_pass() {
    return MetalFramebuffer;
}

void metal_digiplay_GL_viewport(VM *vm, Object *method, VAR *args) {
    metal_vp.originX = args[0].I;
    metal_vp.originY = args[1].I;
    metal_vp.width = args[2].I;
    metal_vp.height = args[3].I;
    metal_vp.znear = 0;
    metal_vp.zfar = 1;
    if(metal_cmdEncoder)
        [metal_cmdEncoder setViewport:metal_vp];
}

void metal_digiplay_GL_clearColor(VM *vm, Object *method, VAR *args) {
    metal_get_pass().colorAttachments[0].clearColor = MTLClearColorMake(args[0].F, args[1].F, args[2].F, args[3].F);
}

void metal_digiplay_GL_clear(VM *vm, Object *method, VAR *args) {
    metal_clear_flags = args[0].I;
    metal_close_encoder();
    metal_get_encoder();
}

void metal_digiplay_GL_drawElements(VM *vm, Object *method, VAR *args) {
    
}

extern NativeMethodInfo digiplay_GL_NATIVES[];
void metal_setup_natives() {
    digiplay_GL_NATIVES[0].handle = &metal_digiplay_GL_viewport;
    digiplay_GL_NATIVES[1].handle = &metal_digiplay_GL_clearColor;
    digiplay_GL_NATIVES[2].handle = &metal_digiplay_GL_clear;
}
/*
#define GL "digiplay/GL"
NativeMethodInfo metal_digiplay_GL_NATIVES[] = {
    {.cls = GL, .name = "viewport", .sign = "(IIII)V", .handle = &metal_digiplay_GL_viewport},
    {.cls = GL, .name = "clearColor", .sign = "(FFFF)V", .handle = &metal_digiplay_GL_clearColor},
    {.cls = GL, .name = "clear", .sign = "(I)V", .handle = &metal_digiplay_GL_clear},

    {.cls = NULL}
};
*/


