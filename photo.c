#include "ascii.h"
#include "photo.h"

Photo init_photo(double fov) {
    Photo photo;
    photo.fov = fov;
    photo.w = get_term_w();
    photo.h = get_term_h();
    photo.pic = malloc(photo.h * sizeof(U8 *));
    for (U32 y = 0; y < photo.h; y++) {
        photo.pic[y] = malloc(photo.w * sizeof(Pixel));
    }
    return photo;
}