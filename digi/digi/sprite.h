//
// Created by mustafa on 2020-06-28.
//

#ifndef SPRITE_H
#define SPRITE_H

#include "vm.h"
#include "geom.h"

typedef struct __attribute__ ((packed)) Shader {
    JINT pos,uv,color,projection,model,texture,user0,user1,user2,user3;
    JLONG gpu;
} Shader;

typedef struct __attribute__ ((packed)) Texture {
    JINT width, height, hwWidth, hwHeight;
    JLONG gpu;
} Texture;

#define VISIBLE (1 << 0)
#define INTERACTIVE (1 << 1)
#define LOCAL_MATRIX_DIRTY (1 << 2)
#define VIEW_MATRIX_DIRTY (1 << 3)
#define INTERACTIVE_CHILD (1 << 4)
#define ROT_SKEW_DIRTY (1 << 5)
#define IN_STAGE (1 << 6)
#define CONTENT_INVALID (1 << 7)
#define DISPOSED (1 << 8)
#define STOP_PROPAGATION (1 << 9)
#define HIDES_SCENE (1 << 10)
#define STAY_ON_TOP (1 << 11)
#define STRETCH_ZERO (1 << 12)

typedef struct __attribute__ ((packed)) Sprite {
    JINT flags;
    JFLOAT x,y,z, _x,_y,_z;
    JFLOAT sx,sy,sz, _sx,_sy,_sz;
    JFLOAT rx,ry,rz, _rx,_ry,_rz;
    JFLOAT skx, sky; //skew
    JFLOAT alpha,_alpha,worldAlpha;
    JFLOAT px,py;
    JFLOAT width,height, midy, midx;
    JFLOAT clipX, clipY, clipW, clipH;
    JINT numChildren, depth, parentVersion, color, depthEnabled, stencilMode, blendMode, textureMode, cullMode;
    Object *parent, *next, *prev, *firstChild, *lastChild;
    Object *local,*world, *inverse;
    Object *mesh;
    Object *texture, *shader;
    Object *behaviours;
    JINT visibleState;
} Sprite;

inline static int update_sprite_localmatrix(Sprite *sprite) {
    int flags = sprite->flags;
    if(flags & (LOCAL_MATRIX_DIRTY|ROT_SKEW_DIRTY)) {
        Mat4 *mat = (Mat4 *)sprite->local->instance;
        float ry = sprite->ry + sprite->_ry;
        float rx = sprite->rx + sprite->_rx;
        if(ry == 0 && rx == 0) {
            mat4_compose2D(mat,
                    sprite->x + sprite->_x,
                   sprite->y + sprite->_y,
                   sprite->sx + sprite->_sx,
                   sprite->sy + sprite->_sy,
                   sprite->midx, sprite->midy,
                   sprite->flags & ROT_SKEW_DIRTY,
                   sprite->rz + sprite->_rz,
                   sprite->skx, sprite->sky);
        } else {
            mat4_compose(mat,
                 sprite->x + sprite->_x,
                 sprite->y + sprite->_y,
                 sprite->z + sprite->_z,

                 sprite->rx + sprite->_rx,
                 sprite->ry + sprite->_ry,
                 sprite->rz + sprite->_rz,

                 sprite->sx + sprite->_sx,
                 sprite->sy + sprite->_sy,
                 sprite->sz + sprite->_sz,

                 sprite->flags & ROT_SKEW_DIRTY);
            if(sprite->midx != 0 || sprite->midy != 0) {
                mat4_prependTranslation(mat, -sprite->midx, -sprite->midy, 0);
            }
        }
        sprite->flags &= ~(LOCAL_MATRIX_DIRTY | ROT_SKEW_DIRTY);
        return 1;
    }
    return 0;
}

#endif //SPRITE_H
