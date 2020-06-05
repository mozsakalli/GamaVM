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

typedef struct MetalShader {
    MTLRenderPipelineDescriptor *renderPipelineDesc;
} MetalShader;

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

void metal_digiplay_GL_compileProgram(VM *vm, Object *method, VAR *args) {
    if(!args[0].O) {
        throw_nullpointerexception(vm);
        return;
    }
    //MTLRenderPipelineDescriptor *desc = [[MTLRenderPipelineDescriptor alloc] init];
    NSError *err;
    id<MTLLibrary> l=[MetalDevice newLibraryWithSource:[NSString stringWithUTF8String:string2c(args[0].O)] options:nil error:&err];
    if(err) {
        NSLog(@"%@",[err description]);
        vm->frames[vm->FP].retVal.J = -1;
        return;
    }
    id<MTLFunction> vertex = [l newFunctionWithName:@"vmain"];
    if(!vertex) {
        vm->frames[vm->FP].retVal.J = -1;
        return;
    }
    /*
    l=[MetalDevice newLibraryWithSource:[NSString stringWithUTF8String:string2c(args[1].O)] options:nil error:&err];
    if(err) {
        NSLog(@"%@",[err description]);
        vm->frames[vm->FP].retVal.J = -1;
        return;
    }*/
    id<MTLFunction> fragment = [l newFunctionWithName:@"fmain"];
    if(!fragment) {
        vm->frames[vm->FP].retVal.J = -1;
        return;
    }
    
    MetalShader *shader = malloc(sizeof(MetalShader));
    shader->renderPipelineDesc = [[MTLRenderPipelineDescriptor alloc] init];
    shader->renderPipelineDesc.vertexFunction = vertex;
    shader->renderPipelineDesc.fragmentFunction = fragment;
    vm->frames[vm->FP].retVal.J = (jlong)shader;
}

void metal_digiplay_GL_attribLocation(VM *vm, Object *method, VAR *args) {
    MetalShader *shader = (MetalShader*)args[0].J;
    if(!shader || !args[1].O) {
        throw_nullpointerexception(vm);
        return;
    }
    
    char *name = string2c(args[1].O);
    for (MTLVertexAttribute* attr in shader->renderPipelineDesc.vertexFunction.vertexAttributes) {
        if (strcmp(name, [[attr name] UTF8String]) == 0) {
            vm->frames[vm->FP].retVal.J = attr.attributeIndex;
            return;
        }
    }
    vm->frames[vm->FP].retVal.J = -1;
}

void metal_digiplay_GL_uniformLocation(VM *vm, Object *method, VAR *args) {
    MetalShader *shader = (MetalShader*)args[0].J;
    if(!shader || !args[1].O) {
        throw_nullpointerexception(vm);
        return;
    }
    
    
    char *name = string2c(args[1].O);
    for (MTLVertexAttribute* attr in shader->renderPipelineDesc.vertexFunction.vertexAttributes) {
        if (strcmp(name, [[attr name] UTF8String]) == 0) {
            vm->frames[vm->FP].retVal.J = attr.attributeIndex;
            return;
        }
    }
    vm->frames[vm->FP].retVal.J = -1;
}

extern NativeMethodInfo digiplay_GL_NATIVES[];
void metal_setup_natives() {
    digiplay_GL_NATIVES[0].handle = &metal_digiplay_GL_viewport;
    digiplay_GL_NATIVES[1].handle = &metal_digiplay_GL_clearColor;
    digiplay_GL_NATIVES[2].handle = &metal_digiplay_GL_clear;
    digiplay_GL_NATIVES[3].handle = &metal_digiplay_GL_compileProgram;
    digiplay_GL_NATIVES[4].handle = &metal_digiplay_GL_attribLocation;
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


