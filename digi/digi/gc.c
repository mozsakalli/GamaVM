//
//  gc.c
//  digi
//
//  Created by Mustafa Ozsakalli on 8.06.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#include "vm.h"

#define COUNT_PER_TICK 128
#define GCSTEP_INIT         0
#define GCSTEP_MARKCLASSES  1
#define GCSTEP_MARKSTACK    2
#define GCSTEP_MARKQUEUE    3
#define GCSTEP_SWEEP        4

int gc_paused = 0;

int heap_is_object(VM *vm, void *o) {
    HeapBlock *b = vm->heap;
    while(b) {
        if(o >= (void*)&b->objects[0] && o <= (void*)&b->objects[HEAP_OBJECTS_PER_BLOCK-1]) return 1;
        b = b->next;
    }
    return 0;
}
void gc_queue_object(VM *vm, Object *o) {
    if(!o || o->gc.version == vm->gcVersion) return;
    o->gc.version = vm->gcVersion;
    if(!o->instance || (o->gc.atomic && !o->gc.isClass)) return;
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
}

void gc_mark_class(VM *vm, VMClass *cls) {
    if(!cls) return;
    //printf("mark class: %s\n", string_to_ascii(cls->name));
    gc_queue_object(vm, cls->clsLoader);
    gc_queue_object(vm, cls->next);
    if(!cls->fields || cls->primitiveSize || cls->elementClass || !cls->global) return;
    int len = cls->fields->length;
    for(int i=0; i<len; i++) {
        Object *fo = ARRAY_DATA_O(cls->fields)[i];
        Field *f = fo->instance;
        if(IS_STATIC(f->flags)) {
            char type = STRCHARS(f->signature)[0];
            if(type == 'L' || type == '[') {
                Object *field_value = *((Object**)(f->offset));
                if(field_value) {
                    gc_queue_object(vm, field_value);
                }
            }
        }
    }
}

void gc_mark_classes(VM *vm) {
    Object *current = vm->gcPtr;
    int count = 0;
    while(current && count++ < COUNT_PER_TICK) {
        VMClass *cls = current->instance;
        if(current != vm->jlClass) {
            gc_mark_class(vm, cls);
        }
        current = cls->next;
    }
    
    if(!current) {
        vm->gcStep = GCSTEP_MARKSTACK;
    } else {
        vm->gcPtr = current;
    }
}

void gc_mark_stack(VM *vm) {
    if(!vm->heap) return;
    for(int i=0; i<vm->SP; i++) {
        void *o = vm->stack[i].O;
        if(o && heap_is_object(vm, o))
            gc_queue_object(vm, (Object*)o);
    }
    vm->gcStep = GCSTEP_MARKQUEUE;
}

void gc_mark_queue(VM *vm) {
    int count = 0;
    
    while(count++ < COUNT_PER_TICK && vm->markQueue.S > 0) {
        Object *o = vm->markQueue.Q[vm->markQueue.R];
        vm->markQueue.R = (vm->markQueue.R + 1) % vm->markQueue.C;
        vm->markQueue.S--;
        
        //printf("cls: %s\n",string_to_ascii(CLS(o->cls,name)));
        if(o->gc.isClass) {
            gc_mark_class(vm, o->instance);
        } else {
            VMClass *cls = o->cls->instance;
            if(cls->instanceOffsets) {
                for(int i=0; i<cls->instanceOffsetCount; i++) {
                    int off = cls->instanceOffsets[i];
                    Object *field_value = *FIELD_PTR_O(o, off);
                    if(field_value) gc_queue_object(vm, field_value);
                }
            } else if(cls->elementClass && !((VMClass*)cls->elementClass->instance)->primitiveSize) {
                int len = o->length;
                for(int i=0; i<len; i++) {
                    Object *array_item = ARRAY_DATA_O(o)[i];
                    if(array_item) gc_queue_object(vm, array_item);
                }
                count += len / 128;
            }
        }
    }
    
    //mark finished
    if(vm->markQueue.S == 0) {
        vm->gcStep = GCSTEP_SWEEP;
        vm->gcPtr = vm->heap;
        vm->gcBlockPtr = 0;
    }
}

void gc_sweep(VM *vm) {
    HeapBlock *blk = vm->gcPtr;
    int blk_ndx = vm->gcBlockPtr;
    int count = 0;
    int version = vm->gcVersion;
    while(blk && count < COUNT_PER_TICK * 3) {
        while(blk_ndx < HEAP_OBJECTS_PER_BLOCK && count++ < COUNT_PER_TICK * 3) {
            Object *o = &blk->objects[blk_ndx];
            if(!o->gc.free && o->gc.version != version) {
                VMClass *cls = o->cls->instance;
                if(cls && cls->finalizer) {
                    VAR args[1] = { {.O = o} };
                    ((VM_CALL)(MTH(cls->finalizer, entry)))(vm, cls->finalizer, &args[0]);
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
        if(blk_ndx == HEAP_OBJECTS_PER_BLOCK) {
            blk = blk->next;
            blk_ndx = 0;
        }
    }
    
    if(!blk) {
        vm->gcStep = GCSTEP_INIT;
    } else {
        vm->gcPtr = blk;
        vm->gcBlockPtr = blk_ndx;
    }
}
void gc_step(VM *vm) {
    if(gc_paused /*|| (vm->gcTick++) % 2 == 0*/) return;
    switch(vm->gcStep) {
        case GCSTEP_INIT: //initialize
            vm->gcVersion = (vm->gcVersion+1) & 15;
            vm->gcStep = GCSTEP_MARKSTACK; //GCSTEP_MARKSTACK; //GCSTEP_MARKCLASSES;
            //vm->gcPtr = ((ClassLoader*)vm->sysClassLoader->instance)->classes;
            vm->markQueue.R = vm->markQueue.W = vm->markQueue.S = 0;
            gc_queue_object(vm, vm->sysClassLoader);
            //gc_queue_object(vm, vm->exception);
            //gc_queue_object(vm, vm->mainMethod);
            for(int i=0; i<vm->gcRootCount; i++)
                gc_queue_object(vm, vm->gcRoots[i]);
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

void gc_pause() {
    gc_paused = 1;
}
void gc_resume() {
    gc_paused = 0;
}
void gc_protect(VM *vm, Object *o) {
    if(!o) return;
    if(vm->gcRootCount > 0) {
        for(int i=0; i<vm->gcRootCount; i++) {
            if(vm->gcRoots[i] == o) {
                return;
            }
        }
    }
    
    if(vm->gcRootCapacity == vm->gcRootCount) {
        int size = (vm->gcRootCapacity == 0 ? 8 : vm->gcRootCapacity) * 2;
        vm->gcRoots = (Object**)realloc(vm->gcRoots, size * sizeof(Object*));
        vm->gcRootCapacity = size;
    }
    vm->gcRoots[vm->gcRootCount++] = o;
}

void gc_unprotect(VM *vm, Object *o) {
    if(!o) return;
    for(int i=0; i<vm->gcRootCount; i++) {
        if(vm->gcRoots[i] == o) {
            vm->gcRoots[i] = vm->gcRoots[vm->gcRootCount - 1];
            vm->gcRoots[vm->gcRootCount - 1] = NULL;
            vm->gcRootCount--;
            break;
        }
    }
}


