//
//  geom.c
//  Digiplay
//
//  Created by mustafa on 20.04.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#include "geom.h"

namespace digiplay {
    float Math::SINTABLE[3] = {0,0,0};
    float Math::CosDeg(float deg) {
        return 0;
    }
    float Math::SinDeg(float deg) {
        return 0;
    }

    Matrix2D* Matrix2D::POOL = nullptr;
    
    Matrix2D* Matrix2D::Alloc() {
        Matrix2D* ret = POOL;
        if(ret) {
            ret->poolNext = nullptr;
            ret->CacheVersion = ret->ModifyCounter = 0;
            POOL = POOL->poolNext;
            ret->Identity();
            return ret;
        }
        return new Matrix2D();
    }
    
    void Matrix2D::Release(){
        poolNext = POOL;
        POOL = this;
    }
    
    Matrix2D* Matrix2D::Multiply(Matrix2D* lhs, Matrix2D* rhs, Matrix2D* result)
    {
        if (!result)
        {
            result = new Matrix2D();
        }

        //local variables are always faster than fields!
        float lhsm00 = lhs->m00;
        float lhsm01 = lhs->m01;
        float lhsm10 = lhs->m10;
        float lhsm11 = lhs->m11;

        float rhsm00 = rhs->m00;
        float rhsm01 = rhs->m01;
        float rhsm02 = rhs->m02;
        float rhsm10 = rhs->m10;
        float rhsm11 = rhs->m11;
        float rhsm12 = rhs->m12;

        // First row
        result->m00 = lhsm00 * rhsm00 + lhsm01 * rhsm10;
        result->m01 = lhsm00 * rhsm01 + lhsm01 * rhsm11;
        result->m02 = lhsm00 * rhsm02 + lhsm01 * rhsm12 + lhs->m02;

        // Second row
        result->m10 = lhsm10 * rhsm00 + lhsm11 * rhsm10;
        result->m11 = lhsm10 * rhsm01 + lhsm11 * rhsm11;
        result->m12 = lhsm10 * rhsm02 + lhsm11 * rhsm12 + lhs->m12;

        return result;
    }

}


/*
static Matrix2D* Matrix2DPool = NULL;

Matrix2D* Matrix2D_alloc() {
    Matrix2D* ret = Matrix2DPool;
    if(ret) {
        ret->cacheVersion = ret->modifyCounter = 0;
        Matrix2DPool = Matrix2DPool->poolNext;
        return ret;
    }
    
    ret = (Matrix2D*)malloc(sizeof(Matrix2D));
    memset(ret, 0, sizeof(Matrix2D));
    return ret;
}

void Matrix2D_release(Matrix2D* mat) {
    if(mat) {
        mat->poolNext = Matrix2DPool;
        Matrix2DPool = mat;
    }
}

void Matrix2D_updateRotAndSkew(Matrix2D* this, float rotation, float skewX, float skewY)
{
    this->cx = math_CosDeg(rotation + skewY);
    this->sx = math_SinDeg(rotation + skewY);
    this->cy = -math_SinDeg(rotation - skewX); // cos, added PI/2
    this->sy = math_CosDeg(rotation - skewX); // sin, added PI/2
}

void compose(Matrix2D* this, float x, float y, float scaleX, float scaleY, float pivotX, float pivotY)
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

*/
