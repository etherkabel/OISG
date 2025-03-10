#include <cstdio>
#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_init.h>

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *win = SDL_CreateWindow("Test", 640, 480, 0);
    SDL_Renderer *ren = SDL_CreateRenderer(win, "rend");

    SDL_RenderClear(ren);
    SDL_RenderPresent(ren);

    SDL_Delay(5000);


    return 0;
}
