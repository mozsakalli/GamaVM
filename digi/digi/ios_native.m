//
//  native_ios.m
//  digi
//
//  Created by mustafa on 7.06.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "vm.h"
#include "miniz.h"

void *read_file(const char* path, int *size) {
    NSString* ret = [[NSBundle mainBundle] resourcePath];
    ret = [[ret stringByAppendingString:@"/assets/"] stringByAppendingString: [[NSString alloc] initWithUTF8String:path]];
    NSData* data = [[NSData alloc] initWithContentsOfFile:ret];
    *size = (int)[data length];
    return (char*)[data bytes];
}

typedef struct JARInfo {
    char path[256];
    mz_zip_archive zip;
    struct JARInfo *next;
} JARInfo;
static JARInfo *JARS = NULL;


void *read_jar_resource(JCHAR *jarName, int jarNameLen, JCHAR *name, int nameLen, int *outLen) {
    NSString* path = [[NSBundle mainBundle] resourcePath];
    path = [[path stringByAppendingString:@"/assets/"] stringByAppendingString: [[NSString alloc] initWithCharacters:jarName length:jarNameLen]];
    char cpath[256];
    snprintf(cpath, 255, "%s", [path UTF8String]);
    [path release];
    JARInfo *jar = JARS;
    while(jar) {
        if(!strcmp(jar->path, cpath)) break;
        jar = jar->next;
    }
    
    if(!jar) {
        FILE *file = fopen(cpath, "r");
        if(!file) return NULL;
    }
    
    return NULL;
}

void *read_class_file(JCHAR *name, int len) {
    
    int jarSize;
    void *jar = read_file("boot.jar", &jarSize);
    if(!jar) return NULL;

    char tmp[512];
    char *str = tmp;
    mz_zip_archive zip = {0};
    
    if(mz_zip_reader_init_mem(&zip, jar, jarSize, 0) == MZ_FALSE) {
        free(jar);
        return NULL;
    }
    memcpy(str, jchar_to_ascii(name, len), len);
    str += len;
    memcpy(str, ".class", 6);
    len += 6;
    tmp[len] = 0;
    //sprintf(str, ".class");
    int file_index = mz_zip_reader_locate_file(&zip, tmp, NULL, 0);//
    mz_zip_archive_file_stat file_stat = {0};
    if (!mz_zip_reader_file_stat(&zip, file_index, &file_stat)) {
        free(jar);
        return NULL;
    }
    size_t uncompressed_size = (size_t) file_stat.m_uncomp_size;
    void *p = mz_zip_reader_extract_file_to_heap(&zip, file_stat.m_filename, &uncompressed_size, 0);
    free(jar);
    if (!p) {
        return NULL;
    } else {
        void *ret = malloc(uncompressed_size);
        memcpy(ret, p, uncompressed_size);
        mz_free(p);
        return ret;
    }

    return NULL;
}

void java_lang_System_SystemOutStream_printImpl(VM *vm, Object *method, VAR *args) {
    Object *string = args[0].O;
    if(!string) return;
    
    NSString *ns = [[NSString alloc] initWithCharacters:STRCHARS(string) length:STRLEN(string)];
    NSLog(@"%@", ns);
    [ns release];
}

extern VM *gamaVM;
void vm_completeCompletable(JLONG gamaHandle, void *buffer, int length) {
    if(!gamaHandle) return;
    Object *target = (Object*)gamaHandle;
    gc_unprotect(gamaVM, target);

    static int methodIndex = -1;
    if(methodIndex == -1) {
        Object *m = resolve_method(gamaVM, gamaVM->sysClassLoader,
        (JCHAR*)L"digiplay/Completable",20, (JCHAR*)L"complete",8, (JCHAR*)L"(JI)V",5);
        if(!m) return;
        methodIndex = MTH(m, iTableIndex);
    }


    Object *method = CLS(target->cls, itable)[methodIndex];
    VAR args[3] = {{.O = target}, {.J = (JLONG)buffer}, {.I = length}};
    CALLVM_V(gamaVM, method, &args[0]);
}
