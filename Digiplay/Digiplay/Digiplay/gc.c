//
//  alloc.c
//  Digiplay
//
//  Created by mustafa on 24.05.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#define GC_THREADS

#include "jvm.h"
#include "gc.h"

#define HEAP_OBJECT_COUNT    32768

/*
typedef struct __attribute__ ((packed)) HeapFree {
    struct HeapFree *next;
    void* tmp;
    int tmp1;
    int tmp2;
} HeapFree;
*/

typedef struct HeapBlock {
    Object objects[HEAP_OBJECT_COUNT];
    struct HeapBlock *next;
    Object *free;
    int used;
} HeapBlock;

typedef struct Heap {
    HeapBlock *blocks;
} Heap;

HeapBlock *alloc_heap_block() {
    HeapBlock *b = (HeapBlock*)malloc(sizeof(HeapBlock));
    Object *hf = &b->objects[0];
    b->free = hf;
    Object *pre = hf;
    for(int i=0; i<HEAP_OBJECT_COUNT; i++) {
        hf->gc.free = 1;
        //hf->gc_version = 0xFFFF;
        hf++;
        pre->cls = hf;
        pre = hf;
    }
    b->objects[HEAP_OBJECT_COUNT-1].cls = NULL;
    b->used = 0;
    printf("HeapBlock %p -> %p\n", &b->objects[0], &b->objects[HEAP_OBJECT_COUNT-1]);
    return b;
}
Object *alloc_heap(VM *vm) {
    Heap *heap = vm->heap;
    HeapBlock *b = heap->blocks;
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
    b->next = heap->blocks;
    heap->blocks = b;
    
    Object *o = (Object*)b->free;
    b->free = b->free->cls;
    //printf(" --heap-o: %p\n", o);
    return o;
}

void alloc_init(VM *vm) {
    vm->heap = (Heap*)malloc(sizeof(Heap));
    memset(vm->heap, 0, sizeof(Heap));
}

ObjectPtr alloc_object(VM *vm,Object *clso) {
    ObjectPtr o = alloc_heap(vm); //(ObjectPtr)malloc(sizeof(Object));
    o->cls = clso;
    o->length = 0;
    o->gc.version = vm->gc_version;
    o->gc.free = 0;
    o->gc.atomic = 0;
    
    ClassFields *cf = (ClassFields*)clso->instance;
    if(cf->instanceSize > 0) {
        o->instance = malloc(cf->instanceSize);
        memset(o->instance, 0, cf->instanceSize);
    } else cf->fields = NULL;
    return o;
}

ObjectPtr alloc_object_array(VM *vm, Object *cls, int length) {
    Object *arr = alloc_heap(vm);  // (Object*)malloc(sizeof(Object));
    arr->length = length;
    arr->cls = cls;
    arr->gc.version = vm->gc_version;
    arr->gc.free = 0;
    arr->gc.atomic = 0;
    arr->instance = malloc(length * sizeof(Object*));
    memset(arr->instance, 0, length * sizeof(Object*));
    return arr;
}

ObjectPtr alloc_prim_array(VM *vm, Object *clso, int length) {
    ClassFields *cf = (ClassFields*)clso->instance;
    ClassFields *cfe = (ClassFields*)cf->elementClass->instance;
    Object *arr = alloc_heap(vm); //(Object*)malloc(sizeof(Object));
    arr->length = length;
    arr->cls = clso;
    arr->gc.version = vm->gc_version;
    arr->gc.free = 0;
    arr->gc.atomic = 1;
    arr->instance = malloc(length * cfe->instanceSize);
    memset(arr->instance, 0, length * cfe->instanceSize);
    return arr;
}

Object* alloc_string(VM *vm, char *chars) {
    int len = (int)strlen(chars);
    Object* jchars = alloc_prim_array(vm, &java_lang_C1D, len);
    for(int i=0; i<len; i++)
        ARRAY_DATA_C(jchars)[i] = chars[i];
    
    Object *str = alloc_object(vm, &java_lang_String);
    StringFields *fields = str->instance;
    fields->length = len;
    fields->chars = jchars;
    
    return str;
}

ObjectPtr alloc_object_nogc(VM *vm,Object *clso) {
    ObjectPtr o = (ObjectPtr)malloc(sizeof(Object));
    o->cls = clso;
    o->gc.atomic = 1;
    ClassFields *cf = (ClassFields*)clso->instance;
    if(cf->instanceSize > 0) {
        o->instance = malloc(cf->instanceSize);
        memset(o->instance, 0, cf->instanceSize);
    } else cf->fields = NULL;
    return o;
}

ObjectPtr alloc_prim_array_nogc(VM *vm, Object *clso, int length) {
    ClassFields *cf = (ClassFields*)clso->instance;
    ClassFields *cfe = (ClassFields*)cf->elementClass->instance;
    Object *arr = (Object*)malloc(sizeof(Object));
    arr->length = length;
    arr->cls = clso;
    arr->instance = malloc(length * cfe->instanceSize);
    arr->gc.atomic = 1;

    memset(arr->instance, 0, length * cfe->instanceSize);
    return arr;
}

ObjectPtr alloc_object_array_nogc(VM *vm, Object *cls, int length) {
    Object *arr = (Object*)malloc(sizeof(Object));
    arr->length = length;
    arr->cls = cls;
    arr->instance = malloc(length * sizeof(Object*));
    arr->gc.atomic = 1;
    memset(arr->instance, 0, length * sizeof(Object*));
    return arr;
}

Object* alloc_string_nogc(VM *vm, char *chars) {
    int len = (int)strlen(chars);
    Object* jchars = alloc_prim_array_nogc(vm, &java_lang_C1D, len);
    for(int i=0; i<len; i++)
        ARRAY_DATA_C(jchars)[i] = chars[i];
    
    Object *str = alloc_object_nogc(vm, &java_lang_String);
    StringFields *fields = str->instance;
    fields->length = len;
    fields->chars = jchars;
    str->gc.atomic = 1;

    return str;
}

Object* alloc_string_utf_nogc(VM *vm, jchar *chars, jint len) {
    Object* jchars = alloc_prim_array_nogc(vm, &java_lang_C1D, len);
    memcpy(jchars->instance, chars, len * sizeof(jchar));
    
    Object *str = alloc_object_nogc(vm, &java_lang_String);
    StringFields *fields = str->instance;
    fields->length = len;
    fields->chars = jchars;
    str->gc.atomic = 1;

    return str;
}

void gc_queue_object(VM *vm, Object *o) {
    if(!o || o->gc.version == vm->gc_version) return;
    o->gc.version = vm->gc_version;
    if(!o->instance || o->gc.atomic) return;
    if(vm->markQueue.S == vm->markQueue.C) {
        int size = vm->markQueue.C;
        if(size == 0) size = 4096; else size *= 2;
        Object *R = vm->markQueue.C > 0 ? vm->markQueue.Q[vm->markQueue.R] : NULL;
        Object *W = vm->markQueue.C > 0 ? vm->markQueue.Q[vm->markQueue.W] : NULL;
        vm->markQueue.Q = realloc(vm->markQueue.Q, size * sizeof(Object*));
        vm->markQueue.C = size;
        //adjust read/write pointers
        if(R || W) {
            for(int i=0; i<vm->markQueue.C; i++) {
                if(vm->markQueue.Q[i] == R) { vm->markQueue.R = i; R = NULL; }
                if(vm->markQueue.Q[i] == W) { vm->markQueue.W = i; W = NULL; }
                if(!R && !W) break;
            }
        }
    }
    vm->markQueue.Q[vm->markQueue.W] = o;
    vm->markQueue.W = (vm->markQueue.W + 1) % vm->markQueue.C;
    vm->markQueue.S++;
    //ClassFields *cls = o->cls->instance;
    //printf("--queue: %s %p\n", string2c(cls->name), o);
}

void gc_mark_class(VM *vm, ClassFields *cls) {
    if(!cls || !cls->fields || cls->primitiveType || cls->elementClass || !cls->globals) return;
    int len = cls->fields->length;
    for(int i=0; i<len; i++) {
        Object *fo = ARRAY_DATA_O(cls->fields)[i];
        FieldFields *f = fo->instance;
        if(IS_STATIC(f)) {
            StringFields *str = f->signature->instance;
            char type = ARRAY_DATA_C(str->chars)[0];
            if(type == 'L' || type == '[') {
                Object *field_value = *((ObjectPtr*)(cls->globals + f->offset));
                if(field_value) {
                    //printf("  field: %s\n",string2c(f->name));
                    gc_queue_object(vm, field_value);
                }
            }
        }
    }
}

#define COUNT_PER_TICK 128
#define GCSTEP_INIT         0
#define GCSTEP_MARKCLASSES  1
#define GCSTEP_MARKSTACK    2
#define GCSTEP_MARKQUEUE    3
#define GCSTEP_SWEEP        4

void gc_mark_classes(VM *vm) {
    Object *current = vm->gc_ptr;
    int count = 0;
    while(current && count++ < COUNT_PER_TICK) {
        ClassFields *cls = current->instance;
        if(current != &java_lang_Class) {
        //if(current->gc_version != 0xFFFF) {
            //printf("Mark Class Globals: %s %p\n", string2c(cls->name), current);
            gc_mark_class(vm, cls);
        }
        current = cls->listNext;
    }
    
    if(!current) {
        vm->gc_step = GCSTEP_MARKSTACK;
    } else {
        vm->gc_ptr = current;
    }
}

int heap_is_object(Heap *heap, void *o) {
    HeapBlock *b = heap->blocks;
    while(b) {
        if(o >= (void*)&b->objects[0] && o <= (void*)&b->objects[HEAP_OBJECT_COUNT-1]) return 1;
        b = b->next;
    }
    return 0;
}

void gc_mark_stack(VM *vm) {
    if(!vm->heap) return;
    Heap *heap = (Heap*)vm->heap;
    for(int i=0; i<vm->SP; i++) {
        void *o = vm->stack[i].O;
        if(o && heap_is_object(heap, o))
            gc_queue_object(vm, (Object*)o);
    }
    
    vm->gc_step = GCSTEP_MARKQUEUE;
}

void gc_mark_queue(VM *vm) {
    int count = 0;
    
    while(count++ < COUNT_PER_TICK && vm->markQueue.S > 0) {
        Object *o = vm->markQueue.Q[vm->markQueue.R];
        vm->markQueue.R = (vm->markQueue.R + 1) % vm->markQueue.C;
        vm->markQueue.S--;
        
        ClassFields *cls = o->cls->instance;
        
        //mark fields
        while(cls) {
            //printf("Mark Class: %s super=%p fields=%p\n", string2c(cls->name), cls->superClass, cls->fields);
            if(cls->instanceSize > 0 && cls->fields && cls->fields->length > 0) {
                //printf("WalkObject: %s %p\n", string2c(o->cls->name), o);
                int len = cls->fields->length;
                for(int i=0; i<len; i++) {
                    Object *fo = ARRAY_DATA_O(cls->fields)[i];
                    FieldFields *f = fo->instance;
                    if(!IS_STATIC(f)) {
                        StringFields *str = f->signature->instance;
                        char type = ARRAY_DATA_C(str->chars)[0];
                        if(type == 'L' || type == '[') {
                            Object *field_value = *FIELD_PTR_O(o, f->offset);
                            if(field_value) {
                                //printf("  field: %s\n",string2c(f->name));
                                gc_queue_object(vm, field_value);
                            }
                        }
                    }
                }
            }

            //mark array
            if(cls->elementClass) {
                ClassFields *ecls = cls->elementClass->instance;
                if(!ecls->primitiveType) {
                    int len = o->length;
                    for(int i=0; i<len; i++) {
                        Object *array_item = ARRAY_DATA_O(o)[i];
                        if(array_item) gc_queue_object(vm, array_item);
                    }
                }
                break;
            }
            
            //printf("---- fin ----\n");
            
            if(cls->superClass) {
                cls = cls->superClass->instance;
            } else break;

        }
    }
    
    //mark finished
    if(vm->markQueue.S == 0) {
        vm->gc_step = GCSTEP_SWEEP;
        vm->gc_ptr = ((Heap*)vm->heap)->blocks;
        vm->gc_blockptr = 0;
    }
}

void gc_sweep(VM *vm) {
    HeapBlock *blk = vm->gc_ptr;
    int blk_ndx = vm->gc_blockptr;
    int count = 0;
    int version = vm->gc_version;
    while(blk && count < COUNT_PER_TICK) {
        while(blk_ndx < HEAP_OBJECT_COUNT && count++ < COUNT_PER_TICK) {
            Object *o = &blk->objects[blk_ndx];
            if(!o->gc.free && o->gc.version != version) {

                ClassFields *cls = o->cls->instance;
                if(cls && cls->finalizer) {
                    VAR args[1] = { {.O = o} };
                    ((JVM_CALL)(MTH_FIELD(cls->finalizer, entry)))(vm, cls->finalizer, &args[0]);
                }
                //free object
                o->gc.free = 1;
                o->cls = blk->free;
                blk->free = o;
                
                if(o->instance) {
                    free(o->instance);
                    o->instance = NULL;
                }
            }
            blk_ndx++;
        }
        if(blk_ndx == HEAP_OBJECT_COUNT) {
            blk = blk->next;
            blk_ndx = 0;
        }
    }
    
    if(!blk) {
        vm->gc_step = GCSTEP_INIT;
    } else {
        vm->gc_ptr = blk;
        vm->gc_blockptr = blk_ndx;
    }
}

void gc_step(VM *vm) {
    static int gc_counter = 0;
    //if(++gc_counter < 5) return;
    //gc_counter = 0;
    switch(vm->gc_step) {
        case GCSTEP_INIT: //initialize
            vm->gc_version = (vm->gc_version+1)&255;
            vm->gc_step = GCSTEP_MARKCLASSES;
            vm->gc_ptr = vm->classes;
            vm->markQueue.R = vm->markQueue.W = vm->markQueue.S = 0;
            gc_queue_object(vm, vm->exception);
            break;
            
        case GCSTEP_MARKCLASSES:
            gc_mark_classes(vm);
            break;
            
        case GCSTEP_MARKSTACK:
            gc_mark_stack(vm);
            break;
            
        case GCSTEP_MARKQUEUE:
            gc_mark_queue(vm);
            break;
            
        case GCSTEP_SWEEP:
            gc_sweep(vm);
            break;
    }
}
