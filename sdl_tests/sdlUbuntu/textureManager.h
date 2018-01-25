//
//  textureManager.h
//  SDL_TEST
//
//  Created by Jeffrey Weng on 1/23/18.
//  Copyright © 2018 Jeffrey Weng. All rights reserved.
//

#ifndef textureManager_h
#define textureManager_h

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h> 

SDL_Texture* loadTexture(char * str);

void drawImage(SDL_Texture *image, int x, int y);
void delay();

extern SDL_Renderer* renderer;


#endif /* textureManager_h */
