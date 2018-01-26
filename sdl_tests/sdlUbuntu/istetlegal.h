#ifndef ISTETLEGAL_H
#define ISTETLEGAL_H

typedef unsigned char boolean; // Boolean

struct tet_block {
    int x; // x-coordinate
    int y; // y-coordinate
    int type; // I/L/T/O/J/Z/S
    int rotation; // Rotation state
};

extern unsigned int tet_location(int, int);

extern boolean is_tet_legal(struct tet_block);

#endif