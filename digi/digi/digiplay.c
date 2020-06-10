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
    mat3d_perspective(&projectionMatrix, 1, far, fov, width/height);
    mat3d_multiply(&projectionMatrix, &localMatrix, m);
}

/*
 public void set(float m00, float m10, float m01, float m11, float m02, float m12)
 {
     this.m00 = m00; this.m01 = m01; this.m02 = m02;
     this.m10 = m10; this.m11 = m11; this.m12 = m12;
 }

 */
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
    m->meshVersion = m->hierarchyVersion = -1;
}
void Java_digiplay_Mat2D_identity(VM *vm, Object *method, VAR *args) {
    if(!args[0].O) {
        throw_null(vm);
        return;
    }
    
    Mat2D *m = (Mat2D*)*FIELD_PTR_O(args[0].O, 0);
    mat2d_identity(m);
}

extern void Java_digiplay_Platform_run(VM *vm, Object *method, VAR *args);

NativeMethodInfo digiplay_native_methods[] = {
    {"digiplay/Platform:run:()V", &Java_digiplay_Platform_run},
    
    {"digiplay/Mat2D:create:()J", &Java_digiplay_Mat2D_create},
    {"digiplay/Mat2D:compose:(FFFFFFZFFF)V", &Java_digiplay_Mat2D_compose},
    {"digiplay/Mat2D:identity:()V", &Java_digiplay_Mat2D_identity},

    NULL
};
