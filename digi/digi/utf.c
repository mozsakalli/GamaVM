//
//  utf.c
//  digi
//
//  Created by mustafa on 7.06.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#include "vm.h"


int get_utf8_length(char *data, int length) {
    char *end = data + length;
    char *ptr = data;
    int jlen = 0;
    while(ptr < end) {
        unsigned int c = *ptr++;
        jlen++;
        if(c < 0x80) {}
        else if(c < 0xE0) ptr++;
        else if(c < 0xF0) ptr += 2;
        else ptr += 3;
    }
    return jlen;
}

void decode_utf8(char *data, int length, JCHAR* buf) {
    char *end = data + length;
    char *ptr = data;
    int jlen = 0;
    while (ptr < end) {
        unsigned int c = *ptr++;
        if (c < 0x80) {
            buf[jlen++] = c;
        } else if (c < 0xE0) {
            buf[jlen++] = (((c & 0x3F) << 6) | ((*ptr++) & 0x7F));
        } else if (c < 0xF0) {
            unsigned int c2 = *ptr++;
            buf[jlen++] = (char) (((c & 0x1F) << 12) | ((c2 & 0x7F) << 6) | ((*ptr++) & 0x7F));
        } else {
            unsigned int c2 = *ptr++;
            unsigned int c3 = *ptr++;
            buf[jlen++] = ((c & 0x0F) << 18) | ((c2 & 0x7F) << 12) | ((c3 & 0x7F) << 6) | ((*ptr++ & 0x7F));
        }
    }
}

char *jchar_to_ascii(JCHAR *chars, int len) {
    static char tmp[1024];
    for(int i=0; i<len; i++) tmp[i] = chars[i];
    tmp[len] = 0;
    return &tmp[0];
}

char *string_to_ascii(Object *str) {
    return jchar_to_ascii(STRCHARS(str), STRLEN(str));
}

JCHAR *char_to_jchar(char *ch, int *len) {
    int l = (int)strlen(ch);
    JCHAR *r = malloc(l * sizeof(JCHAR));
    for(int i=0; i<l; i++) r[i] = ch[i];
    *len = l;
    return r;
}
