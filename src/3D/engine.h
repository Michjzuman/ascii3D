#ifndef _3D_H
#define _3D_H

#include "util.h"

typedef struct {
    double x, y, z;
} P;

typedef U32 pCorner;

typedef struct {
    P *list;
    pCorner count;
} CornerStack;

typedef struct {
    pCorner A, B, C;
    U8 color, texture;
} Triangle;

typedef struct {
    Triangle *list;
    U64 count;
} TriangleStack;

typedef struct {
    TriangleStack triangles;
    CornerStack corners;
} World;

World init_world();
void free_world(World *);

pCorner corner_malloc(World *, pCorner count);

#endif
