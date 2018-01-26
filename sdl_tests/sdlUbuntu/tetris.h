#ifndef TETRIS_H
#define TETRIS_H

#include <stdio.h>
#include <stdlib.h>

typedef unsigned char boolean; // Boolean

unsigned int tetronimos[7][4];

struct tet_block {
    int x; // x-coordinate
    int y; // y-coordinate
    int type; // I/L/T/O/J/Z/S
    int rotation; // Rotation state
};

struct tet_block cur_piece;

unsigned int tet_location(int, int);

void set_tet_inplace(); // Sets the block in place (Reaches bottom)
boolean is_tet_legal(struct tet_block); // Checks if the block is overlapping anything. True if not overlapping.
boolean tet_wall_kick(struct tet_block *); // Moves the block around if it tries to rotate into an obstacle

#endif