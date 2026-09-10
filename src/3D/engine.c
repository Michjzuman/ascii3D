#include "util.h"

#include "3D/engine.h"

World init_world() {
    World world;
    world.triangle_count = 0;
    world.triangles = malloc(0);
    world.corners.list = malloc(0);
    world.corners.count = 0;
    return world;
}

void free_world(World *world) {
    free(world->triangles);
    free(world->corners.list);
}

pCorner corner_malloc(World *world, pCorner count) {
    pCorner result = world->corners.count;
    world->corners.count += count;
    world->corners.list = realloc(
        world->corners.list, world->corners.count * sizeof(P)
    );
    return result;
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
