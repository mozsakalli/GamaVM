//
//  digiplay_native.m
//  Digiplay
//
//  Created by mustafa on 29.05.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <Metal/Metal.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

#include "jvm.h"


//static CGSize ScreenSize;
static CGPoint SafeScreenTopLeft;
static CGPoint SafeScreenBottomRight;
static BOOL IsTouching;
static CGPoint TouchPosition;
CAMetalLayer* MetalLayer;
id<MTLDevice> MetalDevice = nil;

@interface DigiplayView : UIView
@end

@implementation DigiplayView {
    //OpenGL fields
    EAGLContext* eaglContext;
    int framebuffer, colorbuffer, depthbuffer;
    
    
    CADisplayLink* displayLink;
}

+(Class)layerClass {
    Class cls = NSClassFromString(@"CAMetalLayer");
    if(cls) {
        MetalDevice = MTLCreateSystemDefaultDevice();
        if(MetalDevice) {
            NSLog(@"Metal support detected");
            return cls;
        }
    }
    return [CAEAGLLayer class];
}

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
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
extern void vm_test();
Object *digiplayIosPlatform;
Object *digiplayPlatformStepMethod;
VM *gamaVM;

-(void) updateTimerFired {
    static int initialized = 0;
    if(!initialized) {
        initialized = 1;
        vm_test();
    }
    
    if(gamaVM && digiplayPlatformStepMethod) {
        VAR args[1] = { {.O = digiplayIosPlatform} };
        call_void_method(gamaVM,digiplayPlatformStepMethod, &args[0]);
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

    CGFloat scale = [[UIScreen mainScreen] scale];
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

-(void) initMetal {
//#ifndef TARGET_OS_SIMULATOR
    //todo
    MetalLayer = (CAMetalLayer*)self.layer;
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
    //__digiplay_notify_haxe("app:background", NULL);
}
- (void)applicationDidBecomeActive:(UIApplication *)application {
    //__digiplay_notify_haxe("app:foreground", NULL);
    //val_call0(H->get());
    //value o = alloc_empty_object();
 }
@end

int main(int argc, char * argv[]) {
    @autoreleasepool {
        UIApplicationMain(argc, argv, nil, @"DigiplayAppDelegate");
    }
}

void digiplay_ios_IosPlatform_run(VM *vm, Object *method, VAR *args) {
    gamaVM = vm;
    digiplayIosPlatform = args[0].O;
    digiplayPlatformStepMethod = resolve_method(vm, "digiplay/Platform", "step", "()V", 0);
    
    CGRect bounds = [[UIScreen mainScreen] bounds];
    CGFloat scale = [[UIScreen mainScreen] scale];
    
    Object *resize_method = resolve_method(vm, "digiplay/Platform", "resize", "(IIIIII)V", 0);
    VAR vargs[7] = {
        { .O = digiplayIosPlatform },
        { .I = (jint)(bounds.size.width * scale) },
        { .I = (jint)(bounds.size.height * scale) },
        { .I = (jint)SafeScreenTopLeft.x },
        { .I = (jint)SafeScreenTopLeft.y },
        { .I = (jint)SafeScreenBottomRight.x },
        { .I = (jint)SafeScreenBottomRight.y },
    };
    call_void_method(vm, resize_method, &vargs[0]);
}

