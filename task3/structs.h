#pragma once

#ifndef STRUCTS_H
#define STRUCTS_H

#include <SDL.h>



typedef struct {
    Uint8 red;
    Uint8 green;
    Uint8 blue;
} Color;

typedef struct {
    SDL_Point position;
    Color color;
    int id;
    SDL_Window* hwnd;
} Window;

typedef struct {
    SDL_Point position;
    Color color;
    Color highlightColor;
    Color originalColor;
    int windowId;
    char name[255];
    SDL_Window* hwnd;
} Button;

typedef struct {
    int buttonsCounter;
    int windowsCounter;
    Window* windows;
    Button* buttons;
    int currentButton;
} Menu;

typedef enum {
    UP, DOWN, ENTER
} Click;

#endif
