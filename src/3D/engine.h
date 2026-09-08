#ifndef _3D_H
#define _3D_H

#include "util.h"

typedef struct {
    double x, y, z;
} P;

typedef struct {
    P A, B, C;
    U8 color, palette;
} Triangle;

typedef struct {
    Triangle *triangles;
    U32 triangle_count;
} World;

World init_world(void);

void add_body(World *, const Triangle *triangles, const U32 triangle_count);

#endif