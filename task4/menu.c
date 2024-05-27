#define _CRT_SECURE_NO_WARNINGS
#include "menu.h"
#include "sdl_utils.h"

void drawMenu() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_Rect startButton = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 3, SCREEN_WIDTH / 2, 50 };
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &startButton);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &startButton);

    SDL_Rect exitButton = { SCREEN_WIDTH / 4, SCREEN_HEIGHT * 2 / 3, SCREEN_WIDTH / 2, 50 };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &exitButton);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &exitButton);

    SDL_RenderPresent(renderer);
}

void handleMenuInput(SDL_Event event, bool* quit, bool* start) {
    if (event.type == SDL_QUIT) {
        *quit = true;
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        SDL_Rect startButton = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 3, SCREEN_WIDTH / 2, 50 };
        SDL_Rect exitButton = { SCREEN_WIDTH / 4, SCREEN_HEIGHT * 2 / 3, SCREEN_WIDTH / 2, 50 };

        if (x >= startButton.x && x <= startButton.x + startButton.w && y >= startButton.y && y <= startButton.y + startButton.h) {
            *start = true;
        }
        else if (x >= exitButton.x && x <= exitButton.x + exitButton.w && y >= exitButton.y && y <= exitButton.y + exitButton.h) {
            *quit = true;
        }
    }
}
