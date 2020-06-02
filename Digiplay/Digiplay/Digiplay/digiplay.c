//
//  digiplay.c
//  Digiplay
//
//  Created by mustafa on 20.04.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#include "jvm.h"
#include <math.h>

typedef struct __attribute__ ((packed)) Vec2 {
    float x,y;
} Vec2;

typedef struct __attribute__ ((packed)) Vec3 {
    float x,y,z;
} Vec3;

typedef struct __attribute__ ((packed)) Color {
    unsigned char r,g,b,a;
} Color;

typedef struct Quad {
    Vec2 tl;
    Vec2 br;
    Vec2 uv1, uv2, uv3, uv4;
    Vec3 p1, p2, p3, p4;
} Quad;

typedef struct QuadList {
    Quad *quads;
    jint capacity;
    jint size;
    struct QuadList *next;
} QuadList;

typedef struct Matrix2D {
    float m00,m10,m01,m11,m02,m12,cx,cy,sx,sy, _cx,_cy,_sx,_sy, _rot, _skewx, _skewy;
    struct Matrix2D *next;
} Matrix2D;

#define RETURN_LONG(v) vm->frames[vm->FP].retVal.J = (jlong)(v)
#define RETURN_FLOAT(v) vm->frames[vm->FP].retVal.J = (jfloat)(v)

#define sin_precision   100 // gradations per degree, adjust to suit
#define sin_modulus     (360 * sin_precision)
static float SinTable[sin_modulus];
void digiplay_Digiplay_init(VM *vm, Object *method, VAR *args) {
    for (int i = 0; i < sin_modulus; i++)
        SinTable[i] = sin((i * M_PI) / (sin_precision * 180));
}
float sindeg(float deg) {
    int a = (int)(deg * sin_precision + 0.5f);
    return a >= 0 ? SinTable[a % sin_modulus] : -SinTable[(-a) % sin_modulus];
}
#define cosdeg(deg) sindeg((deg + 90))

void digiplay_Digiplay_math_sindeg(VM *vm, Object *method, VAR *args) {
    RETURN_FLOAT(sindeg(args[0].F));
}
void digiplay_Digiplay_math_cosdeg(VM *vm, Object *method, VAR *args) {
    RETURN_FLOAT(cosdeg(args[0].F));
}
/*
[MethodImpl(MethodImplOptions.AggressiveInlining)]
public static unsafe float CosDeg(float degree)
{
    fixed (float* ptr = sinTable)
    {
        var a = (int)((degree + 90) * precision + 0.5f);
        return a >= 0 ? ptr[a % modulus] : -ptr[(-a) % modulus];
    }
}

[MethodImpl(MethodImplOptions.AggressiveInlining)]
public unsafe static float Sin(float radian)
{
    fixed (float* ptr = sinTable)
    {
        var a = (int)(radian / PI * 180 * precision + 0.5f);
        return a >= 0 ? ptr[a % modulus] : -ptr[(-a) % modulus];
    }
}

[MethodImpl(MethodImplOptions.AggressiveInlining)]
public static unsafe float Cos(float degree)
{
    fixed (float* ptr = sinTable)
    {
        var a = (int)((degree / PI * 180 + 90) * precision + 0.5f);
        return a >= 0 ? ptr[a % modulus] : -ptr[(-a) % modulus];
    }
}
*/

static QuadList *QuadCache = NULL;
void digiplay_Digiplay_quad_new(VM *vm, Object *method, VAR *args) {
    jint capacity = args[0].I;
    QuadList *ret = QuadCache;
    if(ret) {
        QuadCache = QuadCache->next;
        if(ret->capacity < capacity) {
            ret->quads = realloc(ret->quads, sizeof(Quad) * capacity);
            ret->capacity = capacity;
        }
    } else {
        ret = (QuadList*)malloc(sizeof(QuadList));
        ret->quads = (Quad*)malloc(sizeof(Quad) * capacity);
        ret->capacity = capacity;
    }
    ret->size = capacity;
    RETURN_LONG(ret);
}
void digiplay_Digiplay_quad_resize(VM *vm, Object *method, VAR *args) {
    QuadList *ql = (QuadList*)args[0].J;
    jint capacity = args[1].I;
    if(ql) {
        if(capacity > 0 && capacity < ql->capacity) {
            ql->quads = realloc(ql->quads, sizeof(Quad) * capacity);
            ql->capacity = capacity;
        }
        ql->size = capacity;
    }
}
void digiplay_Digiplay_quad_delete(VM *vm, Object *method, VAR *args) {
    if(args[0].J) {
        QuadList *ql = (QuadList*)args[0].J;
        ql->next = QuadCache;
        QuadCache = ql;
    }
}
void digiplay_Digiplay_quad_update(VM *vm, Object *method, VAR *args) {
    if(args[0].J && args[1].J) {
        QuadList *ql = (QuadList*)args[0].J;
        Matrix2D *matrix = (Matrix2D*)args[1].J;
        float m00 = matrix->m00;
        float m01 = matrix->m01;
        float m02 = matrix->m02;
        float m10 = matrix->m10;
        float m11 = matrix->m11;
        float m12 = matrix->m12;

        for(int i=0; i<ql->size; i++) {
            Quad *q = &ql->quads[i];
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

            q->p1.x = xm00 + ym01m02;
            q->p1.y = xm10 + ym11m12;
            q->p2.x = x2m00 + ym01m02;
            q->p2.y = x2m10 + ym11m12;
            q->p3.x = x2m00 + y2m01m02;
            q->p3.y = x2m10 + y2m11m12;
            q->p4.x = xm00 + y2m01m02;
            q->p4.y = xm10 + y2m11m12;
        }
    }
}
void digiplay_Digiplay_quad_set(VM *vm, Object *method, VAR *args) {
    QuadList *ql = (QuadList*)args[0].J;
    int index = args[1].I;
    if(ql && index >= 0 && index < ql->capacity) {
        Quad *q = &ql->quads[index];
        q->tl.x = args[2].F;
        q->tl.y = args[3].F;
        q->br.x = args[4].F;
        q->br.y = args[5].F;
        q->uv1.x = args[6].F;
        q->uv1.y = args[7].F;
        q->uv2.x = args[8].F;
        q->uv2.y = args[9].F;
        q->uv3.x = args[10].F;
        q->uv3.y = args[11].F;
        q->uv4.x = args[12].F;
        q->uv4.y = args[13].F;
    }
}

static Matrix2D *Matrix2DCache = NULL;
void digiplay_Digiplay_Matrix2d_alloc(VM *vm, Object *method, VAR *args) {
    Matrix2D *ret = Matrix2DCache;
    if(ret) {
        Matrix2DCache = Matrix2DCache->next;
    } else {
        ret = (Matrix2D*)malloc(sizeof(Matrix2D));
    }
    RETURN_LONG(ret);
}
void digiplay_Disiplay_Matrix2d_delete(VM *vm, Object *method, VAR *args) {
    if(args[0].J) {
        Matrix2D *mat = (Matrix2D*)args[0].J;
        mat->next = Matrix2DCache;
        Matrix2DCache = mat;
    }
}
void digiplay_Digiplay_Matrix2d_compose(VM *vm, Object *method, VAR *args) {
    if(args[0].J) {
        Matrix2D *mat = (Matrix2D*)args[0].J;
        float x = args[1].F;
        float y = args[2].F;
        float scaleX = args[3].F;
        float scaleY = args[4].F;
        float pivotX = args[5].F;
        float pivotY = args[6].F;
        int update_rot = args[7].I;
        if(update_rot) {
            float rotation = args[7].F;
            float skewX = args[8].F;
            float skewY = args[9].F;
            mat->_cx = cosdeg(rotation + skewY);
            mat->_sx = sindeg(rotation + skewY);
            mat->_cy = -sindeg(rotation - skewX); // cos, added PI/2
            mat->_sy = cosdeg(rotation - skewX); // sin, added PI/2
        }
        
        float a = mat->_cx * scaleX;
        float b = mat->_sx * scaleX;
        float c = mat->_cy * scaleY;
        float d = mat->_sy * scaleY;

        mat->m02 = x - ((pivotX * a) + (pivotY * c)); //tx
        mat->m12 = y - ((pivotX * b) + (pivotY * d)); //ty
        mat->m00 = a;
        mat->m10 = b;
        mat->m01 = c;
        mat->m11 = d;
    }
}

void digiplay_Digiplay_Matrix2d_multiply(VM *vm, Object *method, VAR *args) {
    if(args[0].J && args[1].J && args[2].J) {
        Matrix2D *lhs = (Matrix2D*)args[0].J;
        Matrix2D *rhs = (Matrix2D*)args[1].J;
        Matrix2D *result = (Matrix2D*)args[2].J;
        
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
    }
}

/*
#include "digiplay.h"

namespace digiplay {

int Sprite2D::GlobalFrameVersion = 0;
int Sprite2D::InvalidationCounter = 0;

Bag<Sprite2D*> Sprite2D::IterateBag;
void Sprite2D::IterateChildren(Sprite2D* root, Action action) {
    if(!root) return;
    IterateBag.Reset();
    IterateBag.Add(root);
    int index = 0;
    while (index < IterateBag.Count) {
        Sprite2D* item = IterateBag.Items[index++];
        action(item);
        Sprite2D* ptr = item->FirstChild;
        while (ptr) {
            IterateBag.Add(ptr);
            ptr = ptr->Next;
        }
    }
}

void Sprite2D::SetInStage()
{
    if ((Flags & IN_STAGE) != 0) return;
    Flags |= IN_STAGE;
    MarkContentInvalid();
    Sprite2D* ptr = FirstChild;
    while (ptr)
    {
        ptr->SetInStage();
        ptr = ptr->Next;
    }

    if (_Parent == Stage2D::I)
        InvalidateContent();

    Init();
    //OnInit?.Invoke(this);
}


Stage2D* Stage2D::I = nullptr;

}
*/
