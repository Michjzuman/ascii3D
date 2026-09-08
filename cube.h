#include "3D.h"

#define CUBE_BODY(x, y, z, s) (Triangle[]){ \
    {(P){x, y, z}, (P){x, y + s, z}, (P){x + s, y, z}, BLUE}, \
    {(P){x + s, y + s, z}, (P){x, y + s, z}, (P){x + s, y, z}, GREEN}, \
    {(P){x, y, z + s}, (P){x, y + s, z + s}, (P){x + s, y, z + s}, BLUE}, \
    {(P){x + s, y + s, z + s}, (P){x, y + s, z + s}, (P){x + s, y, z + s}, YELLOW}, \
    {(P){x, y, z}, (P){x, y, z + s}, (P){x, y + s, z + s}, WHITE}, \
    {(P){x, y, z}, (P){x, y + s, z}, (P){x, y + s, z + s}, RED}, \
    {(P){x + s, y, z}, (P){x + s, y, z + s}, (P){x + s, y + s, z + s}, GREEN}, \
    {(P){x + s, y, z}, (P){x + s, y + s, z}, (P){x + s, y + s, z + s}, BLUE}, \
    {(P){x, y, z}, (P){x + s, y, z}, (P){x, y, z + s}, YELLOW}, \
    {(P){x + s, y, z + s}, (P){x + s, y, z}, (P){x, y, z + s}, WHITE}, \
    {(P){x, y + s, z}, (P){x + s, y + s, z}, (P){x, y + s, z + s}, YELLOW}, \
    {(P){x + s, y + s, z + s}, (P){x + s, y + s, z}, (P){x, y + s, z + s}, GREEN}, \
}

#define CUBE2_BODY(x, y, z, s) (Triangle[]){ \
    {(P){x + s, y + s, z}, (P){x, y + s, z}, (P){x + s, y, z}, GREEN}, \
    {(P){x, y, z + s}, (P){x, y + s, z + s}, (P){x + s, y, z + s}, BLUE}, \
    {(P){x + s, y + s, z + s}, (P){x, y + s, z + s}, (P){x + s, y, z + s}, YELLOW}, \
    {(P){x, y, z}, (P){x, y, z + s}, (P){x, y + s, z + s}, WHITE}, \
    {(P){x, y, z}, (P){x, y + s, z}, (P){x, y + s, z + s}, RED}, \
    {(P){x + s, y, z}, (P){x + s, y, z + s}, (P){x + s, y + s, z + s}, GREEN}, \
    {(P){x + s, y, z}, (P){x + s, y + s, z}, (P){x + s, y + s, z + s}, BLUE}, \
    {(P){x, y, z}, (P){x + s, y, z}, (P){x, y, z + s}, YELLOW}, \
    {(P){x + s, y, z + s}, (P){x + s, y, z}, (P){x, y, z + s}, WHITE}, \
    {(P){x, y + s, z}, (P){x + s, y + s, z}, (P){x, y + s, z + s}, YELLOW}, \
    {(P){x + s, y + s, z + s}, (P){x + s, y + s, z}, (P){x, y + s, z + s}, GREEN}, \
}


