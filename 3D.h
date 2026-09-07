#ifndef _3D_H
#define _3D_H

#include "photo.h"
#include "colors.h"

typedef struct {
    double x, y, z;
} P;

typedef struct {
    P A, B, C;
    U8 color;
} Triangle;

#define CUBE_BODY(x, y, z, s) (Triangle[]){ \
    {(P){x, y, z}, (P){x, y + s, z}, (P){x + s, y, z}, RED}, \
    {(P){x + s, y + s, z}, (P){x, y + s, z}, (P){x + s, y, z}, GREEN}, \
    {(P){x, y, z + s}, (P){x, y + s, z + s}, (P){x + s, y, z + s}, BLUE}, \
    {(P){x + s, y + s, z + s}, (P){x, y + s, z + s}, (P){x + s, y, z + s}, YELLOW}, \
    {(P){x, y, z}, (P){x, y, z + s}, (P){x, y + s, z + s}, WHITE}, \
    {(P){x, y, z}, (P){x, y + s, z}, (P){x, y + s, z + s}, RED}, \
    {(P){x + s, y, z}, (P){x + s, y, z + s}, (P){x + s, y + s, z + s}, GREEN}, \
    {(P){x + s, y, z}, (P){x + s, y + s, z}, (P){x + s, y + s, z + s}, BLUE}, \
    {(P){x, y, z}, (P){x + s, y, z}, (P){x, y, z + s}, YELLOW}, \
    {(P){x + s, y, z + s}, (P){x + s, y, z}, (P){x, y, z + s}, WHITE}, \
    {(P){x, y + s, z}, (P){x + s, y + s, z}, (P){x, y + s, z + s}, RED}, \
    {(P){x + s, y + s, z + s}, (P){x + s, y + s, z}, (P){x, y + s, z + s}, GREEN}, \
}

typedef struct {
    Triangle *triangles;
    U32 triangle_count;
} World;

typedef struct {
    double x, y, z;
    double dx, dy, dz;
} Camera;

World init_world(void);

void add_body(World *, const Triangle *triangles, const U32 triangle_count);

void take_photo(Photo *, const Camera *, const World *);

#endif