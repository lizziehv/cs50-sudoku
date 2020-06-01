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
#include "button.h"

/* Sets constants */
#define WIDTH 800
#define HEIGHT 600

/* Global variables */
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
bool quit = false;

/* For sudoku rendering */
int SUDOKU_X = 40;
int SUDOKU_Y = 40;
int SQUARE_SIZE = 40;
int BOARD_BORDER = 3;
int sudoku[9][9];

/* For text rendering */
TTF_Font* font;
SDL_Color textColor = { 0, 0, 0, 255 }; // black

/* Mouse position */
int mouse_x = -1;
int mouse_y = -1;
int clicked_row = -1;
int clicked_column = -1;

/*********** Local functions ***********/
int game_init();
void start_screen();
void setup_game();
void handle_events();
void draw_sudoku();
void game_clean();
SDL_Texture* SurfaceToTexture( SDL_Surface* surf );
bool mouse_in_area(int x, int y, int w,int h);
void which_square(int x, int y, int w);

int sudoku[9][9];

int main (int argc, char **argv){
  /* Begin window and renderer */
  if(game_init() != 0)
    return 1;

  /* Begin start screen */
  start_screen();

  sudoku_build(sudoku, 1);
  create_puzzle(sudoku, 40, 1);
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
  while(SDL_PollEvent(&e)){
    if (e.type == SDL_QUIT){
        quit = true;
    }
    if (e.type == SDL_MOUSEBUTTONDOWN){
      //Get mouse position
      SDL_GetMouseState( &mouse_x, &mouse_y );
      
      if(mouse_in_area(SUDOKU_X, SUDOKU_Y, 
          (SQUARE_SIZE + BOARD_BORDER)*9 + BOARD_BORDER, 
          (SQUARE_SIZE + BOARD_BORDER)*9 + BOARD_BORDER)){

          which_square(SUDOKU_X, SUDOKU_Y, (SQUARE_SIZE + BOARD_BORDER)*9 + BOARD_BORDER);
          draw_sudoku(sudoku);
      }
    }
  }
}

void start_screen(){
  /* Clear background */
  SDL_SetRenderDrawColor(renderer, 217, 197, 199, 255);
  SDL_RenderClear(renderer);

}

void setup_game(){
  /* Clear background */
  SDL_SetRenderDrawColor(renderer, 217, 197, 199, 255);
  SDL_RenderClear(renderer);  
}

void draw_sudoku(int sudoku[9][9]){
  /* Draw background Sudoku board */
  setup_game();
  SDL_SetRenderDrawColor(renderer, 110, 107, 105, 255);

  SDL_Rect board;
  board.w = (SQUARE_SIZE + BOARD_BORDER)*9 + BOARD_BORDER;
  board.h = (SQUARE_SIZE + BOARD_BORDER)*9 + BOARD_BORDER;
  board.x = SUDOKU_X;
  board.y = SUDOKU_Y;
  
  SDL_RenderFillRect(renderer, &board);

  /* Draw each square with entries from a sudoku */
  
  SDL_Rect r;
  r.w = SQUARE_SIZE;
  r.h = SQUARE_SIZE;

  for(int i = 0; i <= 8; i++){
    r.y = SUDOKU_X + (BOARD_BORDER + SQUARE_SIZE)*i + BOARD_BORDER;
    for(int j = 0; j <= 8; j++){
      /* Draw square */
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      r.x = SUDOKU_Y + (BOARD_BORDER + SQUARE_SIZE)*j + BOARD_BORDER;
      SDL_RenderFillRect(renderer, &r);

      /* Draw red border on last clicked */
      if(i == clicked_row && j == clicked_column){
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &r);
      }
      

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


bool mouse_in_area(int x, int y, int w, int h){
  return (mouse_x <= x+w && mouse_x >= x && mouse_y >= y && mouse_y <= y+ h );
}

void which_square(int x, int y, int w){
  int square_size = w/9;
  
  clicked_row = (int)((mouse_y - y)/square_size); 
  clicked_column = (int)((mouse_x - x)/square_size);
}
