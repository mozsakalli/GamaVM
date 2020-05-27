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

@interface AppDelegate : NSObject<UIApplicationDelegate>
@end
@implementation AppDelegate
-(BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary*)launchOptions{
    
    return YES;
}
@end

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

typedef struct TT {
    int length;
    char C[0];
} TT;
int main(int argc, char * argv[]) {
    /*
    printf("%d\n", sizeof(TT));
    
    TT *t = (TT*)malloc(sizeof(TT) + 10 * sizeof(int));
    t->length = 10;
    for(int i=0; i<t->length; i++)
        *((int*)t->C + i) = i;
    
    for(int i=0; i<t->length; i++)
        printf("%d\n", *((int*)t->C + i));
    */
    vm_test();
     
    //NSString * appDelegateClassName;
    @autoreleasepool {
        // Setup code that might create autoreleased objects goes here.
        //appDelegateClassName = NSStringFromClass([AppDelegate class]);
    }
    //return UIApplicationMain(argc, argv, nil, appDelegateClassName);
    return 0;
}
