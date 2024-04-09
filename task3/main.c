#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <stdlib.h>
#include "structs.h"
#include <string.h>
#include "initialization.h"
#include "drawing.h"
#define MAX_WINDOWS 3

bool windowsOpened[MAX_WINDOWS] = { false };
Menu menu;

int main() {
    init("data.txt");
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 700, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    bool quit = false;
    int selectedButtonIndex = 0;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_UP) {
                    selectedButtonIndex--;
                    if (selectedButtonIndex < 0) {
                        selectedButtonIndex = menu.buttonsCounter - 1;
                    }
                }
                else if (event.key.keysym.sym == SDLK_DOWN) {
                    selectedButtonIndex++;
                    if (selectedButtonIndex >= menu.buttonsCounter) {
                        selectedButtonIndex = 0;
                    }
                }
                else if (event.key.keysym.sym == SDLK_RETURN) {
                    getPressed(selectedButtonIndex, windowsOpened);
                    if (selectedButtonIndex == 2) {
                        quit = true;
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 150, 189, 215, 255);
        SDL_RenderClear(renderer); 

        getWindow(&menu, renderer, 0);
        drawButtonsForWindow(renderer, menu.buttons, menu.buttonsCounter, menu.windows[0].id, selectedButtonIndex);

        for (int i = 1; i < MAX_WINDOWS; i++) {
            if (windowsOpened[i]) {
                getWindow(&menu, renderer, i);
                drawButtonsForWindow(renderer, menu.buttons, menu.buttonsCounter, menu.windows[i].id, selectedButtonIndex);
            }
        }
                
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


