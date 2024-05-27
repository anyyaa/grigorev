#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "game.h"
#include "sdl_utils.h"

Snake snake;
Frog frog;
bool gameOver = false;
int eatenFrogs = 0;

void initializeGame() {
    snake.length = 1;
    snake.segments[0].x = SCREEN_WIDTH / 2;
    snake.segments[0].y = SCREEN_HEIGHT / 2;
    snake.direction = RIGHT;
    frog.position.x = 100;
    frog.position.y = 100;
    frog.exists = true;
    gameOver = false;
    eatenFrogs = 0;
}

void handleInput(SDL_Event event) {
    switch (event.key.keysym.sym) {
    case SDLK_UP:
        if (snake.direction != DOWN)
            snake.direction = UP;
        break;
    case SDLK_DOWN:
        if (snake.direction != UP)
            snake.direction = DOWN;
        break;
    case SDLK_LEFT:
        if (snake.direction != RIGHT)
            snake.direction = LEFT;
        break;
    case SDLK_RIGHT:
        if (snake.direction != LEFT)
            snake.direction = RIGHT;
        break;
    }
}

void update(int frogCount, int snakeSpeed) {
    Position prevHead = snake.segments[0];

    for (int i = snake.length - 1; i > 0; --i) {
        snake.segments[i] = snake.segments[i - 1];
    }

    switch (snake.direction) {
    case UP:
        snake.segments[0].y -= CELL_SIZE;
        break;
    case DOWN:
        snake.segments[0].y += CELL_SIZE;
        break;
    case LEFT:
        snake.segments[0].x -= CELL_SIZE;
        break;
    case RIGHT:
        snake.segments[0].x += CELL_SIZE;
        break;
    }

    if (snake.segments[0].x < 0)
        snake.segments[0].x = SCREEN_WIDTH - CELL_SIZE;
    else if (snake.segments[0].x >= SCREEN_WIDTH)
        snake.segments[0].x = 0;

    if (snake.segments[0].y < 0)
        snake.segments[0].y = SCREEN_HEIGHT - CELL_SIZE;
    else if (snake.segments[0].y >= SCREEN_HEIGHT)
        snake.segments[0].y = 0;

    for (int i = 1; i < snake.length; ++i) {
        if (snake.segments[0].x == snake.segments[i].x && snake.segments[0].y == snake.segments[i].y) {
            gameOver = true;
            return;
        }
    }

    if (snake.segments[0].x == frog.position.x && snake.segments[0].y == frog.position.y) {
        snake.length++;
        frog.position.x = rand() % (SCREEN_WIDTH / CELL_SIZE) * CELL_SIZE;
        frog.position.y = rand() % (SCREEN_HEIGHT / CELL_SIZE) * CELL_SIZE;
        eatenFrogs++;
        if (eatenFrogs >= frogCount) {
            gameOver = true;
        }
    }
}


void render(int snakeColorR, int snakeColorG, int snakeColorB) {
    if (gameOver) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        return;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, snakeColorR, snakeColorG, snakeColorB, 255);
    for (int i = 0; i < snake.length; ++i) {
        SDL_Rect segmentRect = { snake.segments[i].x, snake.segments[i].y, CELL_SIZE, CELL_SIZE };
        SDL_RenderFillRect(renderer, &segmentRect);
    }

    if (frog.exists) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect frogRect = { frog.position.x, frog.position.y, CELL_SIZE, CELL_SIZE };
        SDL_RenderFillRect(renderer, &frogRect);
    }

    SDL_RenderPresent(renderer);
}

int startGame(int currentLevel) {
    initializeGame();
    int snakeSpeed = levels[currentLevel].snakeSpeed;
    int snakeColorR = levels[currentLevel].snakeColorR;
    int snakeColorG = levels[currentLevel].snakeColorG;
    int snakeColorB = levels[currentLevel].snakeColorB;
    gameOver = false;

    bool quit = false;
    Uint32 lastMoveTime = 0;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN) {
                handleInput(e);
            }
        }

        Uint32 currentTime = SDL_GetTicks();
        if (!gameOver && currentTime - lastMoveTime >= snakeSpeed) {
            update(levels[currentLevel].frogCount, snakeSpeed);
            lastMoveTime = currentTime;
        }

        render(snakeColorR, snakeColorG, snakeColorB);

        if (gameOver && currentLevel + 1 < levelCount) {
            printStats(currentLevel + 1, eatenFrogs);
            return currentLevel + 1;
        }

        SDL_Delay(10);
    }

    return -1;
}

void printStats(int level, int frogsEaten) {
    printf("You passed level %d. Eaten frogs: %d. Points: %d\n", level, frogsEaten, (level+1)*frogsEaten);
}
