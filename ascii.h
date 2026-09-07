#ifndef ASCII_H
#define ASCII_H

#include "photo.h"

#define abs(a) ((a) < 0 ? -(a) : (a))

typedef struct {char ch; U8 value;} Letter;

void init(void);
void draw(const Photo *);
void close(void);

U32 get_term_w();
U32 get_term_h();

#endif