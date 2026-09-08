#include "util.h"

#include "3D/engine.h"

World init_world() {
    World world;
    world.triangle_count = 0;
    world.triangles = malloc(0);
    return world;
}

void free_world(World *world) {
    for (U32 i = 0; i < world->triangle_count; i++) {
        P *corners[] = {
            world->triangles[i].A, world->triangles[i].B, world->triangles[i].C
        };
        for (U32 c = 0; c < 3; c++) {
            // todo
        }
    }
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
