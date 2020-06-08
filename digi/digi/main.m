//
//  main.m
//  digi
//
//  Created by mustafa on 7.06.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#import <UIKit/UIKit.h>
#include "vm.h"
//extern void gamavm_main(char *className, char *methodName, char *signature);

int main(int argc, char * argv[]) {
    NSString * appDelegateClassName;
    @autoreleasepool {
        // Setup code that might create autoreleased objects goes here.
        //appDelegateClassName = NSStringFromClass([AppDelegate class]);
    }
    //return UIApplicationMain(argc, argv, nil, appDelegateClassName);
    //gamavm_main("Main", "main", "()V");
    VM *vm = vm_init();
    vm_main(vm, "Main", "main", "()V");
    return 0;
}
