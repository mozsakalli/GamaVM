//
//  native_ios.m
//  digi
//
//  Created by mustafa on 7.06.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "gamavm.h"
#include "miniz.h"

void *read_file(const char* path, int *size) {
    NSString* ret = [[NSBundle mainBundle] resourcePath];
    ret = [[ret stringByAppendingString:@"/assets/"] stringByAppendingString: [[NSString alloc] initWithUTF8String:path]];
    NSData* data = [[NSData alloc] initWithContentsOfFile:ret];
    *size = (int)[data length];
    return (char*)[data bytes];
}

void *read_class_file(jchar *name, int len) {
    int jarSize;
    void *jar = read_file("jvm_test.jar", &jarSize);
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
    if (!p) {
        free(jar);
        return NULL;
    } else {
        void *ret = malloc(uncompressed_size);
        memcpy(ret, p, uncompressed_size);
        mz_free(p);
        return ret;
    }

    return NULL;
}
