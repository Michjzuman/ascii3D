#include <math.h>
#include <float.h>
#define PI 3.14159265358979323846
#define EPSILON 0.000001

#include "types.h"

#include "3D.h"

World init_world() {
    World world;
    world.triangle_count = 0;
    world.triangles = malloc(0);
    return world;
}

void add_body(World *world, const Triangle *triangles, const U32 triangle_count) {
    world->triangles = realloc(
        world->triangles,
        (world->triangle_count + triangle_count) * sizeof(Triangle)
    );
    for (U32 i = 0; i < triangle_count; i++) {
        world->triangles[world->triangle_count + i] = triangles[i];
    }
    world->triangle_count += triangle_count;
}

static double get_distance(const Camera *cam, const Triangle *tri, double dx, double dy) {
    P dir;
    dir.x = cosf(dy) * cosf(dx);
    dir.y = sinf(dy);
    dir.z = cosf(dy) * sinf(dx);

    P kat1;
    kat1.x = tri->B.x - tri->A.x;
    kat1.y = tri->B.y - tri->A.y;
    kat1.z = tri->B.z - tri->A.z;
    P kat2;
    kat2.x = tri->C.x - tri->A.x;
    kat2.y = tri->C.y - tri->A.y;
    kat2.z = tri->C.z - tri->A.z;
    P hyp;
    hyp.x = dir.y * kat2.z - dir.z * kat2.y;
    hyp.y = dir.z * kat2.x - dir.x * kat2.z;
    hyp.z = dir.x * kat2.y - dir.y * kat2.x;
    
    double det = kat1.x * hyp.x + kat1.y * hyp.y + kat1.z * hyp.z;
    if (fabs(det) < EPSILON) return  -1.0;

    double f = 1.0f / det;

    P s;
    s.x = cam->x - tri->A.x;
    s.y = cam->y - tri->A.y;
    s.z = cam->z - tri->A.z;

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
    double yaw = atan2(cam->dz, cam->dx);
    double pitch = atan2(cam->dy, hypot(cam->dx, cam->dz));
    for (U32 x = 0; x < photo->w; x++) {
        for (U32 y = 0; y < photo->h; y++) {
            double next_dis = DBL_MAX;
            U8 color;
            for (U32 i = 0; i < world->triangle_count; i++) {
                Triangle *tri = &world->triangles[i];
                double sx = ((double)x + 0.5) - (double)photo->w / 2.0;
                double sy = ((double)y + 0.5) - (double)photo->h / 2.0;
                double dx = yaw + atan(sx / photo->fov);
                double dy = pitch + atan(sy / photo->fov);
                double dis = get_distance(cam, tri, dx, dy);
                if (dis >= 0 && dis < next_dis) {
                    next_dis = dis;
                    color = tri->color;
                }
            }
            U8 value = (U8)next_dis;
            if (next_dis < 0) value = 0;
            if (next_dis > 255.0) value = 255;
            photo->pic[y][x].value = value;
            photo->pic[y][x].color = color;
        }
    }
}


