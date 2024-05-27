#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "init.h"
#include "game.h"

int levelCount = 0;
LevelInfo* levels = NULL;

void init(const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        strtok(line, "\n");

        if (strcmp(line, "LevelBegin") == 0) {
            levelCount++;
            levels = realloc(levels, sizeof(LevelInfo) * levelCount);
            LevelInfo level;
            fscanf(file, "\tFrogCount=%d\n", &level.frogCount);
            fscanf(file, "\tSnakeSpeed=%d\n", &level.snakeSpeed);
            fscanf(file, "\tColor=(%d,%d,%d)\n", &level.snakeColorR, &level.snakeColorG, &level.snakeColorB);
            fscanf(file, "\tLevelId=%d\n", &level.levelId);

            levels[levelCount - 1] = level;
        }
        else if (strcmp(line, "MenuEnd") == 0) {
            fclose(file);
            return;
        }
    }
}
