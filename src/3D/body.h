#ifndef BODY_H
#define BODY_H


TriangleStack finish_tri_body(pCorner, pCorner, pCorner, U8 color, U8 texture);
TriangleStack finish_quad_body(pCorner, pCorner, pCorner, pCorner, U8 color, U8 texture);


TriangleStack quad_body(World *world, P p1, P p2, P p3, P p4, U8 color, U8 texture);
TriangleStack cube_body(World *, P p, double s);


TriangleStack merge_bodies(TriangleStack a, TriangleStack b);

#define add_body(w, b) w.triangles = merge_bodies(w.triangles, b)


#endif
