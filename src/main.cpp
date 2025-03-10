#include "SDL3/SDL_error.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_render.h"
#include <cstdio>
#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_init.h>
#include "SDL3/SDL_timer.h"
#include "utils/Logger.h"
#include <iostream>

int main() {
    Logger log("main", Logger::DEBUG);
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *win = SDL_CreateWindow("Test", 640, 480, SDL_WINDOW_RESIZABLE);
    if (!win) {
        log.stream(Logger::FATAL) << "Window CREATION!!!!!! failed" << SDL_GetError() << endl;
    }
    SDL_Renderer *ren = SDL_CreateRenderer(win, NULL);
    if (!ren) {
        log.stream(Logger::FATAL) << "Renderer CREATION!!!!!! failed" << SDL_GetError() << endl;
    }
    log.debug("Initialization complete");

    SDL_Event e;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_EVENT_QUIT: running = false; break;
                case SDL_EVENT_WINDOW_RESIZED: {
                    log.stream(Logger::INFO) << "Window resized to " << e.window.data1 << "x" << e.window.data2 << endl;
                }
            }
        }
        SDL_SetRenderDrawColor(ren, 0, 200, 0, 255);
        SDL_RenderClear(ren);
        SDL_RenderPresent(ren);
        SDL_Delay(10);
    }

    return 0;
}
