#include "tetris.h"
#include "istetlegal.h"

unsigned int tetronimos[7][4] = {
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

boolean tet_wall_kick(struct tet_block *tet) {
    tet->x -= 1; // Try to move it left
    if (is_tet_legal(*tet))
        return 1; // Success
    tet->x += 2; // Moves back and then one more to the right. Try to move it right
    if (is_tet_legal(*tet))
        return 1; // Success
    tet->x -= 1; // Moves back to where it was
    tet->y += 1; // Move up one
    if (is_tet_legal(*tet))
        return 1; // Success
    tet->y -= 1; // Return to where it was
    return 0; // Failure
}