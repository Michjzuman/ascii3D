#include "3D/engine.h"
#include "graphics/colors.h"

Triangle *create_cube_body(Triangle *tri, double x, double y, double z, double s) {
    P *c = malloc(8 * sizeof(P));

    enum {aaa, baa, bba, bbb, aba, abb, aab, bab};

    c[aaa] = (P){x, y, z};
    c[baa] = (P){x + s, y, z};
    c[bba] = (P){x + s, y + s, z};
    c[bbb] = (P){x + s, y + s, z + s};
    c[aba] = (P){x, y + s, z};
    c[abb] = (P){x, y + s, z + s};
    c[aab] = (P){x, y, z + s};
    c[bab] = (P){x + s, y, z + s};

    tri[0] = (Triangle){&c[aaa], &c[aba], &c[baa], BLUE};
    tri[1] = (Triangle){&c[bba], &c[aba], &c[baa], GREEN};
    tri[2] = (Triangle){&c[aab], &c[abb], &c[bab], BLUE};
    tri[3] = (Triangle){&c[bbb], &c[abb], &c[bab], YELLOW};
    tri[4] = (Triangle){&c[aaa], &c[aab], &c[abb], WHITE};
    tri[5] = (Triangle){&c[aaa], &c[aba], &c[abb], RED};
    tri[6] = (Triangle){&c[baa], &c[bab], &c[bbb], GREEN};
    tri[7] = (Triangle){&c[baa], &c[bba], &c[bbb], BLUE};
    tri[8] = (Triangle){&c[aaa], &c[baa], &c[aab], YELLOW};
    tri[9] = (Triangle){&c[bab], &c[baa], &c[aab], WHITE};
    tri[10] = (Triangle){&c[aba], &c[bba], &c[abb], YELLOW};
    tri[11] = (Triangle){&c[bbb], &c[bba], &c[abb], GREEN};

    return tri;
}