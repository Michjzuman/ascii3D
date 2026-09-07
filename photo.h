#ifndef PHOTO_H
#define PHOTO_H

#include "types.h"

typedef struct {
    U8 value;
    U8 color;
} Pixel;

typedef struct {
    U32 w, h;
    Pixel **pic;
    float fov;
} Photo;

Photo init_photo(double fov);

#endif