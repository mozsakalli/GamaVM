//
//  digiplay.h
//  digi
//
//  Created by mustafa on 9.06.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#ifndef digiplay_h
#define digiplay_h

#include <math.h>

typedef struct VEC2 {
    float x,y;
} VEC2;
typedef struct VEC3 {
    float x,y,z;
} VEC3;
typedef struct COLOR {
    unsigned char r,g,b,a;
} COLOR;
typedef struct VERT2D {
    VEC3 pos;
    COLOR color;
    VEC2 uv;
} VERT2D;

typedef struct Mat2D {
    int meshVersion;
    int hierarchyVersion;
    float _cx,_cy,_sx,_sy;
    float m00;
    float m10;
    float m01;
    float m11;
    float m02;
    float m12;
} Mat2D;

typedef struct Mat3D {
    float vals[16];
} Mat3D;

typedef struct QuadMeshItem {
    VEC2 tl, br;
    VEC2 t1, t2, t3, t4;
    VEC3 p1, p2, p3, p4;
} QuadMeshItem;

typedef struct QuadMesh {
    int version;
    int capacity;
    int size;
    QuadMeshItem *items;
    struct QuadMesh *next;
} QuadMesh;


inline static void mat2d_identity(Mat2D *m) {
     memset(m, 0, sizeof(Mat2D));
     m->m00 = m->m11 = 1;
     m->_cx = 1; // cos rotation + skewY;
     m->_sy = 1; // sin rotation + Math.PI/2 - skewX;
    m->hierarchyVersion++;
    m->meshVersion++;
}

inline static void mat2d_compose(Mat2D *m, float x, float y, float scaleX, float scaleY, float pivotX, float pivotY, int rotSkew, float rotation, float skewX, float skewY) {
    if(rotSkew) {
        //rotation = rotation / 180.0f * MathF.PI;
        m->_cx = cos((rotation + skewY)/180.0f * M_PI);
        m->_sx = sin((rotation + skewY)/180.0f * M_PI);
        m->_cy = -sin((rotation - skewX)/180.0f * M_PI); // cos, added PI/2
        m->_sy = cos((rotation - skewX)/180.0f * M_PI); // sin, added PI/2
    }
    
    float a = m->_cx * scaleX;
    float b = m->_sx * scaleX;
    float c = m->_cy * scaleY;
    float d = m->_sy * scaleY;

    m->m02 = x - ((pivotX * a) + (pivotY * c)); //tx
    m->m12 = y - ((pivotX * b) + (pivotY * d)); //ty
    m->m00 = a;
    m->m10 = b;
    m->m01 = c;
    m->m11 = d;
    m->meshVersion++;
    m->hierarchyVersion++;
}


extern void mat3d_identity(Mat3D *m);
extern void mat3d_setup2d(Mat3D *m, float width, float height);
extern void mat3d_multiply(Mat3D *lhs, Mat3D *rhs, Mat3D *result);

#endif /* digiplay_h */
