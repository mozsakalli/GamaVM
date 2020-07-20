//
//  ios_net.m
//  digi
//
//  Created by mustafa on 10.06.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "vm.h"

@interface digiplay_Net$Http : NSObject {
    NSURLConnection *connection;
    @public NSMutableData *receivedData;
    @public JLONG gamaHandle;
}
- (id)initWithURLAndPostParams:(NSString*)url postParams:(NSString*)postParams thiz:(JLONG)handle;
- (void)clear;
- (void)doCallback:(void*)data length:(int)length;
@end

@implementation digiplay_Net$Http

- (id) initWithURLAndPostParams:(NSString*)url postParams:(NSString*)postParams thiz:(JLONG)handle  {
    self = [super init];
    if (self) {
        NSMutableURLRequest *request = [[NSMutableURLRequest alloc] init];
        [request setURL:[NSURL URLWithString:url]];
        if(postParams != nil && [postParams length] > 0) {
            NSData *postData = [postParams dataUsingEncoding:NSASCIIStringEncoding allowLossyConversion:YES];
            NSString *postLength = [NSString stringWithFormat:@"%d", [postData length]];
            [request setHTTPMethod:@"POST"];
            [request setValue:postLength forHTTPHeaderField:@"Content-Length"];
            [request setValue:@"application/x-www-form-urlencoded" forHTTPHeaderField:@"Content-Type"];
            [request setHTTPBody:postData];
            [postLength release];
        }
        [request setTimeoutInterval:15];
        gamaHandle = handle;
        [self download:request];
        [request release];
        request = nil;
    }
    return self;
}


- (void)download:(NSURLRequest *)request {
    connection = request==nil ? nil : [[NSURLConnection alloc] initWithRequest:request delegate:self startImmediately:true];
    if(connection == nil) {
        [self doCallback:nil length:0];
    } else {
        [connection start];
    }
}

- (void)clear {
    if(connection != nil) {
        @try{[connection cancel];}@catch(NSException *exception){}
        @try {
            [connection release];
        }
        @catch (NSException *exception) {}
        connection = nil;
    }
    if(receivedData) {
        [receivedData release];
        receivedData = nil;
    }
}

- (void)dealloc {
    [self clear];
    [super dealloc];
}


#pragma mark NSURLConnection delegate methods

- (void)connection:(NSURLConnection *)conn didReceiveResponse:(NSURLResponse *)response {
    if(receivedData == nil) {
        receivedData = [[NSMutableData data] retain];
    }
}

// Called when a chunk of data has been downloaded.
- (void)connection:(NSURLConnection *)conn didReceiveData:(NSData *)data {
    [receivedData appendData:data];
}

- (void)connectionDidFinishLoading:(NSURLConnection *)conn {
    if(receivedData && gamaHandle) {
        int length = (int)[receivedData length];
        void* data = (void*)[receivedData bytes];
        [self doCallback:data length:length];
    }
}

// Forward errors
- (void)connection:(NSURLConnection *)conn didFailWithError:(NSError *)error {
    [self doCallback:nil length:0];
}

extern VM *gamaVM;
extern void vm_completeCompletable(JLONG gamaHandle, void *buffer, int length);
- (void)doCallback:(void*)data length:(int)length {
    /*
    if(gamaHandle) {
        gc_unprotect(gamaVM, (Object*)gamaHandle);
        if(data) {
            Object *method = find_method(gamaVM, callback->cls, L"onHttpSuccess", 13, L"([B)V", 5);
            if(method) {
                Object *ba = alloc_array_B(gamaVM, length, 0);
                memcpy(ba->instance, data, length);
                VAR args[2] = { {.O = callback }, {.O = ba }};
                invoke_interface_v(gamaVM, method, &args[0]);
            }
        } else {
            Object *method = find_method(gamaVM, callback->cls, L"onHttpFail", 10, L"()V", 3);
            if(method) {
                VAR args[1] = { {.O = callback }};
                invoke_interface_v(gamaVM, method, &args[0]);
            }
        }
    }*/
    void *buffer = NULL;
    if(data && length > 0) {
        buffer = malloc(length);
        memcpy(buffer, data, length);
    } else length = 0;
    
    vm_completeCompletable(gamaHandle, buffer, length);
    [self clear];
    [self release];
}

+(void)start:(JLONG)handle url:(NSString*)url post:(NSString*)post {
    gc_protect(gamaVM, (Object*)handle);
    digiplay_Net$Http *http = [[digiplay_Net$Http alloc] initWithURLAndPostParams:url postParams:post thiz:handle];
    [http retain];
}
@end


