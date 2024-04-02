#define _CRT_SECURE_NO_WARNINGS

#include "initialization.h"
#include "structs.h"
#include <stdio.h>


Menu menu;

void init(const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        return;
    }

    menu.windowsCounter = 0;
    menu.buttonsCounter = 0;

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        strtok(line, "\n");
        printf(line);

        if (strcmp(line, "WindowBegin") == 0) {
            menu.windowsCounter++;
            Window window;
            fscanf(file, "\tPosition=(%d,%d)\n", &window.position.x, &window.position.y);
            fscanf(file, "\tColor=(%d,%d,%d)\n", &window.color.red, &window.color.green, &window.color.blue);
            fscanf(file, "\tId=%d\n", &window.id);

            menu.windows = (Window*)realloc(menu.windows, sizeof(Window) * menu.windowsCounter);
            menu.windows[menu.windowsCounter - 1] = window;
            fgets(line, sizeof(line), file);
        }
        else if (strcmp(line, "ButtonBegin") == 0) {
            menu.buttonsCounter++;
            Button button;
            fscanf(file, "\tPosition=(%d,%d)\n", &button.position.x, &button.position.y);
            fscanf(file, "\tColor=(%d,%d,%d)\n", &button.color.red, &button.color.green, &button.color.blue);
            fscanf(file, "\tHiglightColor=(%d,%d,%d)\n", &button.highlightColor.red, &button.highlightColor.green, &button.highlightColor.blue);
            fscanf(file, "\tName=%s\n", button.name);
            fscanf(file, "\tWindowId=%d\n", &button.windowId);
            button.originalColor = button.color;

            menu.buttons = (Button*)realloc(menu.buttons, sizeof(Button) * menu.buttonsCounter);
            menu.buttons[menu.buttonsCounter - 1] = button;
            fgets(line, sizeof(line), file);
        }
        else if (strcmp(line, "MenuEnd") == 0) {
            fclose(file);
            return;
        }
    }
}
