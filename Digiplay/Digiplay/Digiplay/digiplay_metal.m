//
//  digiplay_metal.m
//  Digiplay
//
//  Created by mustafa on 30.05.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <Metal/Metal.h>
#include "jvm.h"

extern CAMetalLayer* MetalLayer;
extern id<MTLDevice> MetalDevice;

typedef struct Buffer_Metal {
    int stride;
    id<MTLBuffer> buffer;
} Buffer_Metal;


