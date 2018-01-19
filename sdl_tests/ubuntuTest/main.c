#include <SDL2/SDL.h>
#include <stdio.h>

int init();
void close();

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//The window we'll be rendering to
SDL_Window* window = NULL;

//The surface contained by the window
SDL_Surface* screenSurface = NULL;

//images
SDL_Surface* tetrisBlock = NULL;

int init(){
  int success = 1;
  if(SDL_Init(SDL_INIT_VIDEO) < 0){
    printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    success = 0;
  }
  else{
     window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
     if( window == NULL ){
      printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
      success = 0;
     }
     else{
      //Get window surface
      screenSurface = SDL_GetWindowSurface( window );
     }
      
  }
  return success;

}

void closeProgram(){
  //Destroy window
  SDL_DestroyWindow( window );
  window = NULL;
  
  //Quit SDL subsystems
  SDL_Quit();

}

void eventHandler(){
  //loop flag
  int quit = 0;

  //Event Handler
  SDL_Event event;
  //While application is running
  while(!quit){

    //Handle Events
    while(SDL_PollEvent(&event) != 0){

      //User requests quit
      if(event.type == SDL_QUIT){
	quit = 1;
      }
    }

    //Updating the surface
    
    SDL_UpdateWindowSurface(window);
  }
}


int main( int argc, char* args[] ){
  if(!init()){
    printf( "Failed to initialize!\n" );
  }
  else{
    //DO THINGS
    eventHandler();
  }

  closeProgram();
  return 0;
}
