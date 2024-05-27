#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <stdbool.h>

typedef struct {
    int x;
    int y;
} Position;

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;

typedef struct {
    Position segments[100];
    int length;
    Direction direction;
} Snake;

typedef struct {
    Position position;
    bool exists;
} Frog;

typedef struct {
    int frogCount;
    int snakeSpeed;
    int snakeColorR;
    int snakeColorG;
    int snakeColorB;
    int levelId;
} LevelInfo;

extern int levelCount;
extern LevelInfo* levels;

void initializeGame();
void handleInput(SDL_Event event);
void update(int frogCount, int snakeSpeed);
void render(int snakeColorR, int snakeColorG, int snakeColorB);
int startGame(int currentLevel);
void printStats(int level, int frogsEaten);

#endif 
