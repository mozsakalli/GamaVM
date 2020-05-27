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

void gc_init(VM *vm) {
    static int initialized = 0;
    if(!initialized) {
        initialized = 1;
        GC_set_no_dls(1);
        GC_set_java_finalization(1);
        GC_enable_incremental();
        GC_INIT();
        GC_allow_register_threads();
        
        gc_register_current_thread();
    }
}

void gc_register_current_thread() {
    struct GC_stack_base stackBase;
    if (GC_thread_is_registered()) {
        // Always deregister the current thread to prevent a situation where the
        // thread is registered with the GC yet the GC's thread local alloc TLS
        // has been cleared (see #1025).
        GC_unregister_my_thread();
    }
    GC_get_stack_base(&stackBase);
    GC_register_my_thread(&stackBase);
}

void gc_unregister_current_thread() {
    if (GC_thread_is_registered()) {
        GC_unregister_my_thread();
    }
}

void *gc_alloc(VM *vm, int size) {
    return malloc(size);
    void* m = GC_MALLOC(size);
    if(!m) {
        GC_gcollect();
        m = GC_MALLOC(size);
    }
    return m;
    //return malloc(size);
}

void *gc_alloc_global(VM *vm, int size) {
    return malloc(size);
    return GC_MALLOC_UNCOLLECTABLE(size);
}

void* gc_alloc_atomic(VM *vm, int size) {
    return malloc(size);
    void* m = GC_MALLOC_ATOMIC(size);
    if(!m) {
        GC_gcollect();
        m = GC_MALLOC_ATOMIC(size);
    }
    return m;

    //return malloc(size);
}

ObjectPtr alloc_object(VM *vm,Class *cls) {
    int size = sizeof(Object) + cls->instanceSize;
    ObjectPtr o = (ObjectPtr)gc_alloc(vm, size);
    memset(o, 0, size);
    o->cls = cls;
    return o;
}

ObjectPtr alloc_object_array(VM *vm, Class *cls, int length) {
    int size = sizeof(Array) + sizeof(Object*) * length;
    Array *arr = (Array*)gc_alloc(vm, size);
    memset(arr, 0, size);
    arr->cls = cls;
    arr->length = length;
    return (ObjectPtr)arr;
}

ObjectPtr alloc_prim_array(VM *vm, Class *cls, int length) {
    //printf("alloc-prim: %s %d\n", string2c(cls->name), length);
    int size = sizeof(Array) + cls->elementClass->instanceSize * length;
    Array *arr = (Array*)gc_alloc_atomic(vm, size);
    memset(arr, 0, size);
    arr->cls = cls;
    arr->length = length;
    //printf("alloc-prim-array: %s -> %p\n", string2c(cls->name), arr);
    return (ObjectPtr)arr;
}

String* alloc_string(VM *vm, char *chars) {
    int len = (int)strlen(chars);
    Array* jchars = (Array*)alloc_prim_array(vm, &java_lang_C1D, len);
    for(int i=0; i<len; i++)
        ((jchar*)jchars->data)[i] = chars[i];
    
    String *str = (String*)alloc_object(vm, &java_lang_String);
    str->length = len;
    str->chars = jchars;
    
    return str;
}
/*
extern char *string2c(String* str);

typedef struct __attribute__ ((packed)) MemChunk {
    struct {
        unsigned int used : 1;
        unsigned int mark : 3;
        unsigned int size : 28;
    } info;
} MemChunk;

typedef struct MemBlock {
    int size;
    int free_size;
    void *base;
    struct MemBlock *next;
} MemBlock;

MemBlock *gc_add_block(VM *vm, int size) {
    MemBlock *block = malloc(sizeof(MemBlock));
    memset(block, 0, sizeof(MemBlock));
    block->size = block->free_size = size;
    block->base = malloc(size);
    memset(block->base, 0, size);
    
    MemChunk *c = block->base;
    c->info.size = size;
    
    block->next = vm->heap;
    vm->heap = block;
    
    printf("--------------------- GC: Add new block\n");
    return block;
}

MemBlock *gc_find_block(VM *vm, int size) {
    MemBlock *block = vm->heap;
    while(block) {
        if(block->free_size >= size) {
            return block;
        }
        block = block->next;
    }
    
    return gc_add_block(vm, 1024*1024*4);
}

void *gc_alloc(VM *vm, int size) {
    size = ((size+sizeof(MemChunk)+3)/4)*4;
    //printf("alloc: %d\n", size);
    MemBlock *block = gc_find_block(vm, size);
    MemChunk *c = block->base;
    while((void*)c < block->base + block->size) {
        if(!c->info.used && c->info.size >= size) {
            if(c->info.size > size) {
                //split
                MemChunk *nc = (void*)c + size;
                nc->info.used = 0;
                nc->info.size = c->info.size - size;
            }
            c->info.size = size;
            c->info.used = 1;
            c->info.mark = vm->gcVersion;
            block->free_size -= size;
            //printf("block-size: %d\n", block->free_size);
            return c+1;
        }
        
        c = (void*)c + c->info.size;
    }
    
    printf("ALLOc failed\n");
    return NULL;
}

MemBlock *gc_find_block_of(VM *vm, void *ptr) {
    void *c = (MemChunk*)ptr - 1;
    MemBlock *b = vm->heap;
    while(b) {
        if(c >= b->base && c < b->base + b->size) return b;
        b = b->next;
    }
    return NULL;
}

int gc_is_object(VM *vm, void *ptr) {
    return gc_find_block_of(vm, ptr) != NULL;
}

void gc_free(VM *vm, void *ptr) {
    MemBlock *blk = gc_find_block_of(vm, ptr);
    if(!blk) return;
    MemChunk *c = (MemChunk*)ptr - 1;
    c->info.used = 0;
    MemChunk *p = c;
    while((void*)p < blk->base + blk->size && !p->info.used) {
        c->info.size += p->info.size;
        p = (void*)p + p->info.size;
    }
    blk->free_size += c->info.size;
}

ObjectPtr alloc_object(VM *vm,Class *cls) {
    int size = sizeof(Object) + cls->instanceSize;
    ObjectPtr o = (ObjectPtr)gc_alloc(vm, size);
    memset(o, 0, size);
    o->cls = cls;
    //printf("alloc-object: %s -> %p\n", string2c(cls->name), o);
    return o;
}

ObjectPtr alloc_object_array(VM *vm, Class *cls, int length) {
    int size = sizeof(Array) + sizeof(Object*) * length;
    Array *arr = (Array*)gc_alloc(vm, size);
    memset(arr, 0, size);
    arr->cls = cls;
    arr->length = length;
    //printf("alloc-object-array: %s -> %p\n", string2c(cls->name), arr);
    return (ObjectPtr)arr;
}

ObjectPtr alloc_prim_array(VM *vm, Class *cls, int length) {
    //printf("alloc-prim: %s %d\n", string2c(cls->name), length);
    int size = sizeof(Array) + cls->elementClass->instanceSize * length;
    Array *arr = (Array*)gc_alloc(vm, size);
    memset(arr, 0, size);
    arr->cls = cls;
    arr->length = length;
    //printf("alloc-prim-array: %s -> %p\n", string2c(cls->name), arr);

    return (ObjectPtr)arr;
}

void gc_queue_object(VM *vm, Object *o) {
    if(!o || !gc_is_object(vm, o)) return;
    MemChunk *c = (MemChunk*)o - 1;
    if(!o || c->info.mark == vm->gcVersion) return;
    printf("Queue: %s\n", string2c(o->cls->name));
    if(vm->markQueue.S == vm->markQueue.C) {
        int size = vm->markQueue.C;
        if(size == 0) size = 4096; else size *= 2;
        vm->markQueue.Q = realloc(vm->markQueue.Q, size * sizeof(Object*));
        vm->markQueue.C = size;
    }
    c->info.mark = vm->gcVersion;
    vm->markQueue.Q[vm->markQueue.W] = o;
    vm->markQueue.W = (vm->markQueue.W + 1) % vm->markQueue.C;
    vm->markQueue.S++;
}

void gc_mark_globals(VM *vm) {
    Class *cls = (Class*)vm->gcCurrent;
    int count = 0;
    while(cls && count++ < 256) {
        if(!cls->globals || !cls->fields || cls->primitiveType) {
            cls = cls->listNext;
            continue;
        }
        
        printf("WalkGlobal: %s\n", string2c(cls->name));
        int len = cls->fields->length;
        Field **fields = (Field**)cls->fields->data;
        for(int i=0; i<len; i++) {
            Field *f = fields[i];
            jchar *sig = (jchar*)f->signature->chars->data;
            if(IS_STATIC(f) && (sig[0] == 'L' || sig[0] == '[')) {
                Object *o = *((ObjectPtr*)(cls->globals + f->offset));
                if(o) gc_queue_object(vm, o);
            }
        }
        cls = cls->listNext;
    }
    
    for(int i=0; i<vm->SP; i++) {
        void *o = vm->stack[i].O;
        if(o && gc_is_object(vm, o)) gc_queue_object(vm, o);
    }
    
    if(!cls) {
        vm->gcStep++;
    } else vm->gcCurrent = cls;
}

void gc_mark_queue(VM *vm) {
    int count = 0;
    
    while(count++ < 256 && vm->markQueue.S > 0) {
        Object *o = vm->markQueue.Q[vm->markQueue.R];
        vm->markQueue.R = (vm->markQueue.R + 1) % vm->markQueue.C;
        vm->markQueue.S--;
        
        //mark fields
        if(o->cls->fields) {
            printf("WalkObject: %s %p\n", string2c(o->cls->name), o);
            int len = o->cls->fields->length;
            Field **fields = (Field**)o->cls->fields->data;
            for(int i=0; i<len; i++) {
                Field *f = fields[i];
                jchar *sig = (jchar*)f->signature->chars->data;
                if(!IS_STATIC(f) && (sig[0] == 'L' || sig[0] == '[')) {
                    Object *c = *((ObjectPtr*)(o+sizeof(Object)+f->offset));
                    printf("    QueueField: %s -> %p\n", string2c(f->name), c);
                    if(c) gc_queue_object(vm, c);
                }
            }
        }
        
        //mark object arrays
        if(o->cls->elementClass && !o->cls->elementClass->primitiveType) {
            printf("mark array cls:%s\n",string2c(o->cls->name));
            Array *arr = (Array*)o;
            Object **data = (Object**)arr->data;
            for(int i=0; i<arr->length; i++) {
                if(data[i])
                    gc_queue_object(vm, data[i]);
            }
        }
    }
    
    //mark finished
    if(vm->markQueue.S == 0) {
        vm->gcStep++;
        vm->gcCurrent = vm->heap;
        vm->gcCurrentMem = ((MemBlock*)vm->heap)->base;
    }
}

void gc_sweep(VM *vm) {
    MemBlock *blk = vm->gcCurrent;
    MemChunk *chunk = vm->gcCurrentMem;
    
    int count = 0;
    while(blk && count++ < 256) {
        if(chunk->info.used && chunk->info.mark != vm->gcVersion) {
            chunk->info.used = 0;
            blk->free_size += chunk->info.size;
        }
        chunk = (void*)chunk + chunk->info.size;
        if((void*)chunk >= blk->base + blk->size) {
            blk = blk->next;
            if(blk) chunk = blk->base;
        }
    }
    
    if(!blk) {
        vm->gcStep = 0;
        printf("Sweep completed...\n");
    } else {
        vm->gcCurrent = blk;
        vm->gcCurrentMem = chunk;
    }

}
*/
void gc_step(VM *vm) {
    return;
    /*
    if(vm->exception) return;
    switch(vm->gcStep) {
        case 0: //initialize
            vm->gcVersion = (vm->gcVersion+1)&7;
            vm->gcStep = 1;
            vm->gcCurrent = vm->classes;
            vm->markQueue.R = vm->markQueue.W = vm->markQueue.S = 0;
            gc_queue_object(vm, vm->exception);
            break;
            
        case 1: //mark globals
            gc_mark_globals(vm);
            break;
            
        case 2: //mark queue
            gc_mark_queue(vm);
            break;
            
        case 3: //sweep
            gc_sweep(vm);
            break;
    }*/
}
