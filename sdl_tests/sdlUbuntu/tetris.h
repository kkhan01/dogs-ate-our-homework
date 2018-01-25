#ifndef TETRIS_H
#define TETRIS_H

typedef unsigned char boolean; // Boolean

unsigned int tetronimos[7][4];

struct tet_block {
    int x; // x-coordinate
    int y; // y-coordinate
    int type; // I/L/T/O/J/Z/S
    int rotation; // Rotation state
};

struct tet_block cur_piece;

void move_tet(int); // Moves block if possible. 0-left; 1-right; 2-down
void rotate_tet(int); // Rotates block if possible. 0-left; 1-right
void set_tet_inplace(); // Sets the block in place (Reaches bottom)
boolean is_tet_legal(); // Checks if the block is overlapping anything. True if not overlapping.

#endif