//
//  map.c
//  SDL_TEST
//
//  Created by Jeffrey Weng on 1/22/18.
//  Copyright © 2018 Jeffrey Weng. All rights reserved.
//

#include "map.h"

Map map;

void loadMap(char *filename){
    int y_coord, x_coord;
    FILE *file;
    
    file = fopen(filename, "rb");
    
    if (file == NULL){
        printf("Failed to open map %s\n", filename);
        exit(1);
    }
    
    
    for(y_coord = 0; y_coord < TILE_MAX_Y; y_coord++){
        for(x_coord = 0; x_coord < TILE_MAX_X; x_coord++){
            //printf("%d", map.tile[y_coord][x_coord]);
            fscanf(file, "%d", &map.tile[y_coord][x_coord]);
        }
    }
    
    fclose(file);
    
    
}

void drawMap(){
    int y_coord, x_coord;
    
    for(y_coord = 0; y_coord < TILE_MAX_Y; y_coord++){
        for(x_coord = 0; x_coord < TILE_MAX_X; x_coord++){
            if(map.tile[y_coord][x_coord] != 0){
                drawImage(stoneTexture, x_coord * TILE_SIZE, y_coord * TILE_SIZE);
            }
            else if(map.tile[y_coord][x_coord] == 0){
                drawImage(brickTexture, x_coord * TILE_SIZE, y_coord * TILE_SIZE);
            }
        }
    }
    
    
}









