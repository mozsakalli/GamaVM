//
// Created by Mustafa Ozsakalli on 25.06.2020.
//
#include "vm.h"

typedef struct VEC2 {
    float x,y;
} VEC2;
typedef struct VEC3 {
    float x,y,z;
} VEC3;
typedef struct COLOR {
    unsigned char r,g,b,a;
} COLOR;

#define MESH_QUAD       0
#define MESH_TRIANGLES  1

typedef struct Mesh {
    int type;
    int capacity;
    int size;
    int version;    // sync with world matrix when batching
    VEC3 *pos;
    VEC3 *calculatedPos;
    VEC2 *uv;
    COLOR *color;
    struct Mesh *next;  // cache
} Mesh;

static Mesh *MESH_CACHE = NULL;

void Java_digiplay_Mesh_create(VM *vm, Object *method, VAR *args) {
    int capacity = args[0].I;
    Mesh *result = MESH_CACHE;
    if(result) {
        if(result->capacity < capacity) {
            result->pos = realloc(result->pos, sizeof(VEC3) * capacity);
        }

    }
}