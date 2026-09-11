#ifndef TEXTURE_H
#define TEXTURE_H

#include "util.h"

typedef struct {
    char ch;
    U8 value;
} Letter;

typedef struct {
    U8 count;
    U8 jitter;
    Letter *letters;
} Texture;

extern Texture textures[20];

#endif
