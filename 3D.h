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

typedef struct {
    Triangle *triangles;
    U32 triangle_count;
} World;

typedef struct {
    double x, y, z, dx, dy, dz;
} CameraPosition;

typedef struct {
    double x, y, z, xz;
} CameraVelocity;

typedef struct {
    CameraPosition pos;
    CameraVelocity vel;
} Camera;

Camera init_cam(void);

World init_world(void);

void add_body(World *, const Triangle *triangles, const U32 triangle_count);

void take_photo(Photo *, const Camera *, const World *);

#endif