//
// Created by mustafa on 2020-06-25.
//

#ifndef MY_APPLICATION_IVANK_H
#define MY_APPLICATION_IVANK_H

#include "vm.h"

class M4 {
public:
    static void identity(float *vals) {
        memset(vals, 0, sizeof(vals));
        vals[0] = vals[5] = vals[10] = vals[15] = 1.0;
    }

    static float *multiply(float *a, float *b, float *out) {
        float a00 = a[0], a01 = a[1], a02 = a[2], a03 = a[3],
                a10 = a[4], a11 = a[5], a12 = a[6], a13 = a[7],
                a20 = a[8], a21 = a[9], a22 = a[10], a23 = a[11],
                a30 = a[12], a31 = a[13], a32 = a[14], a33 = a[15];

        // Cache only the current line of the second matrix
        float b0  = b[0], b1 = b[1], b2 = b[2], b3 = b[3];
        out[0] = b0*a00 + b1*a10 + b2*a20 + b3*a30;
        out[1] = b0*a01 + b1*a11 + b2*a21 + b3*a31;
        out[2] = b0*a02 + b1*a12 + b2*a22 + b3*a32;
        out[3] = b0*a03 + b1*a13 + b2*a23 + b3*a33;

        b0 = b[4]; b1 = b[5]; b2 = b[6]; b3 = b[7];
        out[4] = b0*a00 + b1*a10 + b2*a20 + b3*a30;
        out[5] = b0*a01 + b1*a11 + b2*a21 + b3*a31;
        out[6] = b0*a02 + b1*a12 + b2*a22 + b3*a32;
        out[7] = b0*a03 + b1*a13 + b2*a23 + b3*a33;

        b0 = b[8]; b1 = b[9]; b2 = b[10]; b3 = b[11];
        out[8] = b0*a00 + b1*a10 + b2*a20 + b3*a30;
        out[9] = b0*a01 + b1*a11 + b2*a21 + b3*a31;
        out[10] = b0*a02 + b1*a12 + b2*a22 + b3*a32;
        out[11] = b0*a03 + b1*a13 + b2*a23 + b3*a33;

        b0 = b[12]; b1 = b[13]; b2 = b[14]; b3 = b[15];
        out[12] = b0*a00 + b1*a10 + b2*a20 + b3*a30;
        out[13] = b0*a01 + b1*a11 + b2*a21 + b3*a31;
        out[14] = b0*a02 + b1*a12 + b2*a22 + b3*a32;
        out[15] = b0*a03 + b1*a13 + b2*a23 + b3*a33;
        return out;
    }

};


class Transform {
public:
    friend class DisplayObject;
    int _mdirty, _vdirty;
    float tmat[16], imat[16];
    DisplayObject *object;

    Transform() : _mdirty(0), _vdirty(0) {
        M4::identity(&tmat[0]);
        M4::identity(&imat[0]);
    }
};

class Rectangle {
public:
    float x,y,width,height;
    Rectangle(float x=0, float y=0, float w=0, float h=0):x(x),y(y),width(w),height(h) {}
};

class DisplayObject {
public:
    float x,y,z,_x,_y,_z;
    float sx,sy,sz,_sx,_sy,_sz;
    Transform transform;
    DisplayObject() {
        x=y=z=_x=_y=_z=0;
        sx=sy=sz=1;
        _sx=_sy=_sz=0;
        transform.object = this;
    }
};

typedef struct Color {
    unsigned char r,g,b,a;
};
class BitmapData {
public:
    Color *pixels;
    int width, height, dirty;
    BitmapData(int w, int h) : width(w), height(h) {
        pixels = new Color[w*h];
    }
    void setPixel32(int x, int y, unsigned int color) {
        if(x < 0 || y < 0 || x >= width || y >= height) return;
        unsigned char r = (color >> 24)&0xff;
        unsigned char g = (color >> 24)&0xff;
        unsigned char b = (color >> 24)&0xff;
        unsigned char a = (color >> 24)&0xff;
        float af = a / 255f;
        Color *c = &pixels[y * width + x];
        c->r = r * af;
        c->g = r * af;
        c->b = r * af;
        c->a = a;
        dirty = 1;
    }
};
#endif //MY_APPLICATION_IVANK_H
