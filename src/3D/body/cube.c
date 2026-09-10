#include "3D/engine.h"
#include "graphics/colors.h"

Triangle *create_cube_body(World *world, Triangle *tri, double x, double y, double z, double s) {
    pCorner pc = corner_malloc(world, 8);

    P *c = world->corners.list;
    
    enum {aaa, baa, bba, bbb, aba, abb, aab, bab};

    c[pc + aaa] = (P){x, y, z};
    c[pc + baa] = (P){x + s, y, z};
    c[pc + bba] = (P){x + s, y + s, z};
    c[pc + bbb] = (P){x + s, y + s, z + s};
    c[pc + aba] = (P){x, y + s, z};
    c[pc + abb] = (P){x, y + s, z + s};
    c[pc + aab] = (P){x, y, z + s};
    c[pc + bab] = (P){x + s, y, z + s};

    tri[0] = (Triangle){pc + aaa, pc + aba, pc + baa, BLUE};
    tri[1] = (Triangle){pc + bba, pc + aba, pc + baa, GREEN, 2};
    tri[2] = (Triangle){pc + aab, pc + abb, pc + bab, BLUE};
    tri[3] = (Triangle){pc + bbb, pc + abb, pc + bab, YELLOW};
    tri[4] = (Triangle){pc + aaa, pc + aab, pc + abb, WHITE, 1};
    tri[5] = (Triangle){pc + aaa, pc + aba, pc + abb, RED};
    tri[6] = (Triangle){pc + baa, pc + bab, pc + bbb, GREEN};
    tri[7] = (Triangle){pc + baa, pc + bba, pc + bbb, BLUE};
    tri[8] = (Triangle){pc + aaa, pc + baa, pc + aab, YELLOW};
    tri[9] = (Triangle){pc + bab, pc + baa, pc + aab, WHITE};
    tri[10] = (Triangle){pc + aba, pc + bba, pc + abb, YELLOW};
    tri[11] = (Triangle){pc + bbb, pc + bba, pc + abb, GREEN};

    return tri;
}
