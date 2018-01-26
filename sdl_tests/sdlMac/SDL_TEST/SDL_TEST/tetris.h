#ifndef TETRIS_H
#define TETRIS_H

#include <stdio.h>
#include <stdlib.h>
#include "istetlegal.h"

extern unsigned int tetronimos[7][4];

unsigned int tet_location(int, int);

void set_tet_inplace(); // Sets the block in place (Reaches bottom)
boolean tet_wall_kick(struct tet_block *); // Moves the block around if it tries to rotate into an obstacle
extern boolean is_tet_legal(struct tet_block);
#endif
