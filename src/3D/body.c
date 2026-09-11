#include "3D/engine.h"
#include "graphics/color.h"
#include "3D/body.h"

TriangleStack finish_tri_body(
    pCorner p1, pCorner p2, pCorner p3,
    U8 color, U8 texture
) {
    TriangleStack result;
    result.count = 1;
    result.list = malloc(result.count * sizeof(Triangle));
    result.list[0] = (Triangle){p1, p2, p3, color, texture};
    return result;
}

TriangleStack finish_quad_body(
    pCorner p1, pCorner p2, pCorner p3, pCorner p4,
    U8 color, U8 texture
) {
    TriangleStack result;
    result.count = 2;
    result.list = malloc(result.count * sizeof(Triangle));
    result.list[0] = (Triangle){p1, p2, p3, color, texture};
    result.list[1] = (Triangle){p4, p2, p3, color, texture};
    return result;
}

TriangleStack quad_body(World *world, P p1, P p2, P p3, P p4, U8 color, U8 texture) {
    pCorner pc = corner_malloc(world, 4);
    P *c = world->corners.list;
    c[pc + 0] = p1; c[pc + 1] = p2; c[pc + 2] = p3; c[pc + 3] = p4;
    return finish_quad_body(pc + 0, pc + 1, pc + 2, pc + 3, color, texture);
}

TriangleStack cube_body(World *world, P p, double s) {
    pCorner pc = corner_malloc(world, 8);
    
    P *c = world->corners.list;
    
    enum {aaa, baa, bba, bbb, aba, abb, aab, bab};

    c[pc + aaa] = (P){p.x, p.y, p.z};
    c[pc + baa] = (P){p.x + s, p.y, p.z};
    c[pc + bba] = (P){p.x + s, p.y + s, p.z};
    c[pc + bbb] = (P){p.x + s, p.y + s, p.z + s};
    c[pc + aba] = (P){p.x, p.y + s, p.z};
    c[pc + abb] = (P){p.x, p.y + s, p.z + s};
    c[pc + aab] = (P){p.x, p.y, p.z + s};
    c[pc + bab] = (P){p.x + s, p.y, p.z + s};
    
    TriangleStack r = {.list = malloc(0)};

    r = merge_bodies(r, finish_quad_body(pc + aaa, pc + aba, pc + baa, pc + bba, BLUE, 0));
    r = merge_bodies(r, finish_quad_body(pc + aab, pc + abb, pc + bab, pc + bbb, YELLOW, 0));
    r = merge_bodies(r, finish_quad_body(pc + aab, pc + abb, pc + aaa, pc + aba, RED, 0));
    r = merge_bodies(r, finish_quad_body(pc + bab, pc + bbb, pc + baa, pc + bba, GREEN, 0));
    r = merge_bodies(r, finish_quad_body(pc + aaa, pc + baa, pc + aab, pc + bab, WHITE, 0));
    r = merge_bodies(r, finish_quad_body(pc + aba, pc + bba, pc + abb, pc + bbb, WHITE, 0));

    return r;
}
