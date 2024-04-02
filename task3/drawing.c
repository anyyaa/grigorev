#define _CRT_SECURE_NO_WARNINGS

#include "drawing.h"
#include "structs.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

Menu menu;

void drawButtonsForWindow(SDL_Renderer* renderer, Button* buttons, int buttonsCount, int windowId, int selectedButtonIndex) {
    for (int i = 0; i < buttonsCount; i++) {
        if (buttons[i].windowId == windowId) {
            SDL_Rect buttonRect = { buttons[i].position.x, buttons[i].position.y, 200, 100 };
            if (i == selectedButtonIndex) {
                buttonRect.x -= 4;
                buttonRect.y -= 4;
                buttonRect.w += 8;
                buttonRect.h += 8;
            }
            SDL_Color buttonColor = { buttons[i].color.red, buttons[i].color.green, buttons[i].color.blue };
            SDL_SetRenderDrawColor(renderer, buttonColor.r, buttonColor.g, buttonColor.b, SDL_ALPHA_OPAQUE);
            SDL_RenderFillRect(renderer, &buttonRect);
        }
    }
}

int createWindows(SDL_Window** windows, SDL_Renderer** renderers) {
    for (int i = 0; i < menu.windowsCounter; i++) {
        windows[i] = SDL_CreateWindow("SDL Window with Buttons", menu.windows[i].position.x, menu.windows[i].position.y, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        if (windows[i] == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            for (int j = 0; j < i; j++) {
                SDL_DestroyWindow(windows[j]);
            }
            return 0;
        }

        renderers[i] = SDL_CreateRenderer(windows[i], -1, SDL_RENDERER_ACCELERATED);
        if (renderers[i] == NULL) {
            printf("Could not create the renderer: %s\n", SDL_GetError());
            for (int j = 0; j < i; j++) {
                SDL_DestroyRenderer(renderers[j]);
                SDL_DestroyWindow(windows[j]);
            }
            return 0;
        }
    }
    return 1;
}
