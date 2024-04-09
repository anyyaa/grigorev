#pragma once
#ifndef DRAWING_H
#define DRAWING_H

#include <SDL.h>
#include <stdbool.h>
#include "structs.h"

void drawButtonsForWindow(SDL_Renderer* renderer, Button* buttons, int buttonsCount, int windowId, int selectedButtonIndex);
void getWindow(Menu* menu, SDL_Renderer* renderer, int id);
void getPressed(int selectedButtonIndex, bool* windowsOpened);

#endif
