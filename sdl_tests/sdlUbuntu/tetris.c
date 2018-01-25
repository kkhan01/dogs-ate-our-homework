#include "tetris.h"

tetronimos = {
    {0b0100010001000100, 0b0000111100000000, 0b0010001000100010, 0b0000000011110000}, // I
    {0b0110010001000000, 0b0000111000100000, 0b0100010011000000, 0b1000111000000000}, // L
    {0b0100111000000000, 0b0100011001000000, 0b0000111001000000, 0b0100110001000000}, // T
    {0b0000011001100000, 0b0000011001100000, 0b0000011001100000, 0b0000011001100000}, // O
    {0b0100010001100000, 0b0000111010000000, 0b1100010001000000, 0b0010111000000000}, // J
    {0b1100011000000000, 0b0010011001000000, 0b0000110001100000, 0b0100110010000000}, // Z
    {0b0110110000000000, 0b0100011000100000, 0b0000011011000000, 0b1000110001000000}  // S    
};

// Returns absolute position of the block
unsigned int tet_location(int x, int y) {
    return 0b1000000000000000 >> (x + y * 4);
}

// Moves left if possible
void move_tet_left() {
    struct tet_block tet = cur_piece;
    tet.x--;
    if (is_tet_legal(tet)) {
        cur_piece = tet; // If the move is valid, replace the board block with moved block
    }
}

void move_tet(int move_type) {
    struct tet_block tet = cur_piece;
    if (move_type == 0) { // Left
        tet.x--;
    } else if (move_type == 1) { // Right
        tet.x++;
    } else if (move_type == 2) { // Down
        tet.y--;
    } else {
        printf("You messed up. " + move_type + " is not a valid move type.");
        return 0;
    }

    if (is_tet_legal(tet)) {
        cur_piece = tet; // If the move is valid, replace the board block with moved block
    }

    return 0;
}

void rotate_tet(int rot_type) {
    struct tet_block tet = cur_piece;
    if (rot_type == 0) {
        if (tet.rotation == 3)
            tet.rotation = 0;
        else
            tet.rotation++;
    } else if (rot_type == 1) {
        if (tet.rotation == 0)
            tet.rotation = 3;
        else
            tet.rotation--;
    } else {
        printf("You messed up. " + rot_type + " is not a valid rotation type.");
        return 0;
    }

    if (is_tet_legal(tet)) {
        cur_piece = tet; // If the rotation is valid, replace the board block with rotated block.
    }

    return 0;
}

// Checks if the block is overlapping anything. True if not overlapping.
boolean is_tet_legal(struct tet_block tet) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int x = tet.x + i;
            int y = tet.y + j;
            if (tetronimos[tet.type][tet.rotation]&tet_location(i, j)) {
                if (x < 0 || x >= 10 || y < 0 || y >= 20) // If the block is our of the board
                    return 0;
            }
        }
    }
    return 1;
}