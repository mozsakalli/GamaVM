//
//  gc.c
//  digi
//
//  Created by mustafa on 7.06.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#include "vm.h"

HeapBlock *alloc_heap_block() {
    HeapBlock *b = (HeapBlock*)malloc(sizeof(HeapBlock));
    Object *hf = &b->objects[0];
    b->free = hf;
    Object *pre = hf;
    for(int i=0; i<HEAP_OBJECTS_PER_BLOCK; i++) {
        hf->gc.free = 1;
        //hf->gc_version = 0xFFFF;
        hf++;
        pre->cls = hf;
        pre = hf;
    }
    b->objects[HEAP_OBJECTS_PER_BLOCK-1].cls = NULL;
    b->used = 0;
    //printf("HeapBlock %p -> %p\n", &b->objects[0], &b->objects[HEAP_OBJECT_COUNT-1]);
    return b;
}
Object *alloc_heap(VM *vm) {
    HeapBlock *b = vm->heap;
    while(b) {
        if(b->free) {
            Object *o = b->free;
            b->free = b->free->cls;
            //printf(" --heap-o: %p\n", o);
            return o;
        }
        b = b->next;
    }
    
    //not found allocate new block
    b = alloc_heap_block();
    b->next = vm->heap;
    vm->heap = b;
    
    Object *o = (Object*)b->free;
    b->free = b->free->cls;
    //printf(" --heap-o: %p\n", o);
    return o;
}

Object *alloc_object(VM *vm, Object *cls, int atomic) {
    Object *o = atomic ? (Object*)malloc(sizeof(Object)) : alloc_heap(vm);
    o->cls = cls;
    o->length = 0;
    o->gc.version = vm->gcVersion;
    o->gc.atomic = atomic;
    o->gc.free = 0;
    
    int size = CLS(cls, instanceSize);
    if(size > 0) {
        o->instance = vm_alloc(size);
    } else o->instance = NULL;
    
    return o;
}

Object *alloc_array(VM *vm, Object *cls, int length, int atomic) {
    Object *arr = alloc_object(vm, cls, atomic);
    arr->length = length;
    Object *element = CLS(cls, elementClass);
    int primitiveSize = CLS(element, primitiveSize);
    arr->instance = vm_alloc((primitiveSize ? primitiveSize : sizeof(Object*)) * length);
    return arr;
}

Object *alloc_class(VM *vm) {
    Object *cls = alloc_object(vm, vm->jlClass, 1);
    CLS(cls, vm) = vm;
    return cls;
}

void free_class(Object *cls) {
    
}

Object *alloc_string_ascii(VM *vm, char *chars, int atomic) {
    int len = (int)strlen(chars);
    Object *charArray = alloc_array(vm, get_arrayclass_of(vm, vm->primClasses[PRIM_C]), len, atomic);
    for(int i=0; i<len; i++) ((JCHAR*)charArray->instance)[i] = chars[i];
    
    Object *str = alloc_object(vm, vm->jlString, atomic);
    STR(str, chars) = charArray;
    STR(str, offset) = 0;
    STR(str, length) = len;
    
    return str;
}

Object *alloc_string_java(VM *vm, JCHAR *chars, int len, int atomic) {
    Object *charArray = alloc_array(vm, get_arrayclass_of(vm, vm->primClasses[PRIM_C]), len, atomic);
    memcpy(charArray->instance, chars, len * sizeof(JCHAR));
    
    Object *str = alloc_object(vm, vm->jlString, atomic);
    STR(str, chars) = charArray;
    STR(str, offset) = 0;
    STR(str, length) = len;
    
    return str;
}

Object *alloc_string_utf8(VM *vm, char *chars, int datalen, int atomic) {
    int charlen = get_utf8_length(chars, datalen);
    Object *charArray = alloc_array(vm, get_arrayclass_of(vm, vm->primClasses[PRIM_C]), charlen, atomic);
    decode_utf8(chars, datalen, (JCHAR*)charArray->instance);
    
    Object *str = alloc_object(vm, vm->jlString, atomic);
    STR(str, chars) = charArray;
    STR(str, offset) = 0;
    STR(str, length) = charlen;
    
    return str;
}

