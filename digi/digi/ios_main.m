//
//  digiplay_native.m
//  Digiplay
//
//  Created by mustafa on 29.05.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

//#define METAL_ENABLED

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <Metal/Metal.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

#include "vm.h"

//static CGSize ScreenSize;
static CGPoint SafeScreenTopLeft;
static CGPoint SafeScreenBottomRight;
static BOOL IsTouching;
static CGPoint TouchPosition;

CAMetalLayer* MetalLayer;
id<MTLDevice> MetalDevice = nil;
id<CAMetalDrawable> MetalDrawable;
id<MTLTexture> MetalDepth = nil;
id<MTLTexture> MetalStencil = nil;
MTLRenderPassDescriptor *MetalFramebuffer;

Object *digiplayPlatformStepMethod;
VM *gamaVM;

@interface DigiplayView : UIView
@end

@implementation DigiplayView {
    //OpenGL fields
    EAGLContext* eaglContext;
    int framebuffer, colorbuffer, depthbuffer;
    
    
    CADisplayLink* displayLink;
}

+(Class)layerClass {
#ifdef METAL_ENABLED
    Class cls = NSClassFromString(@"CAMetalLayer");
    if(cls) {
        MetalDevice = MTLCreateSystemDefaultDevice();
        if(MetalDevice) {
            NSLog(@"Metal support detected");
            return cls;
        }
    }
#endif
    return [CAEAGLLayer class];
}

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        [self setContentScaleFactor: [[UIScreen mainScreen] scale] ];
        framebuffer = -1;
        
        if(!MetalDevice)
            [self initOpenGL];
        else
            [self initMetal];
    }
    return self;
}

- (void)layoutSubviews {
    [super layoutSubviews];
    if(!MetalDevice) {
        if(framebuffer == -1)
            [self createOpenGLBuffers];
    } else {
        //if(!MetalDrawable) [self createMetalBuffers];
    }
    
    if([self respondsToSelector:NSSelectorFromString(@"safeAreaInsets")]) {
        UIEdgeInsets i = self.safeAreaInsets;
        SafeScreenTopLeft = CGPointMake(i.left, i.top);
        SafeScreenBottomRight = CGPointMake(i.right, i.bottom);
    } else {
        SafeScreenTopLeft = CGPointMake(0,0);
        SafeScreenBottomRight = CGPointMake(0,0);
    }
}

- (void)didMoveToWindow {
    if(self.window) {
        if(!MetalDevice) {
            if(framebuffer == -1) [self createOpenGLBuffers];
        } else {
            //if(!MetalDrawable) [self createMetalBuffers];
        }
    }
}

-(void) startAnimation {
    if(!displayLink) {
        displayLink=[NSClassFromString(@"CADisplayLink") displayLinkWithTarget:self selector:@selector(updateTimerFired)];
        [displayLink setFrameInterval:1];
        [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    }
}
//extern void vm_test();
//extern void metal_begin_frame();
//extern void metal_end_frame();


-(void) updateTimerFired {
    static int initialized = 0;
    if(!initialized) {
        initialized = 1;
        gamaVM = vm_init();
        vm_main(gamaVM, "Main", "main", "()V");
    }
    
    if(MetalDevice) {
        [self createMetalBuffers];
        //metal_begin_frame();
    } else {
        
    }
    
    if(gamaVM && digiplayPlatformStepMethod) {
        //VAR args[1] = { {.O = digiplayPlatform} };
        CALLVM_V(gamaVM, digiplayPlatformStepMethod, NULL);//&args[0]);
    }
    if(!MetalDevice)
        [self present];
    else {
        //metal_end_frame();
        [MetalDrawable release];
        MetalDrawable = nil;
    }
}

-(void) present {
    if([EAGLContext currentContext] != eaglContext)
        [EAGLContext setCurrentContext:eaglContext];
    glBindRenderbuffer(GL_RENDERBUFFER, colorbuffer);
    [eaglContext presentRenderbuffer:GL_RENDERBUFFER];
}

-(void) initOpenGL {
    CAEAGLLayer* layer = (CAEAGLLayer*)self.layer;
    layer.opaque = true;
    layer.drawableProperties = @{
        kEAGLDrawablePropertyRetainedBacking:@(NO),
        kEAGLDrawablePropertyColorFormat:kEAGLColorFormatRGBA8
    };
    eaglContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    if([EAGLContext currentContext] != eaglContext)
        [EAGLContext setCurrentContext:eaglContext];
}

-(void) createOpenGLBuffers {
    if([EAGLContext currentContext] != eaglContext)
        [EAGLContext setCurrentContext:eaglContext];

    
    CGFloat scale = [[self layer] contentsScale];
    int ScreenSizeWidth = (int)(self.layer.bounds.size.width * scale);
    int ScreenSizeHeight = (int)(self.layer.bounds.size.height * scale);
    
    glGenFramebuffers(1, (GLuint*)&framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    // Create our Depth buffer. Color buffer must be the last one bound
    glGenRenderbuffers(1, (GLuint*)&depthbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthbuffer);
    
    int internalFormat = GL_DEPTH24_STENCIL8_OES;
    glRenderbufferStorage(GL_RENDERBUFFER, internalFormat, ScreenSizeWidth, ScreenSizeHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthbuffer);
    if (internalFormat == GL_DEPTH24_STENCIL8_OES)
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthbuffer);

    glGenRenderbuffers(1, (GLuint*)&colorbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, colorbuffer);

    // TODO: EAGLContext.RenderBufferStorage returns false
    //       on all but the first call.  Nevertheless, it
    //       works.  Still, it would be nice to know why it
    //       claims to have failed.
    [eaglContext renderbufferStorage:GL_RENDERBUFFER fromDrawable:(CAEAGLLayer*)self.layer];
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorbuffer);

    int status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        NSLog(@"OpenGL FrameBuffer could not initialized");
    }
}

-(void) createMetalBuffers {
    if(!MetalDrawable) {
    MetalDrawable=[MetalLayer nextDrawable];
    [MetalDrawable retain];
    /*
    if (MetalDepth==nil) {
        MTLTextureDescriptor *td=[MTLTextureDescriptor new];
        td.pixelFormat=MTLPixelFormatDepth32Float;
        td.width=[MetalDrawable.texture width];
        td.height=[MetalDrawable.texture height];
        td.usage=MTLStorageModePrivate;
        MetalDepth=[MetalDevice newTextureWithDescriptor:td];
        td.pixelFormat=MTLPixelFormatStencil8;
        MetalStencil=[MetalDevice newTextureWithDescriptor:td];
    }*/
    MetalFramebuffer.colorAttachments[0].texture=MetalDrawable.texture;
    MetalFramebuffer.depthAttachment.texture=MetalDepth;
    MetalFramebuffer.depthAttachment.loadAction=MTLLoadActionClear;
    MetalFramebuffer.stencilAttachment.texture=MetalStencil;
    MetalFramebuffer.stencilAttachment.loadAction=MTLLoadActionClear;
    int framebufferWidth=[MetalDrawable.texture width];
    int framebufferHeight=[MetalDrawable.texture height];
    MetalFramebuffer.colorAttachments[0].loadAction=MTLLoadActionClear;
    MetalFramebuffer.colorAttachments[0].clearColor=MTLClearColorMake(1,1,1,1);
    
    //gpu_metal_init();
    /*
    if ((lfbw!=framebufferWidth)||(lfbh!=framebufferHeight))
        gdr_surfaceChanged(framebufferWidth,framebufferHeight);
    lfbw=framebufferWidth;
    lfbh=framebufferHeight;
     */
    }
}

//extern void metal_setup_natives();
-(void) initMetal {
//#ifndef TARGET_OS_SIMULATOR
    //todo
    MetalLayer = (CAMetalLayer*)self.layer;
    MetalFramebuffer=[MTLRenderPassDescriptor renderPassDescriptor];
    [MetalFramebuffer retain];
    //metal_setup_natives();
//#endif
}

@end

///////////////////////////
//DigiplayWindow
//////////////////////////
@interface DigiplayWindow : UIWindow
@end

@implementation DigiplayWindow

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    /*
    NSArray *touchArr = [touches allObjects];
    UITouch *aTouch = [touchArr objectAtIndex:0];
    IsTouching = YES;
    TouchPosition = [aTouch locationInView:aTouch.view];
    TouchPosition.x *= ScreenScaleFactor;
    TouchPosition.y *= ScreenScaleFactor;
     */
}

- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    /*
    NSArray *touchArr = [touches allObjects];
    UITouch *aTouch = [touchArr objectAtIndex:0];
    IsTouching = NO;
    TouchPosition = [aTouch locationInView:aTouch.view];
    TouchPosition.x *= ScreenScaleFactor;
    TouchPosition.y *= ScreenScaleFactor;
     */
}

- (void)touchesMoved:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    /*
    NSArray *touchArr = [touches allObjects];
    UITouch *aTouch = [touchArr objectAtIndex:0];
    IsTouching = YES;
    TouchPosition = [aTouch locationInView:aTouch.view];
    TouchPosition.x *= ScreenScaleFactor;
    TouchPosition.y *= ScreenScaleFactor;
     */
}
@end

///////////////////////////
//DigiplayViewController
//////////////////////////
@interface DigiplayViewController : UIViewController
@end

@implementation DigiplayViewController

- (void)loadView {
    self.view = [[DigiplayView alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    self.view.clearsContextBeforeDrawing = false;
}

- (void)viewDidLoad {
    [(DigiplayView*)self.view startAnimation];
    if (@available(iOS 11.0, *)) {
        [self setNeedsUpdateOfHomeIndicatorAutoHidden];
    }
}
@end

@interface DigiplayAppDelegate : NSObject<UIApplicationDelegate>
@end

@implementation DigiplayAppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    UIWindow* window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    window.rootViewController = [[DigiplayViewController alloc] init];
    
    [window makeKeyAndVisible];
    return YES;
}
- (void)applicationDidEnterBackground:(UIApplication *)application {
    if(gamaVM) {
        //Object *mth = resolve_method(gamaVM, "digiplay/Platform", "pause", "()V", 0);
        //VAR args[1] = { {.O = digiplayPlatform}};
        //if(mth) call_void_method(gamaVM, mth, &args[0]);
    }
}
- (void)applicationDidBecomeActive:(UIApplication *)application {
    if(gamaVM) {
        //Object *mth = resolve_method(gamaVM, "digiplay/Platform", "resume", "()V", 0);
        //VAR args[1] = { {.O = digiplayPlatform}};
        //if(mth) call_void_method(gamaVM, mth, &args[0]);
    }
 }
@end

int main(int argc, char * argv[]) {
    @autoreleasepool {
        UIApplicationMain(argc, argv, nil, @"DigiplayAppDelegate");
    }
}

@interface digiplay_Platform : NSObject
@end

@implementation digiplay_Platform

+(NSData*) readAsset:(NSString*) path {
    if(!path) return nil;
    NSString* ret = [[NSBundle mainBundle] resourcePath];
    ret = [[ret stringByAppendingString:@"/assets/"] stringByAppendingString: path];
    NSData* data = [[NSData alloc] initWithContentsOfFile:ret];
    //if(data) [data retain];
    return data;
}

+(void) run {
    digiplayPlatformStepMethod = resolve_method(gamaVM, gamaVM->sysClassLoader, L"digiplay/Platform",17, L"step",4, L"()V", 3);
    
    CGRect bounds = [[UIScreen mainScreen] bounds];
    CGFloat scale = [[UIScreen mainScreen] scale];
    
    Object *resize_method = resolve_method(gamaVM, gamaVM->sysClassLoader, L"digiplay/Platform",17, L"resize",6, L"(II)V", 5);
    VAR vargs[7] = {
        //{ .O = digiplayPlatform },
        { .I = (JINT)(bounds.size.width * scale) },
        { .I = (JINT)(bounds.size.height * scale) },
    };
    CALLVM_V(gamaVM, resize_method, &vargs[0]);
}
@end

/*
void Java_digiplay_Platform_run(VM *vm, Object *method, VAR *args) {
    digiplayPlatform = args[0].O;
    digiplayPlatformStepMethod = resolve_method(vm, L"digiplay/Platform",17, L"step",4, L"()V", 3);
    
    CGRect bounds = [[UIScreen mainScreen] bounds];
    CGFloat scale = [[UIScreen mainScreen] scale];
    
    Object *resize_method = resolve_method(vm, L"digiplay/Platform",17, L"resize",6, L"(II)V", 5);
    VAR vargs[7] = {
        //{ .O = digiplayPlatform },
        { .I = (JINT)(bounds.size.width * scale) },
        { .I = (JINT)(bounds.size.height * scale) },
    };
    CALLVM_V(vm, resize_method, &vargs[0]);
}
*/
