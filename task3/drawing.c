#define _CRT_SECURE_NO_WARNINGS

#include "drawing.h"
#include "structs.h"
#include <stdbool.h>



Menu menu;

void getWindow(Menu* menu, SDL_Renderer* renderer, int id) {

    Window window = menu->windows[id];
    SDL_Rect rect = { window.position.x, window.position.y, 200, 300 };
    SDL_SetRenderDrawColor(renderer, window.color.red, window.color.green, window.color.blue, 255);
    SDL_RenderFillRect(renderer, &rect);

}

void drawButtonsForWindow(SDL_Renderer* renderer, Button* buttons, int buttonsCount, int windowId, int selectedButtonIndex) {
    for (int i = 0; i < buttonsCount; i++) {
        if (buttons[i].windowId == windowId) {
            SDL_Rect buttonRect = { buttons[i].position.x, buttons[i].position.y, 100, 50 };
            if (i == selectedButtonIndex) {
                buttonRect.x -= 3;
                buttonRect.y -= 3;
                buttonRect.w += 6;
                buttonRect.h += 6;
            }
            SDL_Color buttonColor = { buttons[i].color.red, buttons[i].color.green, buttons[i].color.blue };
            SDL_SetRenderDrawColor(renderer, buttonColor.r, buttonColor.g, buttonColor.b, SDL_ALPHA_OPAQUE);
            SDL_RenderFillRect(renderer, &buttonRect);
        }
    }
}
void getPressed(int selectedButtonIndex, bool* windowsOpened) {
    Button* selectedButton = &menu.buttons[selectedButtonIndex];
    if (selectedButton->color.red == selectedButton->highlightColor.red &&
        selectedButton->color.green == selectedButton->highlightColor.green &&
        selectedButton->color.blue == selectedButton->highlightColor.blue) {
        selectedButton->color = selectedButton->originalColor;
    }
    else {
        selectedButton->color = selectedButton->highlightColor;
        if (selectedButtonIndex % 3 == 0) {

            windowsOpened[selectedButtonIndex / 3 + 1] = true;
        }
        if (selectedButtonIndex % 3 == 1 && selectedButtonIndex < 5) {

            windowsOpened[selectedButtonIndex / 3 + 1] = false;
        }

    }
}
