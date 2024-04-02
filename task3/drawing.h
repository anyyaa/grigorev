#pragma once
#ifndef DRAWING_H
#define DRAWING_H

#include <SDL.h>
#include "structs.h"

void drawButtonsForWindow(SDL_Renderer* renderer, Button* buttons, int buttonsCount, int windowId, int selectedButtonIndex);
int createWindows(SDL_Window** windows, SDL_Renderer** renderers);

#endif
