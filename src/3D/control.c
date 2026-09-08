#include <ncurses.h>
#include <math.h>

#include "3D/camera.h"

#define drift 0.82

bool control_cam(Camera *cam) {
    switch (getch()) {
        case 'q': return false; break;
        case KEY_UP:
            cam->vel.x += cam->pos.dx;
            cam->vel.y += cam->pos.dy;
            cam->vel.z += cam->pos.dz;
            break;
        case KEY_DOWN:
            cam->vel.x -= cam->pos.dx;
            cam->vel.y -= cam->pos.dy;
            cam->vel.z -= cam->pos.dz;
            break;
        case KEY_RIGHT:
            cam->vel.x -= cam->pos.dz;
            cam->vel.z += cam->pos.dx;
            break;
        case KEY_LEFT:
            cam->vel.x += cam->pos.dz;
            cam->vel.z -= cam->pos.dx;
            break;
        case 'w': cam->vel.y--; break;
        case 's': cam->vel.y++; break;
        case 'a': cam->vel.yaw -= 0.05; break;
        case 'd': cam->vel.yaw += 0.05; break;
        /*
        case 'a': cam->dz -= 0.5f; break;
        case 'd': cam->dz += 0.5f; break;
        */
    }
    {
        cam->pos.x += cam->vel.x;
        cam->pos.y += cam->vel.y;
        cam->pos.z += cam->vel.z;
        {
            double dx = cam->pos.dx;
            double dz = cam->pos.dz;
            double a = cam->vel.yaw;
            cam->pos.dx = dx * cos(a) - dz * sin(a);
            cam->pos.dz = dx * sin(a) + dz * cos(a);
        }
    }
    {
        cam->vel.x *= drift;
        cam->vel.y *= drift;
        cam->vel.z *= drift;
        cam->vel.yaw *= drift;
    }
    return true;
}