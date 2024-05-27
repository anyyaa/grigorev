#define _CRT_SECURE_NO_WARNINGS
#include "sdl_utils.h"


SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool initializeSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("������ ��� ������������� SDL: %s\n", SDL_GetError());
        return false;
    }
    window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("������ ��� �������� ����: %s\n", SDL_GetError());
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("������ ��� �������� ���������: %s\n", SDL_GetError());
        return false;
    }

    //if (TTF_Init() == -1) {
    //    printf("������ ��� ������������� SDL_ttf: %s\n", TTF_GetError());
    //    return false;
    //}
    //font = TTF_OpenFont("font.ttf", 28); 
    //if (font == NULL) {
    //    printf("������ ��� �������� ������: %s\n", TTF_GetError());
    //    return false;
    //}

    return true;
}

void closeSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
