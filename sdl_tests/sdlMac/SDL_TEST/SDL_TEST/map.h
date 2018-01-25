//
//  map.h
//  SDL_TEST
//
//  Created by Jeffrey Weng on 1/22/18.
//  Copyright © 2018 Jeffrey Weng. All rights reserved.
//

#ifndef map_h
#define map_h

#define TILE_MAX_Y 16
#define TILE_MAX_X 10

#define TILE_SIZE 32
#define FONTSIZE 36



#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>


void loadMap();
void drawMap();

typedef struct Map{
    int tile[TILE_MAX_Y][TILE_MAX_X]; //(16,10)
}Map;

extern Map map;

void drawImage(SDL_Texture *image, int x, int y);

extern SDL_Texture* tetrisBlockTexture;

extern SDL_Texture* unfilledBlockTexture;

#endif /* map_h */
