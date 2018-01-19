#include <tetris.h>

struct tetris_game {

    int width; // Width of board
    int height; // Height of board
    int gameover; // Is the game over?
    int score; // Game score
    struct tetris_tet {
        char tet_info[5][5]; // Tetronimo shapes
        int tet_width; // Tetronimo width
        int tet_height; // Tetronimo height
    }

};

struct tet_tet {
    
}