//
//  digiplay.c
//  digi
//
//  Created by mustafa on 9.06.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//
#include "vm.h"
#include "digiplay.h"
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

//MAT3D
void mat3d_identity(Mat3D *m) {
    m->vals[M00] = 1;
    m->vals[M01] = 0;
    m->vals[M02] = 0;
    m->vals[M03] = 0;
    m->vals[M10] = 0;
    m->vals[M11] = 1;
    m->vals[M12] = 0;
    m->vals[M13] = 0;
    m->vals[M20] = 0;
    m->vals[M21] = 0;
    m->vals[M22] = 1;
    m->vals[M23] = 0;
    m->vals[M30] = 0;
    m->vals[M31] = 0;
    m->vals[M32] = 0;
    m->vals[M33] = 1;
}

void mat3d_set(Mat3D *m,float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33) {
    m->vals[M00] = m00;
    m->vals[M01] = m01;
    m->vals[M02] = m02;
    m->vals[M03] = m03;
    m->vals[M10] = m10;
    m->vals[M11] = m11;
    m->vals[M12] = m12;
    m->vals[M13] = m13;
    m->vals[M20] = m20;
    m->vals[M21] = m21;
    m->vals[M22] = m22;
    m->vals[M23] = m23;
    m->vals[M30] = m30;
    m->vals[M31] = m31;
    m->vals[M32] = m32;
    m->vals[M33] = m33;
}

void mat3d_set2(Mat3D *m,float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33) {
    m->vals[M00] = m00;
    m->vals[M10] = m01;
    m->vals[M20] = m02;
    m->vals[M30] = m03;
    m->vals[M01] = m10;
    m->vals[M11] = m11;
    m->vals[M21] = m12;
    m->vals[M31] = m13;
    m->vals[M02] = m20;
    m->vals[M12] = m21;
    m->vals[M22] = m22;
    m->vals[M32] = m23;
    m->vals[M03] = m30;
    m->vals[M13] = m31;
    m->vals[M23] = m32;
    m->vals[M33] = m33;
}

void mat3d_multiply(Mat3D *lhs, Mat3D *rhs, Mat3D *result) {
    float m111, m121, m131, m141, m112, m122, m132, m142, m113, m123, m133, m143, m114, m124, m134, m144;
    float *ptr = &rhs->vals[0];
    m111 = ptr[0];
    m121 = ptr[4];
    m131 = ptr[8];
    m141 = ptr[12];

    m112 = ptr[1];
    m122 = ptr[5];
    m132 = ptr[9];
    m142 = ptr[13];

    m113 = ptr[2];
    m123 = ptr[6];
    m133 = ptr[10];
    m143 = ptr[14];

    m114 = ptr[3];
    m124 = ptr[7];
    m134 = ptr[11];
    m144 = ptr[15];

    float m211, m221, m231, m241, m212, m222, m232, m242, m213, m223, m233, m243, m214, m224, m234, m244;

    ptr = &lhs->vals[0];
    m211 = ptr[0];
    m221 = ptr[4];
    m231 = ptr[8];
    m241 = ptr[12];

    m212 = ptr[1];
    m222 = ptr[5];
    m232 = ptr[9];
    m242 = ptr[13];

    m213 = ptr[2];
    m223 = ptr[6];
    m233 = ptr[10];
    m243 = ptr[14];

    m214 = ptr[3];
    m224 = ptr[7];
    m234 = ptr[11];
    m244 = ptr[15];
    float *raw = &result->vals[0];
    raw[0] = m111 * m211 + m112 * m221 + m113 * m231 + m114 * m241;
    raw[1] = m111 * m212 + m112 * m222 + m113 * m232 + m114 * m242;
    raw[2] = m111 * m213 + m112 * m223 + m113 * m233 + m114 * m243;
    raw[3] = m111 * m214 + m112 * m224 + m113 * m234 + m114 * m244;

    raw[4] = m121 * m211 + m122 * m221 + m123 * m231 + m124 * m241;
    raw[5] = m121 * m212 + m122 * m222 + m123 * m232 + m124 * m242;
    raw[6] = m121 * m213 + m122 * m223 + m123 * m233 + m124 * m243;
    raw[7] = m121 * m214 + m122 * m224 + m123 * m234 + m124 * m244;

    raw[8] = m131 * m211 + m132 * m221 + m133 * m231 + m134 * m241;
    raw[9] = m131 * m212 + m132 * m222 + m133 * m232 + m134 * m242;
    raw[10] = m131 * m213 + m132 * m223 + m133 * m233 + m134 * m243;
    raw[11] = m131 * m214 + m132 * m224 + m133 * m234 + m134 * m244;

    raw[12] = m141 * m211 + m142 * m221 + m143 * m231 + m144 * m241;
    raw[13] = m141 * m212 + m142 * m222 + m143 * m232 + m144 * m242;
    raw[14] = m141 * m213 + m142 * m223 + m143 * m233 + m144 * m243;
    raw[15] = m141 * m214 + m142 * m224 + m143 * m234 + m144 * m244;
}

void mat3d_lookAt(Mat3D *m, float eyeX, float eyeY, float eyeZ, float atX, float atY, float atZ, float upX, float upY, float upZ) {
    //normalize(eye - at)
    float azX = eyeX - atX;
    float azY = eyeY - atY;
    float azZ = eyeZ - atZ;
    float tmp = 1.0f / (float)sqrt(azX * azX + azY * azY + azZ * azZ);
    azX *= tmp;
    azY *= tmp;
    azZ *= tmp;

    //normalize(cross(up, az))
    float axX = upY * azZ - upZ * azY;
    float axY = upZ * azX - upX * azZ;
    float axZ = upX * azY - upY * azX;
    tmp = (float) sqrt(axX * axX + axY * axY + axZ * axZ);
    if (tmp == 0) {
        axX = azX;
        axY = azY;
        axZ = azZ;
    } else {
        tmp = 1.0f / tmp;
        axX *= tmp;
        axY *= tmp;
        axZ *= tmp;
    }

    //cross(az, ax)
    float ayX = azY * axZ - azZ * axY;
    float ayY = azZ * axX - azX * axZ;
    float ayZ = azX * axY - azY * axX;

    mat3d_set2(m,
            axX, ayX, azX, 0,
            axY, ayY, azY, 0,
            axZ, ayZ, azZ, 0,
            0, 0, 0, 1);

    Mat3D T;
    mat3d_set2(&T,
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            -eyeX, -eyeY, -eyeZ, 1
    );
    mat3d_multiply(m, &T, m);
}

void mat3d_perspective(Mat3D *m, float near, float far, float fovy, float aspectRatio) {
    mat3d_identity(m);
    float l_fd = (float) (1.0f / tan((fovy * (M_PI / 180)) / 2.0f));
    float l_a1 = (far + near) / (near - far);
    float l_a2 = (2 * far * near) / (near - far);
    m->vals[M00] = l_fd / aspectRatio;
    m->vals[M10] = 0;
    m->vals[M20] = 0;
    m->vals[M30] = 0;
    m->vals[M01] = 0;
    m->vals[M11] = l_fd;
    m->vals[M21] = 0;
    m->vals[M31] = 0;
    m->vals[M02] = 0;
    m->vals[M12] = 0;
    m->vals[M22] = l_a1;
    m->vals[M32] = -1;
    m->vals[M03] = 0;
    m->vals[M13] = 0;
    m->vals[M23] = l_a2;
    m->vals[M33] = 0;
}

void mat3d_compose(Mat3D *m, float _x, float _y, float _z, float _rx, float _ry, float _rz, float _sx, float _sy, float _sz) {
    float rxd = _rx / 180.0f * M_PI;
    float ryd = _ry / 180.0f * M_PI;
    float rzd = _rz / 180.0f * M_PI;
    float cx = fast_cos(rxd);
    float cy = fast_cos(ryd);
    float cz = fast_cos(rzd);
    float sx = fast_sin(rxd);
    float sy = fast_sin(ryd);
    float sz = fast_sin(rzd);
    
    float *ptr = &m->vals[0];
    ptr[0] = cy * cz * _sx;
    ptr[1] = cy * sz * _sx;
    ptr[2] = -sy * _sx;
    ptr[3] = 0;
    ptr[4] = (sx * sy * cz - cx * sz) * _sy;
    ptr[5] = (sx * sy * sz + cx * cz) * _sy;
    ptr[6] = sx * cy * _sy;
    ptr[7] = 0;
    ptr[8] = (cx * sy * cz + sx * sz) * _sz;
    ptr[9] = (cx * sy * sz - sx * cz) * _sz;
    ptr[10] = cx * cy * _sz;
    ptr[11] = 0;
    ptr[12] = _x;
    ptr[13] = _y;
    ptr[14] = _z;
    ptr[15] = 1;
}

void mat3d_orthographic(Mat3D *m, float left, float right, float bottom, float top, float near, float far)
{
    mat3d_identity(m);
    float x_orth = 2 / (right - left);
    float y_orth = 2 / (top - bottom);
    float z_orth = -2 / (far - near);

    float tx = -(right + left) / (right - left);
    float ty = -(top + bottom) / (top - bottom);
    float tz = -(far + near) / (far - near);
    float *raw = &m->vals[0];
    raw[M00] = x_orth;
    raw[M10] = 0;
    raw[M20] = 0;
    raw[M30] = 0;
    raw[M01] = 0;
    raw[M11] = y_orth;
    raw[M21] = 0;
    raw[M31] = 0;
    raw[M02] = 0;
    raw[M12] = 0;
    raw[M22] = z_orth;
    raw[M32] = 0;
    raw[M03] = tx;
    raw[M13] = ty;
    raw[M23] = tz;
    raw[M33] = 1;
}

void mat3d_setup2d(Mat3D *m, float width, float height) {
    float x = width / 2;
    float y = height / 2;
    //Camera.z = -height / Z;
    float YUp = -1;
    float fov = 20;
    float far = 100000;
    float ZDIVISOR2D = (2.0 * tan(fov / 180.0 * M_PI / 2.0));
    float z = -height / ZDIVISOR2D;

    Mat3D localMatrix, projectionMatrix;
    mat3d_lookAt(&localMatrix, x, y, z,  x, y, 0,  0, YUp, 0);
    mat3d_perspective(&projectionMatrix, 0, far, fov, width/height);
    mat3d_multiply(&projectionMatrix, &localMatrix, m);
}


//Mat2D
void Java_digiplay_Mat2D_create(VM *vm, Object *method, VAR *args) {
    Mat2D *m = (Mat2D*)vm_alloc(sizeof(Mat2D));
    mat2d_identity(m);
    RETURN_J(m);
}
void Java_digiplay_Mat2D_compose(VM *vm, Object *method, VAR *args) {
    if(!args[0].O) {
        throw_null(vm);
        return;
    }
    
    Mat2D *m = (Mat2D*)*FIELD_PTR_O(args[0].O, 0);
    mat2d_compose(m, args[1].F, args[2].F, args[3].F, args[4].F, args[5].F, args[6].F, args[7].I, args[8].F, args[9].F, args[10].F);
}
void Java_digiplay_Mat2D_identity(VM *vm, Object *method, VAR *args) {
    if(!args[0].O) {
        throw_null(vm);
        return;
    }
    
    Mat2D *m = (Mat2D*)*FIELD_PTR_O(args[0].O, 0);
    mat2d_identity(m);
}
void Java_digiplay_Mat2D_multiply(VM *vm, Object *method, VAR *args) {
    if(!args[0].O || !args[1].O || !args[2].O) {
        throw_null(vm);
        return;
    }
    mat2d_multiply((Mat2D*)*FIELD_PTR_O(args[0].O, 0), (Mat2D*)*FIELD_PTR_O(args[1].O, 0), (Mat2D*)*FIELD_PTR_O(args[2].O, 0));
}



void Java_digiplay_Sprite2D_getLocalMatrix(VM *vm, Object *method, VAR *args) {
    if(!args[0].O) {
        throw_null(vm);
        return;
    }
    Sprite2D *sprite = args[0].O->instance;
    sprite2d_update_localmatrix(sprite);
    vm->frames[vm->FP].ret.O = sprite->localMatrix;
}

void Java_digiplay_Sprite2D_getWorldMatrix(VM *vm, Object *method, VAR *args) {
    if(!args[0].O) {
        throw_null(vm);
        return;
    }
    Sprite2D *sprite = args[0].O->instance;
    int gloalFrameVersion = args[1].I;
    if(gloalFrameVersion != sprite->frameVersion) {
        int lastUpdateCount = sprite->matrixUpdateCount;
        sprite2d_update_localmatrix(sprite);
        Sprite2D *parent = sprite->parent ? sprite->parent->instance : NULL;
        if(parent) {
            VAR tmp[1] = {{.O = sprite->parent}};
            Java_digiplay_Sprite2D_getWorldMatrix(vm, method, &tmp[0]);
            if(parent->matrixUpdateCount != sprite->parentMatrixUpdateCount || lastUpdateCount != sprite->matrixUpdateCount) {
                mat2d_multiply((Mat2D *)*FIELD_PTR_O(parent->worldMatrix, 0), (Mat2D *)*FIELD_PTR_O(sprite->localMatrix, 0), (Mat2D *)*FIELD_PTR_O(sprite->worldMatrix, 0));
                sprite->parentMatrixUpdateCount = parent->matrixUpdateCount;
                sprite->matrixUpdateCount++;
            }
        } else {
            memcpy((Mat2D *)*FIELD_PTR_O(sprite->worldMatrix, 0), (Mat2D *)*FIELD_PTR_O(sprite->localMatrix, 0),sizeof(Mat2D));
        }
        sprite->frameVersion = gloalFrameVersion;
    }
    vm->frames[vm->FP].ret.O = sprite->worldMatrix;
}

void Java_digiplay_Sprite2D_drawChildren(VM *vm, Object *method, VAR *args) {
    if(!args[0].O) {
        throw_null(vm);
        return;
    }
    static int drawMethodIndex = -1;
    if(drawMethodIndex == -1) {
        Object *mth =
        resolve_method(vm,
                       MTH_LOADER(method),
                       (JCHAR*)L"digiplay/Sprite2D",17,
                       (JCHAR*)L"draw",4,
                       (JCHAR*)L"()V",3);
        if(!mth) return;
        drawMethodIndex = MTH(mth, vTableIndex);
    }
    Sprite2D *sprite = args[0].O->instance;
    Object *ptr = sprite->firstChild;
    VAR callArgs[1];
    while(ptr) {
        Sprite2D *child = ptr->instance;
        if((child->flags & 1) && child->worldAlpha > 0) {
            VMClass *cls = ptr->cls->instance;
            callArgs[0].O = ptr;
            CALLVM_V(vm, cls->vtable[drawMethodIndex], &callArgs[0]);
            if(child->firstChild)
                Java_digiplay_Sprite2D_drawChildren(vm, method, &callArgs[0]);
        }
        ptr = child->next;
    }
}


//extern void Java_digiplay_Platform_run(VM *vm, Object *method, VAR *args);
//extern void Java_digiplay_Net_http(VM *vm, Object *method, VAR *args);


NativeMethodInfo digiplay_native_methods[] = {
    //{"digiplay/Platform:run:()V", &Java_digiplay_Platform_run},
    
    {"digiplay/Mat2D:create:()J", &Java_digiplay_Mat2D_create},
    {"digiplay/Mat2D:compose:(FFFFFFZFFF)V", &Java_digiplay_Mat2D_compose},
    {"digiplay/Mat2D:identity:()V", &Java_digiplay_Mat2D_identity},
    {"digiplay/Mat2D:multiply:(Ldigiplay/Mat2D;Ldigiplay/Mat2D;Ldigiplay/Mat2D;)V", &Java_digiplay_Mat2D_multiply},

    //{"digiplay/Net:http:(Ljava/lang/String;Ljava/lang/String;Ldigiplay/Net$HttpListener;)V", &Java_digiplay_Net_http},

    {"digiplay/Sprite2D:getLocalMatrix:()Ldigiplay/Mat2D;", &Java_digiplay_Sprite2D_getLocalMatrix},
    {"digiplay/Sprite2D:getWorldMatrix:(I)Ldigiplay/Mat2D;", &Java_digiplay_Sprite2D_getWorldMatrix},
    {"digiplay/Sprite2D:drawChildren:()V", &Java_digiplay_Sprite2D_drawChildren},


    NULL
};
