#define _CRT_SECURE_NO_WARNINGS

#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include "init.h"
#include "game.h"
#include "menu.h"
#include "sdl_utils.h"

int main(int argc, char* argv[]) {
    init("data.txt");

    if (!initializeSDL()) {
        printf("Ошибка при инициализации SDL\n");
        return 1;
    }

    bool quit = false;
    bool start = false;
    int currentLevel = 0;
    SDL_Event e;

    while (!quit) {
        if (!start) {
            drawMenu();

            while (SDL_PollEvent(&e) != 0) {
                handleMenuInput(e, &quit, &start);
            }

            SDL_Delay(10);
        }
        else {
            int nextLevel = startGame(currentLevel);
            if (nextLevel != -1 && nextLevel < levelCount) {
                currentLevel = nextLevel;
            }
            else {
                start = false;
                currentLevel = 0;
            }
        }
    }

    closeSDL();
    return 0;
}

