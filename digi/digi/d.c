//
// Created by Mustafa Ozsakalli on 25.06.2020.
//
#include "vm.h"
#include "d.h"

VERTEX BatchVerts[MAX_VERTS];
int BatchVertexCount;
int BatchIndexCount;
int CurrentMaterial;
Texture *CurrentTexture;
Mat4 projection;

extern void render_init();
extern void render_setup_material(int material);
extern void render_draw_quads_indexed(VERTEX *verts, int indexCount, Texture *texture);

inline static void render_flush() {
    if(BatchIndexCount > 0) {
        render_draw_quads_indexed(&BatchVerts[0], BatchIndexCount, CurrentTexture);
        BatchIndexCount = BatchVertexCount = 0;
    }
}

void mesh_render_quads(Mesh *mesh, Mat4 *mat, int color, float alpha) {
    QuadMeshItem *quads = mesh->vertices;

    if(mat->version != mesh->version) {
        //update cache
        if(!mat->is3d) {
            float m00 = mat->vals[M2D00];
            float m01 = mat->vals[M2D01];
            float m02 = mat->vals[M2D02];
            float m10 = mat->vals[M2D10];
            float m11 = mat->vals[M2D11];
            float m12 = mat->vals[M2D12];
            QuadMeshItem *q = quads;
            for (int i = 0; i < mesh->size; i++) {
                float xm00 = q->tl.x * m00;
                float xm10 = q->tl.x * m10;
                float x2m00 = q->br.x * m00;
                float x2m10 = q->br.x * m10;
                float ym01 = q->tl.y * m01;
                float ym11 = q->tl.y * m11;
                float y2m01 = q->br.y * m01;
                float y2m11 = q->br.y * m11;
                float ym01m02 = ym01 + m02;
                float ym11m12 = ym11 + m12;
                float y2m01m02 = y2m01 + m02;
                float y2m11m12 = y2m11 + m12;

                q->p1 = (VEC3) {xm00 + ym01m02, xm10 + ym11m12, 0};
                q->p2 = (VEC3) {x2m00 + ym01m02, x2m10 + ym11m12, 0};
                q->p3 = (VEC3) {x2m00 + y2m01m02, x2m10 + y2m11m12, 0};
                q->p4 = (VEC3) {xm00 + y2m01m02, xm10 + y2m11m12, 0};
                q++;
            }
        } else {
            //todo: update 3d
        }
        mesh->version = mat->version;
    }

    if(alpha > 1) alpha = 1;
    COLOR col;
    if(color == 0xFFFFFF && alpha == 1) {
        col = {255,255,255,255};
    } else {
        col.r = ((color >> 16) & 0xff) * alpha;
        col.g = ((color >> 8) & 0xff) * alpha;
        col.b = ((color >> 0) & 0xff) * alpha;
        col.a = alpha * 255;
    }

    QuadMeshItem *q = quads;
    VERTEX *v = &BatchVerts[BatchVertexCount];
    for(int i=0; i<mesh->size; i++) {
        if(BatchVertexCount + 4 == MAX_VERTS) {
            render_flush();
            v = &BatchVerts[0];
        }

        v->pos = q->p1;
        v->uv = q->t1;
        v->color = col;
        v++;

        v->pos = q->p2;
        v->uv = q->t1;
        v->color = col;
        v++;

        v->pos = q->p3;
        v->uv = q->t1;
        v->color = col;
        v++;

        v->pos = q->p4;
        v->uv = q->t1;
        v->color = col;
        v++;
        q++;
        BatchVertexCount += 4;
        BatchIndexCount += 6;
    }
}

void node_render(Object *o) {
    Node *node = o->instance;

    //update matrix
    int dirty = (node->flags & (NODE_ROT_DIRTY|NODE_LOCAL_DIRTY)) != 0;
    if(dirty) node_update_localmatrix(node);
    if(node->parent) {
        Node *parent = node->parent->instance;
        Mat4 *parentWorld = parent->world->instance;
        if(node->parentVersion != parentWorld->version || dirty) {
            Mat4_mul2d(parentWorld, node->local->instance, node->world->instance);
            node->parentVersion = parentWorld->version;
        }
    }

    if(node->mesh) {
        Mesh *mesh = node->mesh->instance;
        if(mesh->size > 0) {
            if(CurrentMaterial != node->material) {
                render_flush();
                render_setup_material(node->material);
                CurrentMaterial = node->material;
            }
            if(CurrentTexture != node->texture) {
                render_flush();
                CurrentTexture = node->texture;
            }
            switch (mesh->type) {
                case MESH_QUAD:
                    mesh_render_quads(mesh, node->world->instance, node->color, node->worldAlpha);
                    break;
            }
        }
    }
    Object *ptr = node->firstChild;
    while(ptr) {
        Node *child = ptr->instance;
        if((child->flags & NODE_VISIBLE) != 0 && child->worldAlpha > 0) {
            node_render(ptr);
        }
        ptr = child->next;
    }
}
void Gama_digiplay_Stage_render(VM *vm, Object *method, VAR *args) {
    if(!args[0].O) {
        throw_null(vm);
        return;
    }

    int width = args[0].I;
    int height = args[1].I;

    node_render(args[0].O);
}
/*
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
*/