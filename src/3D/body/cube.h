#ifndef CUBE_H
#define CUBE_H

Triangle *create_cube_body(World *, Triangle *tri, double x, double y, double z, double s);

#define CUBE_BODY(x, y, z, s) (create_cube_body(&world, (Triangle[12]){}, x, y, z, s))

#endif
