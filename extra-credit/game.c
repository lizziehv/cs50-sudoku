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
#define WIDTH 900
#define HEIGHT 700

/* Global variables */
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
bool quit = false;

/* For sudoku rendering */
int SUDOKU_X = 250;
int SUDOKU_Y = 100;
int SQUARE_SIZE = 45;
int BOARD_BORDER = 4;

/* For samurai rendering */
int SAMURAI_X = 250;
int SAMURAI_Y = 40;
int SAMURAI_SQUARE = 25;
int SAMURAI_BORDER = 2;

/* For text rendering */
TTF_Font* font_text;
TTF_Font* font_title;
SDL_Color textColor = { 0, 0, 0, 255 }; // black
SDL_Color titleColor = { 255, 255, 255, 255 }; // white

/* Mouse position */
int mouse_x = -1;
int mouse_y = -1;
int clicked_row = -1;
int clicked_column = -1;
int clicked_sudoku = -1;
int clicked_intersection_r = -1;
int clicked_intersection_c = -1;

/*********** Local functions ***********/
int game_init();
void render_screen();
void render_start();
void begin_puzzles();
void handle_events();
void render_sudoku(int sudoku[9][9], int original_sudoku[9][9], int board_x, int board_y, int border, int square_size, int level, int sudoku_number);
void render_samurai();
void render_options();
void game_clean();
SDL_Texture* to_texture(TTF_Font* font, char* string, SDL_Color textColor );
bool mouse_in_area(int x, int y, int w,int h);
void which_square(int x, int y, int w);

int screen = 0;
int original_sudoku[9][9];
int sudoku[9][9];

int original_samurai[5][9][9];
int samurai[5][9][9];

int main (int argc, char **argv){
  /* Begin window and renderer */
  if(game_init() != 0)
    return 1;

  render_screen();

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
  font_text = TTF_OpenFont("assets/Lato-Bold.ttf", 24);
  font_title = TTF_OpenFont("assets/Lato-Bold.ttf", 100);
  if(font_text == NULL ||font_title == NULL ){
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
    // mouse click buttons
    if (e.type == SDL_MOUSEBUTTONDOWN){
      //Get mouse position
      SDL_GetMouseState( &mouse_x, &mouse_y );
      if(screen == 0){
        if(mouse_in_area((WIDTH - (50*2 + 3*150))/2, 3*(HEIGHT/5), 150, 100))
          screen = 1;
        else if(mouse_in_area((WIDTH - (50*2 + 3*150))/2 + 200, 3*(HEIGHT/5), 150, 100))
          screen = 2;
        else if(mouse_in_area((WIDTH - (50*2 + 3*150))/2 + 400, 3*(HEIGHT/5), 150, 100))
          screen = 3;

        begin_puzzles();
      }
      else if(screen==1 || screen == 2){
        int sudoku_size = (SQUARE_SIZE + BOARD_BORDER)*9 + 5*BOARD_BORDER;
        if(mouse_in_area(SUDOKU_X, SUDOKU_Y,sudoku_size, sudoku_size)){
          which_square(SUDOKU_X, SUDOKU_Y, sudoku_size);
        }    
      }
      else if(screen == 3){
        int samurai_size = (SAMURAI_SQUARE + SAMURAI_BORDER)*9 + 5*SAMURAI_BORDER;
        int two_boxes_dist = 6*SAMURAI_SQUARE + 10*SAMURAI_BORDER;
        if(mouse_in_area(SAMURAI_X + two_boxes_dist, SAMURAI_Y + two_boxes_dist, samurai_size, samurai_size)){
          clicked_sudoku = 2;
          which_square(SAMURAI_X + two_boxes_dist, SAMURAI_Y + two_boxes_dist, samurai_size);
          clicked_intersection_r = clicked_row;
          clicked_intersection_c = clicked_column;
        }
        if(mouse_in_area(SAMURAI_X, SAMURAI_Y, samurai_size, samurai_size)){
          clicked_sudoku = 0;
          which_square(SAMURAI_X, SAMURAI_Y, samurai_size);
        }
        else if(mouse_in_area(SAMURAI_X, SAMURAI_Y + 2*two_boxes_dist, samurai_size, samurai_size)){
          clicked_sudoku = 3;
          which_square(SAMURAI_X, SAMURAI_Y + 2*two_boxes_dist, samurai_size);
        }
        else if(mouse_in_area(SAMURAI_X + 2*two_boxes_dist, SAMURAI_Y, samurai_size, samurai_size)){
          clicked_sudoku = 1;
          which_square(SAMURAI_X + 2*two_boxes_dist, SAMURAI_Y, samurai_size);
        }
        else if(mouse_in_area(SAMURAI_X + 2*two_boxes_dist, SAMURAI_Y + 2*two_boxes_dist, samurai_size, samurai_size)){
          clicked_sudoku = 4;
          which_square(SAMURAI_X + 2*two_boxes_dist, SAMURAI_Y + 2*two_boxes_dist, samurai_size);
        }

        if(clicked_sudoku==2){
          clicked_intersection_r = -1;
          clicked_intersection_c = -1;
        }
      }
      // handle button actions
      if(mouse_in_area(SUDOKU_X - 150, (HEIGHT)/7, 60, 60)){
        screen = 0; // navigate to home screen

        // reset presets
        mouse_x = -1;
        mouse_y = -1;
        clicked_row = -1;
        clicked_column = -1;
        clicked_sudoku = -1;
        clicked_intersection_r = -1;
        clicked_intersection_c = -1;
      }
      else if(mouse_in_area(SUDOKU_X - 150, 2*(HEIGHT)/5, 110, 60)){
        // give up button has been chosen (show recursive solver)
        if(screen != 3){
          solve(original_sudoku, screen);
        }
        else{
          if(solve_samurai(original_samurai)){
            print_samurai(stdout, original_samurai); 
          }
        }
      }
      // rerender
      render_screen();
    }
    // handle keyboard events
    if(e.type == SDL_KEYDOWN){
      int number = 0;
        if( e.key.keysym.sym == SDLK_1 ){
          number = 1;
        } else if(e.key.keysym.sym == SDLK_2) {
          number = 2;
        } else if(e.key.keysym.sym == SDLK_3){
          number = 3;
        } else if(e.key.keysym.sym == SDLK_4){
          number = 4;
        } else if(e.key.keysym.sym == SDLK_5){
          number = 5;
        } else if(e.key.keysym.sym == SDLK_6){
          number = 6;
        } else if(e.key.keysym.sym == SDLK_7){
          number = 7;
        } else if(e.key.keysym.sym == SDLK_8){
          number = 8;
        } else if(e.key.keysym.sym == SDLK_9){
          number = 9;
        }

        // assign to sudoku
        if((screen== 1 || screen == 2) && original_sudoku[clicked_row][clicked_column] == 0){
            sudoku[clicked_row][clicked_column] = number;
        }
        // assign to samurai
        else if(screen==3){
          samurai[clicked_sudoku][clicked_row][clicked_column] = number;
          if(clicked_intersection_r >= 0){
            samurai[2][clicked_intersection_r][clicked_intersection_c] = number;
          }
        }

      render_screen();
    }
  }
}

void render_screen(){
  /* Clear background */
  SDL_SetRenderDrawColor(renderer, 174, 195, 232, 255);
  SDL_RenderClear(renderer);

  if(screen == 0){
    render_start();
  }
  else if(screen == 1 || screen == 2){
    render_options();
    render_sudoku(sudoku, original_sudoku, SUDOKU_X, SUDOKU_Y, BOARD_BORDER, SQUARE_SIZE, screen, 1);
  }
  else if(screen == 3){
    render_options();
    render_samurai();
  }
  
  /* Rerender */
  SDL_RenderPresent(renderer);  
}

void render_start(){
  /* Text */
  SDL_Texture* text;

  text = to_texture(font_title, "SUDOKU", titleColor);
  SDL_Rect solidRect;

  SDL_QueryTexture( text, NULL, NULL, &solidRect.w, &solidRect.h );
  solidRect.x = (WIDTH - solidRect.w)/2;
  solidRect.y = (HEIGHT)/3;

  SDL_RenderCopy(renderer, text, NULL, &solidRect);

  /* Buttons */
  char* levels[3] = {"easy", "medium", "hard"};
  SDL_SetRenderDrawColor(renderer, 135, 94, 189, 255);

  SDL_Rect button;
  button.h = solidRect.h/2;
  button.w = 150;
  button.y = 3*(HEIGHT)/5;
  button.x = (WIDTH - (50*2 + 3*button.w))/2;

  for(int i=0; i < 3; i++){
    SDL_RenderFillRect(renderer, &button);

    /* Text */
    text = to_texture(font_text, levels[i], titleColor);

    SDL_QueryTexture(text, NULL, NULL, &solidRect.w, &solidRect.h);
    solidRect.x = button.x + (button.w - solidRect.w)/2;
    solidRect.y = button.y + (button.h - solidRect.h)/2;

    SDL_RenderCopy(renderer, text, NULL, &solidRect);
    button.x = button.x + 50 + button.w;
  }

}

void render_options(){
  /* Buttons */
  SDL_Texture* text;

  text = to_texture(font_text, "< Back", titleColor);
  SDL_Rect solidRect;

  SDL_QueryTexture( text, NULL, NULL, &solidRect.w, &solidRect.h );
  solidRect.x = SUDOKU_X - 150;
  solidRect.y = (HEIGHT)/7;

  SDL_RenderCopy(renderer, text, NULL, &solidRect);
  SDL_SetRenderDrawColor(renderer, 135, 94, 189, 255);
  char* options[3] = {"Give up", "Hint", "Done!"};
  SDL_Rect button;
  button.h = 60;
  button.w = 110;
  button.y = 2*(HEIGHT)/5;
  button.x = SUDOKU_X - 150;

  for(int i=0; i < 3; i++){
    SDL_RenderFillRect(renderer, &button);

    /* Text */
    text = to_texture(font_text, options[i], titleColor);

    SDL_QueryTexture(text, NULL, NULL, &solidRect.w, &solidRect.h);
    solidRect.x = button.x + (button.w - solidRect.w)/2;
    solidRect.y = button.y + (button.h - solidRect.h)/2;

    SDL_RenderCopy(renderer, text, NULL, &solidRect);
    button.y += 100;
  }
}

void render_sudoku(int sudoku[9][9], int original_sudoku[9][9], int board_x, int board_y, int border, int square_size, int level, int sudoku_number){
  /* Draw background Sudoku board */
  SDL_SetRenderDrawColor(renderer, 38, 49, 74, 255);
  SDL_Rect board;
  board.w = (square_size + border)*3 + border;
  board.h = (square_size + border)*3 + border;

  for(int i = 0; i < 3; i++){
    board.y = board_y + i*(board.h + border);
    for(int j = 0; j < 3; j++){
      board.x = board_x + j*(board.w + border);

      SDL_RenderFillRect(renderer, &board);
    }
  }
  
  /* Draw each square with entries from a sudoku */
  
  SDL_Rect r;
  r.w = square_size;
  r.h = square_size;

  for(int i = 0; i <= 8; i++){
    r.y = board_y + border + (border + square_size)*i + 2*(i/3)*(border);
    for(int j = 0; j <= 8; j++){
      /* Draw square */
      if(i == clicked_row && j == clicked_column && (level!= 3 || sudoku_number == clicked_sudoku)){            // clicked square
        SDL_SetRenderDrawColor(renderer, 255, 222, 251, 200);
      } 
      else if(level == 2 && (i == j || i == 8-j)){            // for diagonal matrices
        SDL_SetRenderDrawColor(renderer, 171, 202, 255, 150);
      } 
      else if(original_sudoku[i][j] == 0){                    // originally empty (white)
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200);
      }
      else {
        SDL_SetRenderDrawColor(renderer, 222, 224, 227, 150);     
      }
      
      r.x = board_x + border + (border + square_size)*j + 2*(j/3)*(border);
      SDL_RenderFillRect(renderer, &r);

      /* Get number */
      int number = (original_sudoku[i][j] != 0) ? original_sudoku[i][j] : sudoku[i][j];

      /* Draw red border on last clicked */
      if(i == clicked_row && j == clicked_column && original_sudoku[i][j] == 0 && (level!= 3 || sudoku_number == clicked_sudoku)){
        SDL_SetRenderDrawColor(renderer, 255, 0, 140, 255);
        SDL_RenderDrawRect(renderer, &r);
      }

      /* Print number */
      if(number != 0){
        char string[2];
        sprintf(string, "%d", number);

        SDL_Texture* solidTexture = to_texture( font_text, string, textColor );

        /* Set rectangle for text */
        SDL_Rect solidRect;
        SDL_QueryTexture( solidTexture, NULL, NULL, &solidRect.w, &solidRect.h );
	      solidRect.x = r.x + (square_size - solidRect.w)/2;
	      solidRect.y = r.y + (square_size - solidRect.h)/2;

        SDL_RenderCopy(renderer, solidTexture, NULL, &solidRect);
      }  
    }
  }
}

void render_samurai(){
  int two_boxes_dist = 6*SAMURAI_SQUARE + 10*SAMURAI_BORDER; //distance covered by two boxes
  // third sudoku
  render_sudoku(samurai[2], original_samurai[2], SAMURAI_X + two_boxes_dist, SAMURAI_Y + 
                two_boxes_dist, SAMURAI_BORDER, SAMURAI_SQUARE, 3, 2);
  // first sudoku
  render_sudoku(samurai[0], original_samurai[0], SAMURAI_X, SAMURAI_Y, SAMURAI_BORDER, SAMURAI_SQUARE, 3, 0);

  // second sudoku
  render_sudoku(samurai[1], original_samurai[1], SAMURAI_X + 2*two_boxes_dist, SAMURAI_Y, SAMURAI_BORDER, SAMURAI_SQUARE, 3, 1);

  //fourth sudoku
  render_sudoku(samurai[3], original_samurai[3], SAMURAI_X, SAMURAI_Y + 2*two_boxes_dist, SAMURAI_BORDER, SAMURAI_SQUARE, 3, 3);

  // fifth sudoku
  render_sudoku(samurai[4], original_samurai[4], SAMURAI_X + 2*two_boxes_dist, SAMURAI_Y + 
                2*two_boxes_dist, SAMURAI_BORDER, SAMURAI_SQUARE, 3, 4);
}

void begin_puzzles(){
  // normal sudokus with different levels
  if(screen == 2 || screen == 1){
    sudoku_build(original_sudoku, screen);
    create_puzzle(original_sudoku, 40, screen);

    // start sudoku matrix for user input
    for(int i = 0; i < 9; i++){
      for(int j = 0; j < 9; j++){
        sudoku[i][j] = original_sudoku[i][j];
      }
    }
  }
  // samurai puzzle
  else if(screen == 3){
    // read from file as an example
    FILE *f_ex = fopen("testdir/example1.txt", "r");
    parse_samurai(f_ex, original_samurai);
    fclose(f_ex);

    // start samurai matrix for user input
    for(int n = 0; n < 5; n++){
      for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
          samurai[n][i][j] = original_samurai[n][i][j];
        }
      }
    }
  }
}

/* Clean up before quitting main
 */
void game_clean(){
  /* Frees memory */
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_CloseFont(font_text);
  TTF_CloseFont(font_title);

  /* Shuts down all SDL subsystems */
  SDL_Quit();
  TTF_Quit();
}

/* @params font, string, textColor
 * return pointer to texture to be rendered
 */
SDL_Texture* to_texture(TTF_Font* font, char* string, SDL_Color textColor ){
  SDL_Surface* solid = TTF_RenderText_Solid(font, string, textColor);
	SDL_Texture* text = SDL_CreateTextureFromSurface( renderer, solid);
	SDL_FreeSurface(solid);

	return text;
}

/* @param x - x coordinate where area begins
 * @param y - y coordinate where area begins
 * @param w - area width
 * @param h - area height
 *
 * @return true if mouse coordinates are in the area.
 */
bool mouse_in_area(int x, int y, int w, int h){
  return (mouse_x <= x+w && mouse_x >= x && mouse_y >= y && mouse_y <= y+ h );
}

/* @param x - x coordinate where sudoku begins
 * @param y - y coordinate where sudoku begins
 * @param w - width and height of sudoku board
 *
 * Update pointers of clicked box
 */
void which_square(int x, int y, int w){
  int square_size = w/9;
  
  clicked_row = (int)((mouse_y - y)/square_size); 
  clicked_column = (int)((mouse_x - x)/square_size);
}
