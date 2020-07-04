//
// Created by mustafa on 2020-06-28.
//

#include "sprite.h"
#define STBI_NO_THREAD_LOCALS
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define MAX_BATCH_QUADS 8192
#define MAX_BATCH_VERTS (MAX_BATCH_QUADS<<2)
#define MAX_BATCH_INDEX (MAX_BATCH_QUADS*6)

VERTEX BatchVerts[MAX_BATCH_VERTS];
short BatchIndex[MAX_BATCH_INDEX];
int BatchVertexCount, BatchIndexCount;
Mat4 ProjectionMatrix;
int ProjectionDirty;
int RenderWidth, RenderHeight, StencilMode, DepthEnabled, BlendMode, Clipping;
Object *_Shader;
Object *_Texture;
int _TextureMode;
int _CullMode;

extern void render_set_cliprect(float x, float y, float w, float h);
extern void render_set_blendmode(int mode);
extern void render_clear_color(int color);
extern void render_viewport(int x, int y, int width, int height);
extern void render_useshader(Shader *shader);
extern void render_set_projection(Mat4 *projection);
extern void render_draw_indexed(VERTEX *vertex, short *index, int count, int drawAsLines);
extern void render_upload_texture(Texture *tex, void *buffer);
extern void render_set_texture(Texture *tex);
extern void render_set_texture_mode(int mode);
extern void render_cull_mode(int mode);

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
        v->uv = q->t2;
        v->color = col;
        v++;

        v->pos = q->p3;
        v->uv = q->t3;
        v->color = col;
        v++;

        v->pos = q->p4;
        v->uv = q->t4;
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

void render_polygon_mesh(Mesh *mesh, Mat4 *mat, int color, float alpha) {
    PolygonMesh *poly = (PolygonMesh*)mesh->vertices;
    if(!poly) return;

    VEC3 *pos = poly->pos ? poly->pos->instance : NULL;
    VEC2 *uv = poly->uv ? poly->uv->instance : NULL;
    COLOR *colors = poly->color ? poly->color->instance : NULL;
    short *index = poly->index ? poly->index->instance : NULL;
    
    if(!pos && !index) return;
    
    //batchable
    if(poly->pos->length <= 768) {
        int len = poly->pos->length / 3;
        if(len > poly->cachePosCapacity) poly->cachePos = realloc(poly->cachePos, (poly->cachePosCapacity = len) * sizeof(VEC3));
        if(mesh->version != mat->version) {
            if(mat->is3d) {
                float *ptr = &mat->vals[0];
                for(int i=0; i<len; i++) {
                    float x = pos[i].x;
                    float y = pos[i].y;
                    float z = pos[i].z;
                    poly->cachePos[i] = (VEC3) {
                        x * ptr[0] + y * ptr[4] + z * ptr[8] + ptr[12],
                        x * ptr[1] + y * ptr[5] + z * ptr[9] + ptr[13],
                        x * ptr[2] + y * ptr[6] + z * ptr[10] + ptr[14]};
                }
            } else {
                float m00 = mat->vals[M2D00];
                float m01 = mat->vals[M2D01];
                float m02 = mat->vals[M2D02];
                float m10 = mat->vals[M2D10];
                float m11 = mat->vals[M2D11];
                float m12 = mat->vals[M2D12];
                for(int i=0; i<len; i++) {
                    poly->cachePos[i] = (VEC3){pos[i].x * m00 + pos[i].y * m01 + m02, pos[i].x * m10 + pos[i].y * m11 + m12, 0};
                }
            }
            mesh->version = mat->version;
        }
        if(BatchVertexCount + poly->pos->length > MAX_BATCH_VERTS)
            render_flush_batch();
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
        VERTEX *v = &BatchVerts[BatchVertexCount];
        for(int i=0; i<len; i++) {
            v->pos = poly->cachePos[i];
            v->color = col;
            v->uv = uv[i];
            v++;
        }
        short *n = &BatchIndex[BatchIndexCount];
        for(int i=0; i<poly->count; i++)
            n[i] = BatchIndexCount + index[i];
        BatchIndexCount += poly->count;
        BatchVertexCount += len;
    } else {
        
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
            _Shader = sprite->shader;
            render_useshader(_Shader ? _Shader->instance : NULL);
            ProjectionDirty = 1;
            _Texture = NULL;
        }

        if(_Texture != sprite->texture) {
            render_flush_batch();
            _Texture = sprite->texture;
            render_set_texture(_Texture ? _Texture->instance : NULL);
            _TextureMode = -1;
        }

        if(_TextureMode != sprite->textureMode) {
            render_flush_batch();
            render_set_texture_mode(_TextureMode = sprite->textureMode);
        }

        if(_CullMode != sprite->cullMode) {
            render_flush_batch();
            render_cull_mode(_CullMode = sprite->cullMode);
        }

        Mesh *mesh = sprite->mesh->instance;
        switch(mesh->type) {
            case MESH_QUAD:
                render_quad_mesh(mesh, sprite->world->instance, sprite->color, sprite->worldAlpha);
                break;
                
            case MESH_POLYGON:
                render_polygon_mesh(mesh, sprite->world->instance, sprite->color, sprite->worldAlpha);
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
    render_cull_mode(0);
    _Texture = NULL;
    _Shader = NULL;
    _TextureMode = -1;
    _CullMode = 0;

    render_useshader(NULL);
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
            mesh->vertices = realloc((void*)mesh->vertices, sizeof(QuadMeshItem) * capacity);
            mesh->capacity = mesh->size = capacity;
            break;
            
        case MESH_POLYGON:
            if(mesh->vertices) free((void*)mesh->vertices); mesh->vertices = 0;
            break;
    }
}

void Gama_digiplay_Mesh_setQuad(VM *vm, Object *method, VAR *args) {
    if(!args[0].O) {
        throw_null(vm);
        return;
    }

    Mesh *mesh = args[0].O->instance;
    if(mesh->type != MESH_QUAD) return;
    
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
    mesh->version = 0;
}

void Gama_digiplay_Mesh_setPolygon(VM *vm, Object *method, VAR *args) {
    if(!args[0].O) {
        throw_null(vm);
        return;
    }

    Mesh *mesh = args[0].O->instance;
    if(mesh->type != MESH_POLYGON) return;
    Object *pos = args[1].O;
    Object *uv = args[2].O;
    Object *color = args[3].O;
    Object *index = args[4].O;
    int count = args[5].I;
    
    if(!mesh->vertices) mesh->vertices = vm_alloc(sizeof(PolygonMesh));
    PolygonMesh *poly = (PolygonMesh*)mesh->vertices;
    if(poly->pos != pos) {
        if(poly->pos) gc_unprotect(vm, poly->pos);
        poly->pos = pos;
        if(poly->pos) gc_protect(vm, poly->pos);
    }
    if(poly->uv != uv) {
        if(poly->uv) gc_unprotect(vm, poly->uv);
        poly->uv = uv;
        if(poly->uv) gc_protect(vm, poly->uv);
    }
    if(poly->color != color) {
        if(poly->color) gc_unprotect(vm, poly->color);
        poly->color = color;
        if(poly->color) gc_protect(vm, poly->color);
    }
    if(poly->index != index) {
        if(poly->index) gc_unprotect(vm, poly->index);
        poly->index = index;
        if(poly->index) gc_protect(vm, poly->index);
    }
    poly->count = count;
    mesh->version = 0;
}

void Gama_digiplay_Texture_upload(VM *vm, Object *method, VAR *args) {
    if(!args[0].O || !args[1].O) {
        throw_null(vm);
        return;
    }

    Texture *tex = (Texture*)args[0].O->instance;
    Object *array = args[1].O;

    int comp = 0;
    stbi_uc* pix = stbi_load_from_memory((stbi_uc *)array->instance, array->length, &tex->width, &tex->height, &comp, 4);
    if(pix) {
        //
        struct RGBA { unsigned char r; unsigned char g; unsigned char b; unsigned char a; };
        struct RGBA * ptr = (struct RGBA * ) pix;
        int len = tex->width * tex->height;
        for (int i = 0; i < len; i++) {
            float a = ptr[i].a / 255.0f;
            ptr[i].r *= a;
            ptr[i].g *= a;
            ptr[i].b *= a;
        }

        tex->hwWidth = tex->width; //glWidth = npot ? width : pow2_size(width);");
        tex->hwHeight = tex->height; // npot ? height : pow2_size(height);");
        render_upload_texture(tex, pix);
        free(pix);
    }
}

NativeMethodInfo digiplay_sprite_methods[] = {
    {"digiplay/Mesh:resize:(I)V", &Gama_digiplay_Mesh_resize},
    {"digiplay/Mesh:setQuad:(IFFFFFFFFFFFF)V", &Gama_digiplay_Mesh_setQuad},
    {"digiplay/Mesh:setPolygon:([F[F[I[SI)V", &Gama_digiplay_Mesh_setPolygon},

    {"digiplay/Texture:upload:([B)V", &Gama_digiplay_Texture_upload},

    {"digiplay/Stage:render:(II)V", &Gama_digiplay_Stage_render},
    NULL
};
