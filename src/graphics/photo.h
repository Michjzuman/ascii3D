#ifndef PHOTO_H
#define PHOTO_H

#include "util.h"

typedef struct {
    U8 value;
    U8 color;
} Pixel;

typedef struct {
    U32 w, h;
    Pixel **pic;
} Photo;

Photo init_photo(U32 w, U32 h);
void free_photo(Photo *);

#endif