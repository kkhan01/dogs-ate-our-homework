//
//  map.c
//  SDL_TEST
//
//  Created by Jeffrey Weng on 1/22/18.
//  Copyright © 2018 Jeffrey Weng. All rights reserved.
//

#include "map.h"
#include "istetlegal.h"

Map map;
int cur_block_num; // Current block in randomly generated block array
int tets_queue[7];

struct tet_block cur_piece;
struct tet_block queue[5];

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

int check_row(int i){
  int filled = 0;//will be used to make sure last row was filled
  int counter = 0;//counter to iterate with in loops over board
  while(counter < 10 && map.tile[i][counter] == 2){//checks to see if last row filed
    filled++;
    counter++;
  }
  if(filled == 10){//it was filled, clear and return true
    clear_row(i);
    print_board();
    normalGravity();
    return 1;
  }
  else{
    return 0;
  }
}
void normalGravity(){
  int xcounter = 0; //counter to iterate with in loops over board
  int ycounter = 0; //counter to iterate with in loops over board
  for (ycounter = 14; ycounter >= 0; ycounter--) {
    for (xcounter = 9; xcounter >= 0; xcounter--) {
      if (map.tile[ycounter][xcounter] == 2) {
        //block that is the bottom or has touched another block touching the bottom
        if (map.tile[ycounter + 1][xcounter] == 0) {
          map.tile[ycounter + 1][xcounter] = 2;
          map.tile[ycounter][xcounter] = 0;
        } //else stays in place i guess
      } //else it was empty space or a moving tetrimo
      //im thinking we have another method handle tetrimo movements
    }
  }
}
void clear_row(int i){
  /*
  int counter = 0;//counter to iterate with in loops over board
  while(counter < 10){
    map.tile[i][counter] = 0;
    counter++;
    //printf("counter: %d\n", counter);
  }*/
  for (int j = 0; j < 10; j++)
    map.tile[15][j] = 0;
  for (i; i > 0; i--) {
    for (int j = 0; j < 10; j++) {
      map.tile[i][j] = map.tile[i - 1][j];
    }
  }
  cur_piece.y++;
}

void gravity() {
  /*
  int xcounter = 0; //counter to iterate with in loops over board
  int ycounter = 0; //counter to iterate with in loops over board
  for (ycounter = 14; ycounter >= 0; ycounter--) {
    for (xcounter = 9; xcounter >= 0; xcounter--) {
      if (map.tile[ycounter][xcounter] == 2) {
        //block that is the bottom or has touched another block touching the bottom
        if (map.tile[ycounter + 1][xcounter] == 0) {
          map.tile[ycounter + 1][xcounter] = 2;
          map.tile[ycounter][xcounter] = 0;
        } //else stays in place i guess
      } //else it was empty space or a moving tetrimo
      //im thinking we have another method handle tetrimo movements
    }
  }
  */
  move_tet(2);
}


int controlledGravity() {
  //print_board();
  int xcounter = 0;
  int ycounter = 0;
  int returntype = 0;
  cur_piece.y = cur_piece.y + 1;
  for (ycounter = 14; ycounter >= 0; ycounter--) {
    for (xcounter = 9; xcounter >= 0; xcounter--) {
      if (map.tile[ycounter][xcounter] == 1) { //block that is the bottom or has touched another block touching the bottom
        if (ycounter + 1 == 15 && map.tile[ycounter + 1][xcounter] != 2) {
          map.tile[ycounter][xcounter] = 0;
          map.tile[15][xcounter] = 2;
          returntype = -1;
        } else if (map.tile[ycounter + 1][xcounter] == 0) { //move down
          map.tile[ycounter + 1][xcounter] = 1;
          map.tile[ycounter][xcounter] = 0;
          returntype = 1;
        } else if (map.tile[ycounter + 1][xcounter] == 2) { //convert into 2
          map.tile[ycounter][xcounter] = 2;
          returntype = -1;
        } else {
          returntype = 0; //idk what to do really
        }
      }
    }
  }
  return returntype;
}


void spawn() {
  next_tet();
  printf("Current type: %d\n", cur_piece.type);
  cur_piece.type = tets_queue[cur_block_num++];
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tetronimos[cur_piece.type][cur_piece.rotation]&tet_location(i, j)) {
	    //printf("X: %d\nY: %d\n", cur_piece.x + i, cur_piece.y + j);
	      map.tile[cur_piece.y + j][cur_piece.x + i] = 1;
      }
    }
  }
}

void next_tet() {
  //printf("Current Piece: %d\n", queue[0]);
  cur_piece = queue[0];
  cur_piece.x = 5;
  cur_piece.y = 0;
  for (int i = 0; i < 4; i++) {
    queue[i] = queue[i + 1];
  }
  queue[4].type = tets_queue[cur_block_num++];
  //printf("current num: %d\n", cur_block_num);
  if (cur_block_num >= 7)
    fill_queue();
  if (!is_tet_legal(cur_piece))
    // End Game
    printf("GG\n");
}

void fill_queue() {
  ran_gen_blocks();
  cur_piece.type = tets_queue[cur_block_num++];
  //printf("TYPE: %d", cur_piece.type);
  cur_piece.rotation = 0;
  cur_piece.x = 5;
  cur_piece.y = 0;
  for (int i = 0; i < 5; i++) {   
    queue[i].type = tets_queue[cur_block_num++];
    queue[i].rotation = 0;
  }
}

void ran_gen_blocks() { // Generates the random blocks
  unsigned int tet_types[7] = {0, 1, 2, 3, 4, 5, 6};
  for (int i = 0; i < 7; i++) {
    int j = rand() % (7 - i);
    //printf("J: %d", j);
    //printf("Tet: %x\n", tet_types[j]);
    tets_queue[i] = tet_types[j];
    for (; j < 6; j++) {
      tet_types[j] = tet_types[j + 1];
    }
  }
  cur_block_num = 0;
}

void move_tet(int move_type) {
  struct tet_block tet = cur_piece;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tetronimos[cur_piece.type][cur_piece.rotation] & tet_location(i, j)) {
        //printf("X: %d\nY: %d\n", cur_piece.x + i, cur_piece.y + j);
        map.tile[cur_piece.y + j][cur_piece.x + i] = 0;
      }
    }
  }
  if (move_type == 0) { // Left
    tet.x--;
  } else if (move_type == 1) { // Right
    tet.x++;
  } else if (move_type == 2) { // Down
    if (check_place(tet)) { // if it can't move
    printf("can't move!\n");
    for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tetronimos[cur_piece.type][cur_piece.rotation]&tet_location(i, j)) {
	    //printf("X: %d\nY: %d\n", cur_piece.x + i, cur_piece.y + j);
	      map.tile[cur_piece.y + j][cur_piece.x + i] = 2;
      }
    }
    }
      sleep(1);
      spawn();
    } else { // otherwise move down
      tet.y++;
    }
  } else {
    printf("You messed up. %d is not a valid move type.", move_type);
  }

  if (is_tet_legal(tet)) {
    cur_piece = tet; // If the move is valid, replace the board block with moved block
  } else {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
      if (tetronimos[cur_piece.type][cur_piece.rotation] & tet_location(i, j)) {
        //printf("X: %d\nY: %d\n", cur_piece.x + i, cur_piece.y + j);
        map.tile[cur_piece.y + j][cur_piece.x + i] = 2;
      }
    }
  }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tetronimos[cur_piece.type][cur_piece.rotation] & tet_location(i, j)) {
        //printf("X: %d\nY: %d\n", cur_piece.x + i, cur_piece.y + j);
        map.tile[cur_piece.y + j][cur_piece.x + i] = 1;
      }
    }
  }
}

void rotate_tet(int rot_type) {
  struct tet_block tet = cur_piece;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tetronimos[cur_piece.type][cur_piece.rotation]&tet_location(i, j)) {
	    //printf("X: %d\nY: %d\n", cur_piece.x + i, cur_piece.y + j);
	    map.tile[cur_piece.y + j][cur_piece.x + i] = 0;
      }
    }
  }
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
    printf("You messed up. %d is not a valid rotation type.", rot_type);
  }

  if (is_tet_legal(tet) || tet_wall_kick(&tet)) {
    cur_piece = tet; // If the rotation is valid or a wall kick is available, replace the board block with rotated block.
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tetronimos[cur_piece.type][cur_piece.rotation]&tet_location(i, j)) {
	    //printf("X: %d\nY: %d\n", cur_piece.x + i, cur_piece.y + j);
	    map.tile[cur_piece.y + j][cur_piece.x + i] = 1;
      }
    }
  }
}

int check_place(struct tet_block tet) {
  tet.y++;
  if (is_tet_legal(tet))
    return 0;
  else
    return 1;
}

int game_end(){// 1 for end, 0 for still playing
  int row;
  int returntype = 0;
  for(row = 0; row < 6 && map.tile[row][6]!=0; row++){
    if(row == 5){
      returntype = 1;
    }
  }
  return returntype;
}
//TEST METHOD, COMMENT OUT USES AT THE END
void print_board(){
  int i, j;
  for(i = 0; i < 16; i++){
    for(j = 0; j < 10; j++){
      printf("%d", map.tile[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

/*======== unsigned is_tet_legal ==========
Inputs:  struct tet_block tet
Returns: Checks if the block is overlapping anything. True (1) if not overlapping.
=======================================*/
boolean is_tet_legal(struct tet_block tet) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int x = tet.x + i;
            int y = tet.y + j;
            if (tetronimos[tet.type][tet.rotation]&tet_location(i, j)) {
                if (x < 0 || x >= 10 || y < 0 || y >= 16) // If the block is out of the board
                    return 0;
                if (y >= 0 && map.tile[y][x] > 0)
                    return 0;
            }
        }
    }
    return 1;
}
