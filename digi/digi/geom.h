//
// Created by mustafa on 2020-06-28.
//

#ifndef GEOM_H_
#define GEOM_H_

#include "vm.h"
#include <math.h>

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

typedef struct __attribute__ ((packed)) Mat4 {
    JFLOAT vals[16];
    JINT version;
    JINT is3d;
    JFLOAT cx,cy,cz,sx,sy,sz;
} Mat4;

inline static void mat4_identity(Mat4 *m) {
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

inline static void mat4_set(Mat4 *m,float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33) {
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

inline static void mat4_set2(Mat4 *m,float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33) {
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

inline static void mat4_multiply(Mat4 *lhs, Mat4 *rhs, Mat4 *result) {
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
    result->version++;
}
inline static void mat4_lookAt(Mat4 *m, float eyeX, float eyeY, float eyeZ, float atX, float atY, float atZ, float upX, float upY, float upZ) {
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

    mat4_set2(m,
              axX, ayX, azX, 0,
              axY, ayY, azY, 0,
              axZ, ayZ, azZ, 0,
              0, 0, 0, 1);

    Mat4 T;
    mat4_set2(&T,
              1, 0, 0, 0,
              0, 1, 0, 0,
              0, 0, 1, 0,
              -eyeX, -eyeY, -eyeZ, 1
    );
    mat4_multiply(m, &T, m);
}
inline static void mat4_perspective(Mat4 *m, float near, float far, float fovy, float aspectRatio) {
    mat4_identity(m);
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
inline static void mat4_setup2d(Mat4 *m, float width, float height) {
    float x = width / 2;
    float y = height / 2;
    //Camera.z = -height / Z;
    float YUp = -1;
    float fov = 20;
    float far = 100000;
    float ZDIVISOR2D = (2.0 * tan(fov / 180.0 * M_PI / 2.0));
    float z = -height / ZDIVISOR2D;

    Mat4 localMatrix, projectionMatrix;
    mat4_lookAt(&localMatrix, x, y, z,  x, y, 0,  0, YUp, 0);
    mat4_perspective(&projectionMatrix, 0, far, fov, width/height);
    mat4_multiply(&projectionMatrix, &localMatrix, m);
}
inline static void mat4_compose2D(Mat4 *mat, float x, float y, float sx, float sy, float px, float py, int rotDirty, float rot, float skx, float sky) {
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
inline static void mat4_compose(Mat4 *mat, float _x, float _y, float _z, float _rx, float _ry, float _rz, float _sx, float _sy, float _sz, int rotDirty) {
    if(rotDirty) {
        _rx = _rx / 180.0f * M_PI;
        _ry = _ry / 180.0f * M_PI;
        _rz = _rz / 180.0f * M_PI;
        mat->cx = fast_cos(_rx);
        mat->cy = fast_cos(_ry);
        mat->cz = fast_cos(_rz);
        mat->sx = fast_sin(_rx);
        mat->sy = fast_sin(_ry);
        mat->sz = fast_sin(_rz);
    }
    float cx = mat->cx;
    float cy = mat->cy;
    float cz = mat->cz;
    float sx = mat->sx;
    float sy = mat->sy;
    float sz = mat->sz;

    mat->vals[0] = cy * cz * _sx;
    mat->vals[1] = cy * sz * _sx;
    mat->vals[2] = -sy * _sx;
    mat->vals[3] = 0;
    mat->vals[4] = (sx * sy * cz - cx * sz) * _sy;
    mat->vals[5] = (sx * sy * sz + cx * cz) * _sy;
    mat->vals[6] = sx * cy * _sy;
    mat->vals[7] = 0;
    mat->vals[8] = (cx * sy * cz + sx * sz) * _sz;
    mat->vals[9] = (cx * sy * sz - sx * cz) * _sz;
    mat->vals[10] = cx * cy * _sz;
    mat->vals[11] = 0;
    mat->vals[12] = _x;
    mat->vals[13] = _y;
    mat->vals[14] = _z;
    mat->vals[15] = 1;
    mat->is3d = 1;
    mat->version++;
}
inline static void mat4_multiply2d(Mat4 *lhs, Mat4 *rhs, Mat4 *result) {
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
inline static void mat4_prependTranslation(Mat4 *mat,
        float translationX, float translationY, float translationZ) {
    return;
    mat->vals[03] += mat->vals[M00] * translationX + mat->vals[M10] * translationY + mat->vals[M20] * translationZ;
    mat->vals[07] += mat->vals[M01] * translationX + mat->vals[M11] * translationY + mat->vals[M21] * translationZ;
    mat->vals[11] += mat->vals[M02] * translationX + mat->vals[M12] * translationY + mat->vals[M22] * translationZ;
    mat->vals[15] += mat->vals[M03] * translationX + mat->vals[M13] * translationY + mat->vals[M23] * translationZ;
}
inline static void mat4_project(Mat4 *mat, VEC3 *pt) {
    if(mat->is3d) {

    } else {
        float x = pt->x * mat->vals[M2D00] + pt->y * mat->vals[M2D01] + mat->vals[M2D02];
        float y = pt->x * mat->vals[M2D10] + pt->y * mat->vals[M2D11] + mat->vals[M2D12];
        pt->x = x;
        pt->y = y;
        pt->z = 0;
    }
}




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

#endif //GEOM_H_
