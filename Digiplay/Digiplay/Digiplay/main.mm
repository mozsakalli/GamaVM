//
//  main.m
//  Digiplay
//
//  Created by mustafa on 14.04.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#import <UIKit/UIKit.h>
#include <sys/time.h>
#include <time.h>
#include <stddef.h>
#import <objc/runtime.h>
#include "jvm.h"


long long millis() {
    struct timeval now;
    gettimeofday(&now, NULL);
    return now.tv_sec * 1000000LL + now.tv_usec;
}

extern "C" void vm_test();

extern "C" {
    void *__platform_read_file(const char* path, int *size) {
        NSString* ret = [[NSBundle mainBundle] resourcePath];
        ret = [[ret stringByAppendingString:@"/assets/"] stringByAppendingString: [[NSString alloc] initWithUTF8String:path]];
        NSData* data = [[NSData alloc] initWithContentsOfFile:ret];
        *size = (int)[data length];
        return (char*)[data bytes];
    }
}

static BOOL didfin(id self, SEL _cmd,.../*, UIApplication *app, NSDictionary *opt*/) {
    va_list args;
    va_start(args, _cmd);
    void *vapp = va_arg(args, void*);
    void *vopt = va_arg(args, void*);
    va_end(args);
    UIApplication *app = (UIApplication*)vapp;
    Class cls = [[app delegate] class];
    
    printf("Worked!!! %p %p %s\n",vapp, vopt,class_getName(cls));
    return YES;
}

int mainx(int argc, char * argv[]) {
    /*
    id nsobject = objc_getClass("NSObject");
    id uiappdelegate = objc_getProtocol("UIApplicationDelegate");
    Class mydel = objc_allocateClassPair(nsobject, "MyDelegate", 0);
    SEL sel = sel_registerName("application:didFinishLaunchingWithOptions:");
    printf("add-proto: %d\n",class_addProtocol(mydel, uiappdelegate));
    objc_method_description mth = protocol_getMethodDescription(uiappdelegate, sel, false, true);
    printf("add-method: %d\n",class_addMethod(mydel, sel, (IMP)didfin, mth.types));
    objc_registerClassPair(mydel);
    //Method mth = class_getInstanceMethod(uiappdelegate, sel);
    
    printf("proto: %s\n", mth.types);
    UIApplicationMain(argc, argv, nil, @"MyDelegate");
    return 0;
    
    //vm_test();
     */
    //NSString * appDelegateClassName;
    vm_test();
        // Setup code that might create autoreleased objects goes here.
        //appDelegateClassName = NSStringFromClass([AppDelegate class]);
    //return UIApplicationMain(argc, argv, nil, appDelegateClassName);
    return 0;
}
