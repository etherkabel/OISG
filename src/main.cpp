#include <SDL3/SDL.h>
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_messagebox.h"
#include "SDL3/SDL_render.h"
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include "SDL3/SDL_timer.h"
#include "engine/drawing/Circle.h"
#include "utils/Clock.h"
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_init.h>
#include <string>
#include "SDL3_ttf/SDL_ttf.h"
#include "utils/Logger.h"
#include "engine/globals.h"

using namespace std;

int main() {
    Logger log("main", Logger::DEBUG);
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        log.stream(Logger::FATAL) << "SDL Initialization failed: " << SDL_GetError() << endl;
    }

    TTF_Init();
    int start = SDL_GetTicks();
    SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0");
    window = SDL_CreateWindow("Test", 640, 480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN);
    if (!window) {
        log.stream(Logger::FATAL) << "Window creation failed: " << SDL_GetError() << endl;
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Error", SDL_GetError(), NULL);
        return 1;
    }
    renderer = SDL_CreateRenderer(window, "vulkan");

    log.stream(Logger::INFO) << "Using video: " << SDL_GetCurrentVideoDriver() << endl;
    if (!renderer) {
        log.stream(Logger::FATAL) << "Renderer creation failed: " << SDL_GetError() << endl;
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Error", SDL_GetError(), NULL);
        return 1;
    }
    log.stream(Logger::INFO) << "Using renderer: " << SDL_GetRendererName(renderer) << endl;
    if (!SDL_SetRenderVSync(renderer, true)) {
        log.stream(Logger::WARN) << "VSync not supported: " << SDL_GetError() << endl;
    }
    textEngine = TTF_CreateRendererTextEngine(renderer);
    TTF_Font *font = TTF_OpenFont("assets/fonts/JetBrainsMonoNL-Regular.ttf", 16);
    SDL_ShowWindow(window);
    log.debug("Initialization complete");
    log.stream(Logger::INFO) << "SDL initialization took " << SDL_GetTicks() - start << "ms" << endl;

    Clock clk(120);

    SDL_Event e;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&e)) {
            GlobalEventBus.emit(e);
            switch (e.type) {
                case SDL_EVENT_QUIT: running = false; break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 64, 128, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        clk.update();
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    log.debug("Shutting down");

    return 0;
}
