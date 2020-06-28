//
// Created by mustafa on 2020-06-25.
//

#ifndef MY_APPLICATION_D_H
#define MY_APPLICATION_D_H

#include "vm.h"
#include <math.h>

#define M00 0
#define M01 4
#define M02 8
#define M03 12
#define M10 1
#define M11 5
#define M12 9
#define M13 13
#define M20 2
#define M21 6
#define M22 10
#define M23 14
#define M30 3
#define M31 7
#define M32 11
#define M33 15

#define M2D00 M00
#define M2D10 M10
#define M2D01 M01
#define M2D11 M11
#define M2D02 M03
#define M2D12 M13

#define MAX_QUAD    8192
#define MAX_VERTS   (MAX_QUAD << 2)

#define CULL_NONE 0
#define CULL_BACK 1
#define CULL_FRONT 2
#define CULL_BOTH 3

#define POLY_FILL 0
#define POLY_LINE 1

#define BLEND_NONE 0
#define BLEND_NORMAL 1
#define BLEND_ADD 2

#define FILTER_LINEAR 0
#define FILTER_NEAR 1

#define WRAP_CLAMP 0
#define WRAP_REPEAT 1

#define DEPTH_TEST_NONE 0
#define DEPTH_TEST_ALWAYS 1
#define DEPTH_TEST_NEVER 2
#define DEPTH_TEST_EQ 3
#define DEPTH_TEST_NEQ 4
#define DEPTH_TEST_GT 5
#define DEPTH_TEST_GE 6
#define DEPTH_TEST_LT 7
#define DEPTH_TEST_LE 8

#define STENCIL_NONE    0
#define STENCIL_MASK    1
#define STENCIL_CHILD   2

#define SHADER_NORMAL       0
#define SHADER_ALPHAMASK    1

typedef struct Material {
    int culling     : 2;
    int polymode    : 1;
    int blendmode   : 2;
    int filter      : 1;
    int wrap        : 1;
    int depthwrite  : 1;
    int depthtest   : 4;
    int colorwrite  : 4;
    int stencil     : 2;
    int shader      : 4;
} Material;

inline static double fast_sin(double x) {
    int k;
    double y;
    double z;

    z = x;
    z *= 0.3183098861837907;
    z += 6755399441055744.0;
    k = *((int *) &z);
    z = k;
    z *= 3.1415926535897932;
    x -= z;
    y = x;
    y *= x;
    z = 0.0073524681968701;
    z *= y;
    z -= 0.1652891139701474;
    z *= y;
    z += 0.9996919862959676;
    x *= z;
    k &= 1;
    k += k;
    z = k;
    z *= x;
    x -= z;

    return x;
}
#define fast_cos(r) fast_sin((r)+M_PI/2)

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
typedef struct QuadMeshItem {
    VEC2 tl, br;
    VEC2 t1, t2, t3, t4;
    VEC3 p1, p2, p3, p4;
} QuadMeshItem;


#define MESH_QUAD   0
typedef struct __attribute__ ((packed)) Mesh {
    JINT type;
    JINT capacity;
    JINT size;
    JINT version;
    JLONG vertices;
    JLONG cache;
    JLONG gpu;
} Mesh;

typedef struct __attribute__ ((packed)) Mat4 {
    JFLOAT vals[16];
    JINT version;
    JINT is3d;
    JFLOAT cx,cy,sx,sy;
} Mat4;

typedef struct __attribute__ ((packed)) Texture {
    JLONG gpu;
    JINT width, height, hwWidth, hwHeight;
} Texture;

#define NODE_VISIBLE        1
#define NODE_LOCAL_DIRTY    2
#define NODE_VIEW_DIRTY     4
#define NODE_ROT_DIRTY      8
#define NODE_INSTAGE        16
#define NODE_CONTENTDIRTY   32


typedef struct __attribute__ ((packed)) Node {
    JINT flags;
    JFLOAT x,y,z, _x,_y,_z;
    JFLOAT sx=1,sy=1,sz=1, _sx,_sy,_sz;
    JFLOAT rx,ry,rz, _rx,_ry,_rz;
    JFLOAT skx, sky; //skew
    JFLOAT alpha=1,_alpha,worldAlpha=1;
    JFLOAT px=.5f,py=.5f;
    JFLOAT width,height, midy, midx;
    JINT numChildren, depth, parentVersion, color;
    Object *parent, *next, *prev, *firstChild, *lastChild;
    Object *local,*world, *inverse;
    Object *mesh;
    JINT material;
    Object *texture;
} Node;


inline static void Mat4_compose2D(Mat4 *mat, float x, float y, float sx, float sy, float px, float py, int rotDirty, float rot, float skx, float sky) {
    if(rotDirty) {
        double tmp = (rot + sky) / 180.0 * M_PI;
        mat->cx = fast_cos(tmp); //cos(tmp); //cos((rotation + skewY)/180.0f * M_PI);
        mat->sx = fast_sin(tmp); //sin((rotation + skewY)/180.0f * M_PI);
        if(skx != 0 || sky != 0) {
            tmp = (rot - skx) / 180.0 * M_PI;
            mat->cy = -fast_sin(tmp); //-sin((rotation - skewX)/180.0f * M_PI); // cos, added PI/2
            mat->sy = fast_cos(tmp); //cos(tmp); //cos((rotation - skewX)/180.0f * M_PI); // sin, added PI/2
        } else {
            mat->cy = -mat->sx;
            mat->sy = mat->cx;
        }
    }
    float a = mat->cx * sx;
    float b = mat->sx * sx;
    float c = mat->cy * sy;
    float d = mat->sy * sy;

    mat->vals[M2D02] = x - ((px * a) + (py * c)); //tx
    mat->vals[M2D12] = y - ((px * b) + (py * d)); //ty
    mat->vals[M2D00] = a;
    mat->vals[M2D10] = b;
    mat->vals[M2D01] = c;
    mat->vals[M2D11] = d;
    mat->version++;
    if(mat->is3d) {
        mat->vals[M02] = 0;
        mat->vals[M12] = 0;
        mat->vals[M20] = 0;
        mat->vals[M21] = 0;
        mat->vals[M22] = 1;
        mat->vals[M23] = 0;
        mat->vals[M30] = 0;
        mat->vals[M31] = 0;
        mat->vals[M32] = 0;
        mat->vals[M33] = 1;
        mat->is3d = 0;
    }
}

inline static void Mat4_mul2d(Mat4 *lhs, Mat4 *rhs, Mat4 *result) {
    float lhsm00 = lhs->vals[M2D00];
    float lhsm01 = lhs->vals[M2D01];
    float lhsm10 = lhs->vals[M2D10];
    float lhsm11 = lhs->vals[M2D11];

    float rhsm00 = rhs->vals[M2D00];
    float rhsm01 = rhs->vals[M2D01];
    float rhsm02 = rhs->vals[M2D02];
    float rhsm10 = rhs->vals[M2D10];
    float rhsm11 = rhs->vals[M2D11];
    float rhsm12 = rhs->vals[M2D12];

    // First row
    result->vals[M2D00] = lhsm00 * rhsm00 + lhsm01 * rhsm10;
    result->vals[M2D01] = lhsm00 * rhsm01 + lhsm01 * rhsm11;
    result->vals[M2D02] = lhsm00 * rhsm02 + lhsm01 * rhsm12 + lhs->vals[M2D02];

    // Second row
    result->vals[M2D10] = lhsm10 * rhsm00 + lhsm11 * rhsm10;
    result->vals[M2D11] = lhsm10 * rhsm01 + lhsm11 * rhsm11;
    result->vals[M2D12] = lhsm10 * rhsm02 + lhsm11 * rhsm12 + lhs->vals[M2D12];

    if(result->is3d) {
        result->vals[M02] = 0;
        result->vals[M12] = 0;
        result->vals[M20] = 0;
        result->vals[M21] = 0;
        result->vals[M22] = 1;
        result->vals[M23] = 0;
        result->vals[M30] = 0;
        result->vals[M31] = 0;
        result->vals[M32] = 0;
        result->vals[M33] = 1;
        result->is3d = 0;
    }
    result->version++;
}

inline static void node_update_localmatrix(Node *node) {
    int flags = node->flags;
    if(flags & (NODE_LOCAL_DIRTY|NODE_ROT_DIRTY)) {
        Mat4 *mat = (Mat4 *)node->local->instance;
        float ry = node->ry + node->_ry;
        float rx = node->rx + node->_rx;
        if(ry == 0 && rx == 0) {
            Mat4_compose2D(mat, node->x + node->_x,
                           node->y + node->_y,
                           node->sx + node->_sx,
                           node->sy + node->_sy,
                           node->midx, node->midy,
                           node->flags & NODE_ROT_DIRTY,
                           node->rz + node->_rz,
                           node->skx, node->sky);
        } else {
            //todo: compose 3d
        }
        node->flags &= ~(NODE_ROT_DIRTY | NODE_LOCAL_DIRTY);
    }
}

#endif //MY_APPLICATION_D_H
