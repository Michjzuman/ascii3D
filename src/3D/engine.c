#include "util.h"

#include "3D/engine.h"

World init_world() {
    World world;
    world.triangles.count = 0;
    world.triangles.list = malloc(0);
    world.corners.count = 0;
    world.corners.list = malloc(0);
    return world;
}

void free_world(World *world) {
    free(world->triangles.list);
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

TriangleStack merge_bodies(TriangleStack a, TriangleStack b) {
    TriangleStack result;
    result.count = a.count + b.count;
    result.list = realloc(
        a.list, result.count * sizeof(Triangle)
    );
    for (U32 i = 0; i < b.count; i++) {
        result.list[a.count + i] = b.list[i];
    }
    free(b.list);
    return result;
}
