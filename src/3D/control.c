#include <ncurses.h>
#include <math.h>

#include "3D/camera.h"

#define drift 0.82

bool control_cam(Camera *cam) {
    switch (getch()) {
        case 'q': return false; break;
        case KEY_UP:
            cam->vel.pos.x += cam->pos.dir.x;
            cam->vel.pos.y += cam->pos.dir.y;
            cam->vel.pos.z += cam->pos.dir.z;
            break;
        case KEY_DOWN:
            cam->vel.pos.x -= cam->pos.dir.x;
            cam->vel.pos.y -= cam->pos.dir.y;
            cam->vel.pos.z -= cam->pos.dir.z;
            break;
        case KEY_RIGHT:
            cam->vel.pos.x -= cam->pos.dir.z;
            cam->vel.pos.z += cam->pos.dir.x;
            break;
        case KEY_LEFT:
            cam->vel.pos.x += cam->pos.dir.z;
            cam->vel.pos.z -= cam->pos.dir.x;
            break;
        case 'w': cam->vel.pos.y--; break;
        case 's': cam->vel.pos.y++; break;
        case 'a': cam->vel.yaw -= 0.05; break;
        case 'd': cam->vel.yaw += 0.05; break;
    }
    {
        cam->pos.pos.x += cam->vel.pos.x;
        cam->pos.pos.y += cam->vel.pos.y;
        cam->pos.pos.z += cam->vel.pos.z;
        {
            double dx = cam->pos.dir.x;
            double dz = cam->pos.dir.z;
            double a = cam->vel.yaw;
            cam->pos.dir.x = dx * cos(a) - dz * sin(a);
            cam->pos.dir.z = dx * sin(a) + dz * cos(a);
        }
    }
    {
        cam->vel.pos.x *= drift;
        cam->vel.pos.y *= drift;
        cam->vel.pos.z *= drift;
        cam->vel.yaw *= drift;
    }
    return true;
}