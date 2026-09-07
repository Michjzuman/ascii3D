#include <ncurses.h>
#include <math.h>

#include "3D.h"

bool control_cam(Camera *cam) {
    switch (getch()) {
        case 'q': return false; break;
        case 'w': cam->y++; break;
        case 's': cam->y--; break;
        case 'e': cam->x += 0.1f; break;
        case 'd': cam->x -= 0.1f; break;
        case 'r': cam->z += 0.1f; break;
        case 'f': cam->z -= 0.1f; break;
    }
    return true;
}