#include <SDL3/SDL.h>
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_messagebox.h"
#include "SDL3/SDL_render.h"
#include <cstddef>
#include <iostream>
#include <cstdio>
#include "SDL3/SDL_timer.h"
#include "utils/Clock.h"
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_init.h>
#include <string>
#include "SDL3_ttf/SDL_ttf.h"
#include "utils/Logger.h"
#include "engine/gui/Button.h"
#include "engine/events//EventBus.h"

using namespace std;

int main() {
    Logger log("main", Logger::DEBUG);
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        log.stream(Logger::FATAL) << "SDL Initialization failed: " << SDL_GetError() << endl;
    }

    TTF_Init();
    int start = SDL_GetTicks();
    SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0");
    SDL_Window *win = SDL_CreateWindow("Test", 640, 480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN);
    if (!win) {
        log.stream(Logger::FATAL) << "Window creation failed: " << SDL_GetError() << endl;
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Error", SDL_GetError(), NULL);
        return 1;
    }
    SDL_Renderer *ren = SDL_CreateRenderer(win, "vulkan");

    log.stream(Logger::INFO) << "Using video: " << SDL_GetCurrentVideoDriver() << endl;
    if (!ren) {
        log.stream(Logger::FATAL) << "Renderer creation failed: " << SDL_GetError() << endl;
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Error", SDL_GetError(), NULL);
        return 1;
    }
    log.stream(Logger::INFO) << "Using renderer: " << SDL_GetRendererName(ren) << endl;
    if (!SDL_SetRenderVSync(ren, true)) {
        log.stream(Logger::WARN) << "VSync not supported: " << SDL_GetError() << endl;
    }
    SDL_ShowWindow(win);
    log.debug("Initialization complete");
    log.stream(Logger::INFO) << "SDL initialization took " << SDL_GetTicks() - start << "ms" << endl;

    Button b({256, 224, 128, 32});
    b.onClick.connect([&log](const Button& b) {
        log.info("Button clicked");
    });
    Clock clk(120);
    EventBus &bus = EventBus::instance();
    SDL_Event e;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&e)) {
            bus.emit(e);
            switch (e.type) {
                case SDL_EVENT_QUIT: running = false; break;
            }
        }
        SDL_SetRenderDrawColor(ren, 0, 64, 128, 255);
        SDL_RenderClear(ren);
        b.render(ren);
        SDL_RenderPresent(ren);
        clk.update();
    }

    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(ren);
    SDL_Quit();

    log.debug("Shutting down");

    return 0;
}
