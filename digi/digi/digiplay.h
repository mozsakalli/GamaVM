//
//  digiplay.h
//  digi
//
//  Created by mustafa on 9.06.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#ifndef digiplay_h
#define digiplay_h

typedef struct __attribute__ ((packed)) VEC2 {
    float x,y;
} VEC2;
typedef struct __attribute__ ((packed)) VEC3 {
    float x,y,z;
} VEC3;
typedef struct __attribute__ ((packed)) COLOR {
    unsigned char r,g,b,a;
} COLOR;
typedef struct __attribute__ ((packed)) VERT2D {
    VEC3 pos;
    COLOR color;
    VEC2 uv;
} VERT2D;

typedef struct Mat2D {
    int meshVersion;
    float m00;
    float m10;
    float m01;
    float m11;
    float m02;
    float m12;
} MAT2D;

typedef struct Mat3D {
    
} MAT3D;

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

#endif /* digiplay_h */
