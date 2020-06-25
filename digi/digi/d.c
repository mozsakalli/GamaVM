//
// Created by Mustafa Ozsakalli on 25.06.2020.
//
#include "vm.h"


typedef struct VEC2 {
    float x,y;
} VEC2;
typedef struct VEC3 {
    float x,y,z;
} VEC3;
typedef struct COLOR {
    unsigned char r,g,b,a;
} COLOR;
typedef struct VERTEX {
    VEC3 pos;
    VEC2 uv;
    COLOR color;
} VERTEX;

typedef struct {
    VEC2 tl, br;
    VEC2 t1,t2,t3,t4;
    VEC3 p1,p2,p3,p4;
} CmdQuadItem;
typedef struct {
    int capacity;
    int size;
    int version;
    CmdQuadItem *items;
    struct CmdQuad *next;
} CmdQuad;

#define CMD_QUAD        0
#define CMD_TRIANGLES   1

typedef struct {
    int cmd;
    void *data;

} RenderCommand;

static CmdQuad *CmdQuadCache = NULL;
void Gama_digiplay_Render_createQuadCommand(VM *vm, Object *method, VAR *args) {
    int capacity = args[0].I;
    CmdQuad *r = CmdQuadCache;
    if(r)
        CmdQuadCache = CmdQuadCache->next;
    else {
        r = vm_alloc(sizeof(CmdQuad));
    }

    if(r->capacity < capacity) {
        r->items = realloc(r->items, sizeof(CmdQuadItem) * capacity);
        r->capacity = capacity;
    }
    r->size = 0;
    r->version = 0;
    r->next = NULL;
    RETURN_J(r);
}

void Gama_digiplay_Render_resizeQuadCommand(VM *vm, Object *method, VAR *args) {
    if(!args[0].J) {
        throw_null(vm);
        return;
    }
    CmdQuad *m = (CmdQuad*)args[0].J;
    int capacity = args[1].I;
    if(capacity > m->capacity) {
        m->items = realloc(m->items, sizeof(CmdQuadItem) * capacity);
        m->capacity = capacity;
    }

}

void Gama_digiplay_Render_setQuadCommandData(VM* vm, Method *method, VAR *args) {
    if(!args[0].J) {
        throw_null(vm);
        return;
    }
    CmdQuad *m = (CmdQuad*)args[0].J;
    int index = args[1].I;
    if(index < 0 || index >= m->capacity) {
        throw_arraybounds(vm, index, m->capacity);
        return;
    }
    CmdQuadItem *q = &m->items[index];
    q->tl = (VEC2){args[2].F, args[3].F};
    q->br = (VEC2){args[4].F, args[5].F};
    q->t1 = (VEC2){args[6].F, args[7].F};
    q->t2 = (VEC2){args[8].F, args[9].F};
    q->t3 = (VEC2){args[10].F, args[11].F};
    q->t4 = (VEC2){args[12].F, args[13].F};

    m->version = 0;
}


#define MAX_VERTEX  16384
typedef struct Render {
    VERTEX batch[MAX_VERTEX];
    int batchSize;
    void *ibo;
} Render;

void Gama_digiplay_Render_begin(VM *vm, Object *method, VAR *args) {

}
