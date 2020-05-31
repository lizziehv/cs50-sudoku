#include <stdio.h>    /* printf and fprintf */
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL_ttf.h>

#ifdef _WIN32
#include <SDL/SDL.h>  /* Windows-specific SDL2 library */
#else
#include <SDL2/SDL.h> /* macOS- and GNU/Linux-specific */
#endif

#include "../common/common.h"
#include "../solve/solve.h"
#include "../create/create.h"

/* Sets constants */
#define WIDTH 800
#define HEIGHT 600

/* Global variables */
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
bool quit = false;

/* For sudoku rendering */
int SUDOKU_X = WIDTH;
int SUDOKU_Y = HEIGHT;
int SQUARE_SIZE = 40;
int BOARD_BORDER = 3;

/* For text rendering */
TTF_Font* font;
SDL_Color textColor = { 0, 0, 0, 255 }; // black
SDL_Color backgroundColor = { 255, 255, 255, 255 }; // white


/*********** Local functions ***********/
int game_init();
void setup_game();
void handle_events();
void draw_sudoku();
void game_clean();
SDL_Texture* SurfaceToTexture( SDL_Surface* surf );

int main (int argc, char **argv){
  /* Begin window and renderer */
  if(game_init() != 0)
    return 1;

  /* Game setup */
  setup_game();

  /* Start and draw a sudoku */
  int sudoku[9][9];
  if (sudoku_build(sudoku, 1)) {
    create_puzzle(sudoku, 40, 1);
  }
  else {
    fprintf(stderr, "Error: Problem filling in sudoku.\n"); 
    return 2; 
  }

  draw_sudoku(sudoku);

  while(!quit){
    handle_events();
    
  }  
  
  game_clean();

  return 0;
}

int game_init(){
  /* Initialises the SDL video subsystem (as well as the events subsystem)*/
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "SDL failed to initialise: %s\n", SDL_GetError());
    return 1;
  }

  /* Initializes fonts */
  if(TTF_Init() != 0){
    fprintf(stderr, "SDL TTF failed to initialise: %s\n", TTF_GetError());
    return 1;
  }

  /* Creates a SDL window */
  window = SDL_CreateWindow("Sudoku",      // Title of the SDL window
                SDL_WINDOWPOS_CENTERED,    // Position x of the window
                SDL_WINDOWPOS_CENTERED,    // Position y of the window
                WIDTH,                     // Width of the window in pixels
                HEIGHT,                    // Height of the window in pixels
                0);                        // Additional flag(s)

  /* Creates a renderer */
  renderer = SDL_CreateRenderer(window, -1, 0);

  /* Load font */
  font = TTF_OpenFont("assets/Lato-Bold.ttf", 24);
  if(font == NULL){
    fprintf(stderr, "Failed to load font: %s\n", TTF_GetError());
    return -1;
  }

  return 0;
}

void handle_events(){
  /* Keep presenting until window is closed */
  SDL_Event e;
  if(SDL_PollEvent(&e)){
    if (e.type == SDL_QUIT){
        quit = true;
    }
    if (e.type == SDL_KEYDOWN){
        quit = true;
    }
  }
}

void setup_game(){
  /* Clear background */
  SDL_SetRenderDrawColor(renderer, 217, 197, 199, 255);
  SDL_RenderClear(renderer);

  
}

void draw_sudoku(int sudoku[9][9]){
  /* Draw background Sudoku board */
  SDL_SetRenderDrawColor(renderer, 110, 107, 105, 255);

  SDL_Rect board;
  board.w = (SQUARE_SIZE + BOARD_BORDER)*9 + BOARD_BORDER;
  board.h = (SQUARE_SIZE + BOARD_BORDER)*9 + BOARD_BORDER;
  board.x = SUDOKU_X/2 - board.w/2;
  board.y = SUDOKU_Y/2 - board.w/2;
  
  SDL_RenderFillRect(renderer, &board);

  /* Draw each square with entries from a sudoku */
  
  SDL_Rect r;
  r.w = SQUARE_SIZE;
  r.h = SQUARE_SIZE;

  for(int i = 0; i <= 8; i++){
    r.x = board.x + (BOARD_BORDER + SQUARE_SIZE)*i + BOARD_BORDER;
    for(int j = 0; j <= 8; j++){
      /* Draw square */
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      r.y = board.y + (BOARD_BORDER + SQUARE_SIZE)*j + BOARD_BORDER;
      SDL_RenderFillRect(renderer, &r);

      /* Draw border */
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderDrawRect(renderer, &r);

      /* Print number */
      int number = sudoku[i][j];
      if(number != 0){
        char string[2];
        sprintf(string, "%d", number);

        SDL_Surface* solid = TTF_RenderText_Solid( font, string, textColor );
        SDL_Texture* solidTexture = SurfaceToTexture( solid );

        /* Set rectangle for text */
        SDL_Rect solidRect;

        SDL_QueryTexture( solidTexture, NULL, NULL, &solidRect.w, &solidRect.h );
	      solidRect.x = r.x + (SQUARE_SIZE - solidRect.w)/2;
	      solidRect.y = r.y + (SQUARE_SIZE - solidRect.h)/2;

        SDL_RenderCopy(renderer, solidTexture, NULL, &solidRect);
      }  
    }
  }
  /* Rerender */
  SDL_RenderPresent(renderer);
}

void game_clean(){
  /* Frees memory */
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_CloseFont(font);

  /* Shuts down all SDL subsystems */
  SDL_Quit();
  TTF_Quit();
}

SDL_Texture* SurfaceToTexture( SDL_Surface* surf ){
	SDL_Texture* text;

	text = SDL_CreateTextureFromSurface( renderer, surf );

	SDL_FreeSurface( surf );

	return text;
}
