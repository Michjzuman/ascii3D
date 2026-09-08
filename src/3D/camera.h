#ifndef CAMERA_H
#define CAMERA_H

#include "util.h"

#include "graphics/photo.h"
#include "3D/engine.h"

typedef struct {
    double x, y, z, dx, dy, dz, fov;
} CameraPosition;

typedef struct {
    double x, y, z, yaw;
} CameraVelocity;

typedef struct {
    CameraPosition pos;
    CameraVelocity vel;
} Camera;

Camera init_cam(void);

void take_photo(Photo *, const Camera *, const World *);

#endif