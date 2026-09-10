#ifndef ASCII_H
#define ASCII_H

#include "3D/camera.h"

#define FPS 60

void init_ascii(void);
void draw_ascii(const Photo *, Camera *);
void close_ascii(void);

U32 ascii_w();
U32 ascii_h();

#endif
