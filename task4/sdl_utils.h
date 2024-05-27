#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include <SDL.h>
#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <SDL_ttf.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define CELL_SIZE 20

extern SDL_Window* window;
extern SDL_Renderer* renderer;

bool initializeSDL();
void closeSDL();

#endif // SDL_UTILS_H
