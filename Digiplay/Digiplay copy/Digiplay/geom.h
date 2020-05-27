//
//  geom.h
//  Digiplay
//
//  Created by mustafa on 20.04.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#ifndef geom_h
#define geom_h

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

namespace digiplay {

#pragma pack(push, 1)
typedef struct VEC2 {
    float X,Y;
} VEC2;
typedef struct VEC3 {
    float X,Y,Z;
} VEC3;
typedef struct COLOR {
    unsigned char r,g,b,a;
} COLOR;
typedef struct VERTEX2D {
    VEC3 Pos;
    VEC2 Uv;
    COLOR Color;
} VERTEX2D;
#pragma pack(pop)

class Math {
public:
    static float SINTABLE[3];
    static float CosDeg(float deg);
    static float SinDeg(float deg);
};

typedef struct Point2D {
public:
    float X,Y;
    Point2D(float x=0, float y=0) {
        this->X = x;
        this->Y = y;
    }
} Point2D;

class Matrix2D {
public:
    float m00,m10,m01,m11,m02,m12,cx,cy,sx,sy;
    Matrix2D* poolNext;
    int ModifyCounter, CacheVersion;
    
    Matrix2D() {
        poolNext = nullptr;
        ModifyCounter = CacheVersion = 0;
        Identity();
    }
    
    static Matrix2D* POOL;
    static Matrix2D* Alloc();
    void Release();
    static Matrix2D* Multiply(Matrix2D* lhs, Matrix2D* rhs, Matrix2D* result = nullptr);
    void Set(float m00, float m10, float m01, float m11, float m02, float m12)
    {
        this->m00 = m00; this->m01 = m01; this->m02 = m02;
        this->m10 = m10; this->m11 = m11; this->m12 = m12;
    }

    void CopyFrom(Matrix2D* s)
    {
        this->m00 = s->m00; this->m01 = s->m01; this->m02 = s->m02;
        this->m10 = s->m10; this->m11 = s->m11; this->m12 = s->m12;
    }

    /**
     * Sets this matrix to the identity matrix.
     */
    void Identity()
    {
        Set(1, 0, 0, 1, 0, 0);
        this->cx = 1; // cos rotation + skewY;
        this->sx = 0; // sin rotation + skewY;
        this->cy = 0; // cos rotation + Math.PI/2 - skewX;
        this->sy = 1; // sin rotation + Math.PI/2 - skewX;
        ModifyCounter++;
    }

    void UpdateRotAndSkew(float rotation, float skewX, float skewY) {
        this->cx = Math::CosDeg(rotation + skewY);
        this->sx = Math::SinDeg(rotation + skewY);
        this->cy = Math::SinDeg(rotation - skewX); // cos, added PI/2
        this->sy = Math::CosDeg(rotation - skewX); // sin, added PI/2
    }
    
    void Compose(float x, float y, float scaleX, float scaleY, float pivotX, float pivotY)
    {
        float a = this->cx * scaleX;
        float b = this->sx * scaleX;
        float c = this->cy * scaleY;
        float d = this->sy * scaleY;

        this->m02 = x - ((pivotX * a) + (pivotY * c)); //tx
        this->m12 = y - ((pivotX * b) + (pivotY * d)); //ty
        this->m00 = a;
        this->m10 = b;
        this->m01 = c;
        this->m11 = d;
    }

};

}

/*
typedef struct Matrix2D {
    float m00,m10,m01,m11,m02,m12,cx,cy,sx,sy;
    struct Matrix2D* poolNext;
    int modifyCounter, cacheVersion;
} Matrix2D;

Matrix2D* Matrix2D_alloc();
void Matrix2D_release(Matrix2D* mat);
void Matrix2D_updateRotAndSkew(Matrix2D* this, float rotation, float skewX, float skewY);
void compose(Matrix2D* this, float x, float y, float scaleX, float scaleY, float pivotX, float pivotY);
*/

#endif /* geom_h */
