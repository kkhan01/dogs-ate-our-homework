#include "map.h"
#include "textureManager.h"

int init();
void closeProgram();
void eventHandler();
int loadMedia();

//The window we'll be rendering to
SDL_Window* window = NULL;

SDL_Texture* tetrisBlockTexture = NULL;

SDL_Texture* unfilledBlockTexture = NULL;


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 512;

//Key press surfaces constants
enum KeyPressSurfaces{
    
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};


int init(){
    int success = 1;
    if(TTF_Init() < 0){
        printf("ttf could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = 0;
    }
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = 0;
    }
    else{
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }
        
        
        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL ){
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = 0;
        }
        else{
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if(renderer == NULL){
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = 0;
            }
            else{
                //Initialize renderer color
                SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
                
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = 0;
                }
                
            }
            
        }
        
    }
    return success;
    
}

//If there's loop for headers, move this
int loadMedia(){
    int success = 1;
    
    tetrisBlockTexture = loadTexture("SDL_TEST/sprites/tetrisBlock.png");
    unfilledBlockTexture = loadTexture("SDL_TEST/sprites/unfilledBlock.png");
    
    loadMap("SDL_TEST/sprites/map01.dat");
    
    if(tetrisBlockTexture == NULL || unfilledBlockTexture == NULL){
        printf("Failed to load texture images\n");
        success = 0;
    }
    
    
    
    return success;
}

void drawText(char* string, int size, int x, int y,
              int c1, int c2, int c3){
    
    int w = 0;
    int h = 0;
    
    TTF_Font* font = TTF_OpenFont("SDL_TEST/fonts/HelveticaNeue Medium.ttf", size);
    
    SDL_Color color = {c1, c2, c3};
    
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, string, color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    
    SDL_QueryTexture(textTexture, NULL, NULL, &w, &h);
    
    SDL_Rect textLocation = {x, y, w, h};
    
    SDL_RenderCopy(renderer, textTexture, NULL, &textLocation);
    
    SDL_FreeSurface(textSurface);
    
    SDL_DestroyTexture(textTexture);
    
    TTF_CloseFont(font);
}


void closeProgram(){
    
    SDL_DestroyTexture(tetrisBlockTexture);
    tetrisBlockTexture = NULL;
    
    SDL_DestroyTexture(unfilledBlockTexture);
    unfilledBlockTexture = NULL;
    
    
    
    //Destroy window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow( window );
    renderer = NULL;
    window = NULL;
    
    //Quit SDL subsystems
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    
}


void eventHandler(){
    //loop flag
    int quit = 0;
    
    unsigned int frameLimit = SDL_GetTicks() + 16;
    
    //Time
    char * timeText;
    char * numstr[21];
    int countdown = 1000000;
    int countdown_seconds = 180;
    
    //Score
    
    char * scoreText;
    char * numstrScore[21];
    int score = 0;
    
    //Event Handler
    SDL_Event event;
    //While application is running
    while(!quit){
        
        //Handle Events
        while(SDL_PollEvent(&event) != 0){
            
            //User requests quit
            if(event.type == SDL_QUIT || countdown_seconds <= 0){
                quit = 1;
            }
            
            else if( event.type == SDL_KEYDOWN )
            {
                //Select surfaces based on key press
                switch( event.key.keysym.sym )
                {
                    case SDLK_UP:
                        printf("Pressed Up\n");
                        break;
                        
                    case SDLK_DOWN:
                        printf("Pressed Down\n");
                        
                        break;
                        
                    case SDLK_LEFT:
                        printf("Pressed Left\n");
                        break;
                        
                    case SDLK_RIGHT:
                        printf("Pressed Right\n");
                        break;
                        
                    case SDLK_j:
                        printf("Pressed J (Left rotate)");
                        
                    case SDLK_k:
                        printf("Pressed k (Right rotate)");
                        
                    default:
                        break;
                }
            }
            
        }
        
        //Updating the surface
        
        //DRAWING TILE MAP
        SDL_RenderClear(renderer);
        
        
        
        drawMap();
        
        if(countdown % 50 == 0){
            countdown_seconds -= 1;
        }
        //Time
        sprintf(numstr, "%d", countdown_seconds);
        timeText = numstr;
        
        //Score
        sprintf(numstrScore, "%d", score);
        scoreText = numstrScore;
        
        
        drawText("Time:", FONTSIZE, SCREEN_WIDTH/2 + SCREEN_WIDTH/10, SCREEN_HEIGHT/2 - SCREEN_WIDTH/4, 0, 0, 0);
        drawText(timeText, FONTSIZE, SCREEN_WIDTH/2 + SCREEN_WIDTH/4, SCREEN_HEIGHT/2 - SCREEN_WIDTH/4, 0, 0, 0);
        drawText("Score:", FONTSIZE, SCREEN_WIDTH/2 + SCREEN_WIDTH/10, SCREEN_HEIGHT/2, 0, 0, 0);
        drawText(scoreText, FONTSIZE, SCREEN_WIDTH/2 + SCREEN_WIDTH/3, SCREEN_HEIGHT/2, 0, 0, 0);
        
        SDL_RenderPresent(renderer);
        
        //DELAY FOR CPU
        //printf("%d\n", frameLimit);
        
        countdown -= 1;
        delay(frameLimit);
        
        frameLimit = SDL_GetTicks() + 16;
        
        
        
        
    }
}


int main( int argc, char* args[] ){
    
    if(!init()){
        printf( "Failed to initialize!\n" );
    }
    else{
        if(!loadMedia()){
            printf("failed to load media\n");
        }
        else{
            eventHandler();
            
        }
    }
    
    closeProgram();
    return 0;
}
