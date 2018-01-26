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
            if(map.tile[y_coord][x_coord] == 0){
                drawImage(unfilledBlockTexture, x_coord * TILE_SIZE, y_coord * TILE_SIZE);
            }
            else if(map.tile[y_coord][x_coord] != 0){
                drawImage(tetrisBlockTexture, x_coord * TILE_SIZE, y_coord * TILE_SIZE);
            }
        }
    }
    
    
}

int clear_row(){
  int filled = 0;//will be used to make sure last row was filled
  int counter = 0;//counter to iterate with in loops over board
  while(counter < 10 && map.tile[15][counter] == 2){//checks to see if last row filed
    filled++;
    counter++;
  }
  counter = 0;
  if(filled == 10){//it was filled, gotta clear it up
    while(counter < 10){
      map.tile[15][counter] = 0;
      counter++;
      //printf("counter: %d\n", counter);
    }
  }
  else{//it wasnt filled, gotta restart function
    filled = 0;
    counter = 0;
    return 0;
  }
  return 100;
  //function ends
}

void gravity(){
  int xcounter = 0;//counter to iterate with in loops over board
  int ycounter = 0;//counter to iterate with in loops over board
  for(ycounter = 14; ycounter >= 0; ycounter--){
    for(xcounter = 9; xcounter >= 0; xcounter--){
      if(map.tile[ycounter][xcounter] == 2){//block that is the bottom or has touched another block touching the bottom
	if(map.tile[ycounter+1][xcounter] == 0){
	  map.tile[ycounter+1][xcounter] = 2;
	  map.tile[ycounter][xcounter] = 0;
	}
	//else stays in place i guess
      }
      //else it was empty space or a moving tetrimo
      //im thinking we have another method handle tetrimo movements
    }
  }
}

void controlledGravity(){
    int xcounter = 0;
    int ycounter = 0;
    for(ycounter = 14; ycounter >= 0; ycounter--){
        for(xcounter = 9; xcounter >= 0; xcounter--){
            if(map.tile[ycounter][xcounter] == 1){//block that is the bottom or has touched another block touching the bottom
                if(map.tile[ycounter+1][xcounter] == 0){
                    map.tile[ycounter+1][xcounter] = 1;
                    map.tile[ycounter][xcounter] = 0;
                    
                }
                //else stays in place i guess
            }
            //else it was empty space or a moving tetrimo
            //im thinking we have another method handle tetrimo movements
        }
    }
}









