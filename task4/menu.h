#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <stdbool.h>

void drawMenu();
void handleMenuInput(SDL_Event event, bool* quit, bool* start);

#endif 
