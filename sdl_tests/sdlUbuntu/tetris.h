#ifndef TETRIS_H
#define TETRIS_H

unsigned int tetronimos[7][4];

struct tet_block {
    int x; // x-coordinate
    int y; // y-coordinate
    int type; // I/L/T/O/J/Z/S
    int rotation; // Rotation state
};

#endif