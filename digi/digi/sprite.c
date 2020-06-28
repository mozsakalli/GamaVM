//
// Created by mustafa on 2020-06-28.
//

#include "sprite.h"

#define MAX_BATCH_QUADS 8192
#define MAX_BATCH_VERTS (MAX_BATCH_QUADS<<2)
#define MAX_BATCH_INDEX (MAX_BATCH_QUADS*6)

VERTEX BatchVerts[MAX_BATCH_VERTS];
short BatchIndex[MAX_BATCH_INDEX];
int BatchVertexCount, BatchIndexCount;
Mat4 ProjectionMatrix;
int ProjectionDirty;
int RenderWidth, RenderHeight, StencilMode, DepthEnabled, BlendMode, Clipping;
Shader *_Shader;

extern void render_set_cliprect(float x, float y, float w, float h);
extern void render_set_blendmode(int mode);
extern void render_clear_color(int color);
extern void render_viewport(int x, int y, int width, int height);
extern void render_useshader(Shader *shader);
extern void render_set_projection(Mat4 *projection);
extern void render_draw_indexed(VERTEX *vertex, short *index, int count, int drawAsLines);

void render_flush_batch() {
    if(BatchIndexCount > 0) {
        if (ProjectionDirty) {
            mat4_setup2d(&ProjectionMatrix, RenderWidth, RenderHeight);
            ProjectionDirty = 0;
        }
        render_set_projection(&ProjectionMatrix);
        render_draw_indexed(&BatchVerts[0], &BatchIndex[0], BatchIndexCount, 0);
        BatchIndexCount = BatchVertexCount = 0;
    }
}
void render_quad_mesh(Mesh *mesh, Mat4 *mat, int color, float alpha) {
    QuadMeshItem *quads = mesh->vertices;
    if(mesh->version != mat->version) {
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
            QuadMeshItem *q = quads;
            for (int i = 0; i < mesh->size; i++) {
                float x = q->tl.x; float y = q->tl.y;
                float x2 = q->br.x; float y2 = q->br.y;
                float z = 0;
                q->p1 = (VEC3) {x * mat->vals[0] + y * mat->vals[4] + z * mat->vals[8] + mat->vals[12]};
                q->p2 = (VEC3) {x2 * mat->vals[0] + y * mat->vals[4] + z * mat->vals[8] + mat->vals[12]};
                q->p3 = (VEC3) {x2 * mat->vals[0] + y2 * mat->vals[4] + z * mat->vals[8] + mat->vals[12]};
                q->p4 = (VEC3) {x * mat->vals[0] + y2 * mat->vals[4] + z * mat->vals[8] + mat->vals[12]};
                q++;
            }
        }
        mesh->version = mat->version;
    }

    if(alpha > 1) alpha = 1;
    COLOR col;
    if(color == 0xFFFFFF && alpha == 1) {
        col = (COLOR){255,255,255,255};
    } else {
        col.r = ((color >> 16) & 0xff) * alpha;
        col.g = ((color >> 8) & 0xff) * alpha;
        col.b = ((color >> 0) & 0xff) * alpha;
        col.a = alpha * 255;
    }

    QuadMeshItem *q = quads;
    VERTEX *v = &BatchVerts[BatchVertexCount];
    short *n = &BatchIndex[BatchIndexCount];
    for(int i=0; i<mesh->size; i++) {
        if(BatchVertexCount + 4 == MAX_BATCH_VERTS) {
            render_flush_batch();
            v = &BatchVerts[0];
            n = &BatchIndex[0];
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

        n[0] = BatchVertexCount;
        n[1] = BatchVertexCount+1;
        n[2] = BatchVertexCount+2;
        n[3] = BatchVertexCount;
        n[4] = BatchVertexCount+2;
        n[5] = BatchVertexCount+3;
        n += 6;

        BatchVertexCount += 4;
        BatchIndexCount += 6;
    }

}

void render_sprite(Object *spriteObject) {
    Sprite *sprite = spriteObject->instance;
    //update matrix
    int dirty = update_sprite_localmatrix(sprite);
    if(sprite->parent) {
        Sprite *parent = sprite->parent->instance;
        Mat4 *local = sprite->local->instance;
        Mat4 *parentWorld = parent->world->instance;
        if(sprite->parentVersion != parentWorld->version || dirty) {
            if(parentWorld->is3d || local->is3d) {
                mat4_multiply(parentWorld, local, sprite->world->instance);
            } else {
                mat4_multiply2d(parentWorld, local, sprite->world->instance);
            }
            sprite->parentVersion = parentWorld->version;
        }
    } else if(dirty){
        memcpy(sprite->world->instance, sprite->local->instance, sizeof(Mat4));
    }

    int clipping = sprite->clipW > 0 && sprite->clipH > 0;
    if(clipping != Clipping) {
        render_flush_batch();
        if(clipping) {
            VEC3 tl = (VEC3){sprite->clipX, sprite->clipY, 0};
            VEC3 br = (VEC3){sprite->clipX+sprite->clipW, sprite->clipY+sprite->clipH, 0};
            mat4_project(sprite->world->instance, &tl);
            mat4_project(sprite->world->instance, &br);
            render_set_cliprect(tl.x, tl.y, br.x, br.y);
        } else render_set_cliprect(0,0,0,0);
        Clipping = clipping;
    }

    if(sprite->mesh) {
        if (BlendMode != sprite->blendMode) {
            render_flush_batch();
            render_set_blendmode(BlendMode = sprite->blendMode);
        }

        if(_Shader != sprite->shader) {
            render_flush_batch();
            render_useshader(_Shader = sprite->shader);
            ProjectionDirty = 1;
        }

        Mesh *mesh = sprite->mesh->instance;
        switch(mesh->type) {
            case MESH_QUAD:
                render_quad_mesh(mesh, sprite->world->instance, sprite->color, sprite->worldAlpha);
                break;
        }
    }

    Object *ptr = sprite->firstChild;
    while(ptr) {
        Sprite *child = ptr->instance;
        if((child->flags & VISIBLE) != 0 && child->worldAlpha > 0) {
            render_sprite(ptr);
        }
        ptr = child->next;
    }

}
void Gama_digiplay_Stage_render(VM *vm, Object *method, VAR *args) {
    if(!args[0].O) {
        throw_null(vm);
        return;
    }
    RenderWidth = args[1].I;
    RenderHeight = args[2].I;
    ProjectionDirty = 1;

    BlendMode = DepthEnabled = StencilMode = Clipping = 0;
    Sprite *stage = args[0].O->instance;

    render_viewport(0, 0, RenderWidth, RenderHeight);
    render_set_blendmode(0);
    render_set_cliprect(0,0,0,0);
    render_clear_color((int)stage->color);

    render_useshader(_Shader = NULL);

    render_sprite(args[0].O);

    render_flush_batch();
}

void Gama_digiplay_Mesh_resize(VM *vm, Object *method, VAR *args) {
    if(!args[0].O) {
        throw_null(vm);
        return;
    }

    Mesh *mesh = args[0].O->instance;
    int capacity = args[1].I;
    switch(mesh->type) {
        case MESH_QUAD:
            mesh->vertices = realloc(mesh->vertices, sizeof(QuadMeshItem) * capacity);
            mesh->capacity = mesh->size = capacity;
            break;
    }
}

void Gama_digiplay_Mesh_setQuad(VM *vm, Object *method, VAR *args) {
    if(!args[0].O) {
        throw_null(vm);
        return;
    }

    Mesh *mesh = args[0].O->instance;
    int index = args[1].I;
    if(index < 0 || index >= mesh->size) {
        throw_arraybounds(vm, index, mesh->size);
        return;
    }

    QuadMeshItem *q = (QuadMeshItem*)mesh->vertices;
    q[index].tl = (VEC2){args[2].F, args[3].F};
    q[index].br = (VEC2){args[2].F+args[4].F, args[3].F+args[5].F};
    q[index].t1 = (VEC2){args[6].F, args[7].F};
    q[index].t2 = (VEC2){args[8].F, args[9].F};
    q[index].t3 = (VEC2){args[10].F, args[11].F};
    q[index].t4 = (VEC2){args[12].F, args[13].F};
}

NativeMethodInfo digiplay_sprite_methods[] = {
        {"digiplay/Mesh:resize:(I)V", &Gama_digiplay_Mesh_resize},
        {"digiplay/Mesh:setQuad:(IFFFFFFFFFFFF)V", &Gama_digiplay_Mesh_setQuad},

        {"digiplay/Stage:render:(II)V", &Gama_digiplay_Stage_render},
        NULL
};
