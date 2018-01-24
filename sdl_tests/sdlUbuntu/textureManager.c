//
//  textureManager.c
//  SDL_TEST
//
//  Created by Jeffrey Weng on 1/23/18.
//  Copyright © 2018 Jeffrey Weng. All rights reserved.
//

#include "textureManager.h"

SDL_Renderer* renderer = NULL;

SDL_Texture* loadTexture(char * filepath){
    SDL_Texture* newTexture = NULL;
    
    SDL_Surface * tempSurface = IMG_Load(filepath);
    if( tempSurface == NULL ){
        printf( "Unable to load image %s! SDL_image Error: %s\n", filepath, IMG_GetError() );
    }
    else{
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, tempSurface);
        if( newTexture == NULL){
            printf( "Unable to create texture from %s! SDL Error: %s\n", filepath, SDL_GetError() );
        }
        //Get rid of old loaded surface
        SDL_FreeSurface( tempSurface );
    }
    
    return newTexture;
}


void delay(unsigned int frameLimit){
    unsigned int ticks = SDL_GetTicks();
    
    if (frameLimit < ticks)
    {
        return;
    }
    
    if (frameLimit > ticks + 16)
    {
        SDL_Delay(16);
    }
    
    else
    {
        SDL_Delay(frameLimit - ticks);
    }
}


void drawImage(SDL_Texture* image, int x, int y){
    SDL_Rect dest;
    int w,h;
    
    SDL_QueryTexture(image, NULL, NULL, &w, &h);
    
    dest.x = x;
    dest.y = y;
    dest.w = w/8; //(1/8 = TILE_SIZE / SIZE OF IMAGE)
    dest.h = h/8; //(1/8 = TILE_SIZE / SIZE OF IMAGE)
    
    SDL_RenderCopy(renderer, image, NULL, &dest);
    
}
