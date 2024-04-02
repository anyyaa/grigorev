#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <stdlib.h>
#include "structs.h"
#include <string.h>


SDL_Surface* screenSurface = NULL;
Menu menu;


int main() {
    init("data.txt");
    SDL_Window** windows = malloc(menu.windowsCounter * sizeof(SDL_Window*));
    SDL_Renderer** renderers = malloc(menu.windowsCounter * sizeof(SDL_Renderer*));

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    if (!createWindows(windows, renderers)) {
        free(windows);
        free(renderers);
        SDL_Quit();
        return 1;
    }

    bool quit = false;
    int selectedButtonIndex = 0;

    while (!quit) {
        for (int i = 0; i < menu.windowsCounter; i++) {
            SDL_Event event;
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
                        Button* selectedButton = &menu.buttons[selectedButtonIndex];
                        if (selectedButton->color.red == selectedButton->highlightColor.red &&
                            selectedButton->color.green == selectedButton->highlightColor.green &&
                            selectedButton->color.blue == selectedButton->highlightColor.blue) {
                            selectedButton->color = selectedButton->originalColor;
                        }
                        else {
                            selectedButton->color = selectedButton->highlightColor;
                        }
                    }
                }
            }

            SDL_SetRenderDrawColor(renderers[i], menu.windows[i].color.red, menu.windows[i].color.green, menu.windows[i].color.blue, 255);
            SDL_RenderClear(renderers[i]);
            drawButtonsForWindow(renderers[i], menu.buttons, menu.buttonsCounter, menu.windows[i].id, selectedButtonIndex);
            SDL_RenderPresent(renderers[i]);
        }
    }

    for (int i = 0; i < menu.windowsCounter; i++) {
        SDL_DestroyRenderer(renderers[i]);
        SDL_DestroyWindow(windows[i]);
    }
    free(windows);
    free(renderers);
    SDL_Quit();
    return 0;
}

