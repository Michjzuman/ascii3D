#include <math.h>
#include <float.h>
#define PI 3.14159265358979323846
#define EPSILON 0.000001

#include "graphics/ascii.h"
#include "3D/camera.h"

Camera init_cam() {
    Camera cam;
    cam.vel.x = 0.0f;
    cam.vel.y = 0.0f;
    cam.vel.z = 0.0f;
    cam.vel.yaw = 0.0f;
    return cam;
}

static double get_distance(const Camera *cam, const World *world, const Triangle *tri, double dx, double dy) {
    P dir;
    dir.x = cosf(dy) * cosf(dx);
    dir.y = sinf(dy);
    dir.z = cosf(dy) * sinf(dx);

    P *c = world->corners.list;

    P kat1;
    kat1.x = c[tri->B].x - c[tri->A].x;
    kat1.y = c[tri->B].y - c[tri->A].y;
    kat1.z = c[tri->B].z - c[tri->A].z;
    P kat2;
    kat2.x = c[tri->C].x - c[tri->A].x;
    kat2.y = c[tri->C].y - c[tri->A].y;
    kat2.z = c[tri->C].z - c[tri->A].z;
    P hyp;
    hyp.x = dir.y * kat2.z - dir.z * kat2.y;
    hyp.y = dir.z * kat2.x - dir.x * kat2.z;
    hyp.z = dir.x * kat2.y - dir.y * kat2.x;
    
    double det = kat1.x * hyp.x + kat1.y * hyp.y + kat1.z * hyp.z;
    if (fabs(det) < EPSILON) return  -1.0;

    double f = 1.0f / det;

    P s;
    s.x = cam->pos.x - c[tri->A].x;
    s.y = cam->pos.y - c[tri->A].y;
    s.z = cam->pos.z - c[tri->A].z;

    double u = f * (s.x * hyp.x + s.y * hyp.y + s.z * hyp.z);
    if (u < 0.0f || u > 1.0f) return  -1.0;

    P q;
    q.x = s.y * kat1.z - s.z * kat1.y;
    q.y = s.z * kat1.x - s.x * kat1.z;
    q.z = s.x * kat1.y - s.y * kat1.x;

    double v = f * (dir.x * q.x + dir.y * q.y + dir.z * q.z);
    if (v < 0.0f || u + v > 1.0f) return  -1.0;

    double t = f * (kat2.x * q.x + kat2.y * q.y + kat2.z * q.z);
    if (t > EPSILON) return t;
    
    return -1.0;
}

void take_photo(Photo *photo, const Camera *cam, const World *world) {
    double yaw = atan2(cam->pos.dz, cam->pos.dx);
    double pitch = atan2(cam->pos.dy, hypot(cam->pos.dx, cam->pos.dz));
    for (U32 x = 0; x < photo->w; x++) {
        for (U32 y = 0; y < photo->h; y++) {
            double next_dis = DBL_MAX;
            U8 color = 1;
            U8 texture = 0;
            for (U32 i = 0; i < world->triangles.count; i++) {
                Triangle *tri = &world->triangles.list[i];
                double sx = ((double)x + 0.5) - (double)photo->w / 2.0;
                double sy = (((double)y + 0.5) - (double)photo->h / 2.0) * 2.0;
                double dx = yaw + atan(sx / cam->pos.fov);
                double dy = pitch + atan(sy / cam->pos.fov);
                double dis = get_distance(cam, world, tri, dx, dy);
                if (dis >= 0 && dis < next_dis) {
                    next_dis = dis;
                    color = tri->color;
                    texture = tri->texture;
                }
            }
            U8 value = (U8)next_dis;
            Pixel *pixel = &photo->pic[y][x];
            if (next_dis < 0) {
                pixel->value = 0;
                pixel->color = 0;
                pixel->texture = 0;
            } else if (next_dis >= 255.0) {
                pixel->value = 255;
                pixel->color = 4;
                pixel->texture = 0;
            } else {
                pixel->value = value;
                pixel->color = color;
                pixel->texture = texture;
            }
        }
    }
}
