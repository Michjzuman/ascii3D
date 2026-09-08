#include "graphics/photo.h"

Photo init_photo(U32 w, U32 h) {
    Photo photo;
    photo.w = w;
    photo.h = h;
    photo.pic = malloc(photo.h * sizeof(U8 *));
    for (U32 y = 0; y < photo.h; y++) {
        photo.pic[y] = malloc(photo.w * sizeof(Pixel));
    }
    return photo;
}

void free_photo(Photo *photo) {
    for (U32 y = 0; y < photo->h; y++) {
        free(photo->pic[y]);
    }
    free(photo->pic);
}