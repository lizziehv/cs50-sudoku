#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "button.h"

/**************** structures ****************/
typedef struct button{
    SDL_Rect draw_rect;    // dimensions of button
    struct {
        Uint8 r, g, b, a;
    } colour;

    bool pressed;
} button_t;


void button_process_event(button_t *btn, const SDL_Event *ev) {
    // react on mouse click within button rectangle by setting 'pressed'
    if(ev->type == SDL_MOUSEBUTTONDOWN) {
        if(ev->button.button == SDL_BUTTON_LEFT &&
                ev->button.x >= btn->draw_rect.x &&
                ev->button.x <= (btn->draw_rect.x + btn->draw_rect.w) &&
                ev->button.y >= btn->draw_rect.y &&
                ev->button.y <= (btn->draw_rect.y + btn->draw_rect.h)) {
            btn->pressed = true;
        }
    }
}

bool button(SDL_Renderer *r, button_t *btn) {
    // draw button
    SDL_SetRenderDrawColor(r, btn->colour.r, btn->colour.g, btn->colour.b, btn->colour.a);
    SDL_RenderFillRect(r, &btn->draw_rect);

    // if button press detected - reset it so it wouldn't trigger twice
    if(btn->pressed) {
        btn->pressed = false;
        return true;
    }
    return false;
}
