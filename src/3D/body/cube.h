#ifndef CUBE_H
#define CUBE_H

Triangle *create_cube_body(Triangle *tri, double x, double y, double z, double s);

#define CUBE_BODY(y, x, z, s) (create_cube_body((Triangle[12]){}, x, y, z, s))

#endif