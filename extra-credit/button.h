
#ifndef __BUTTON_H
#define __BUTTON_H

#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

/**************** structures ****************/
typedef struct button button_t;

void button_process_event(button_t *btn, const SDL_Event *ev);

bool button(SDL_Renderer *r, button_t *btn);

#endif
