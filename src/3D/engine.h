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
    Triangle *triangles;
    U32 triangle_count;
    CornerStack corners;
} World;

World init_world(void);
void free_world(World *);

void add_body(World *, const Triangle *triangles, const U32 triangle_count);

pCorner corner_malloc(World *, pCorner count);

#endif
