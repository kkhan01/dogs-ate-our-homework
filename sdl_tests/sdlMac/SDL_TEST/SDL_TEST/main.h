//
//  main.h
//  SDL_TEST
//
//  Created by Jeffrey Weng on 1/22/18.
//  Copyright © 2018 Jeffrey Weng. All rights reserved.
//

#ifndef main_h
#define main_h

#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>
#include <SDL2_image/SDL_image.h>


int init();
void closeProgram();
void eventHandler();
int loadMedia();

//The window we'll be rendering to
SDL_Window* window = NULL;

SDL_Texture* loadTexture(char * str);

SDL_Renderer* renderer = NULL;

SDL_Texture* texture = NULL;



#endif /* main_h */
