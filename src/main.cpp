#include "SDL3/SDL_blendmode.h"
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_keyboard.h"
#include "SDL3/SDL_messagebox.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include <cstddef>
#include <cstdio>
#include "SDL3/SDL_scancode.h"
#include "SDL3/SDL_surface.h"
#include "SDL3/SDL_timer.h"
#include "utils/Clock.h"
#include "SDL3_image/SDL_image.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_init.h>
#include "utils/Logger.h"

int main() {
    Logger log("main", Logger::DEBUG);
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        log.stream(Logger::FATAL) << "SDL Initialization failed: " << SDL_GetError() << endl;
    }
    int start = SDL_GetTicks();
    SDL_Window *win = SDL_CreateWindow("Test", 640, 480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN);
    if (!win) {
        log.stream(Logger::FATAL) << "Window CREATION!!!!!! failed: " << SDL_GetError() << endl;
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Error", SDL_GetError(), NULL);
        return 1;
    }
    SDL_Renderer *ren = SDL_CreateRenderer(win, NULL);
    if (!ren) {
        log.stream(Logger::FATAL) << "Renderer CREATION!!!!!! failed: " << SDL_GetError() << endl;
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Error", SDL_GetError(), NULL);
        return 1;
    }
    log.stream(Logger::INFO) << "Using renderer: " << SDL_GetRendererName(ren) << endl;
    if (!SDL_SetRenderVSync(ren, false)) {
        log.stream(Logger::WARN) << "VSync not supported: " << SDL_GetError() << endl;
    }
    SDL_ShowWindow(win);
    log.debug("Initialization complete");
    log.stream(Logger::INFO) << "SDL initialization took " << SDL_GetTicks() - start << "ms" << endl;

    SDL_Surface *bmp = IMG_Load("assets/bottle.png");
    if (!bmp) {
        log.stream(Logger::FATAL) << "Image load failed: " << SDL_GetError() << endl;
        return 1;
    }
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
    SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_NEAREST);
    SDL_DestroySurface(bmp);
    SDL_FRect rect{};
    SDL_GetTextureSize(tex, &rect.w, &rect.h);
    rect.h *= 8;
    rect.w *= 8;
    int numKeys;
    const bool *keys = SDL_GetKeyboardState(&numKeys);
    log.stream(Logger::INFO) << "Number of keys: " << numKeys << endl;

    Clock clk(100000);
    SDL_Event e;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_EVENT_QUIT: running = false; break;
            }
        }
        if (keys[SDL_SCANCODE_UP]) {
            rect.y -= 4;
        } else if (keys[SDL_SCANCODE_DOWN]) {
            rect.y += 4;
        }
        if (keys[SDL_SCANCODE_LEFT]) {
            rect.x -= 4;
        } else if (keys[SDL_SCANCODE_RIGHT]) {
            rect.x += 4;
        }
        SDL_SetRenderDrawColor(ren, 0, 200, 0, 255);
        SDL_RenderClear(ren);
        SDL_RenderTexture(ren, tex, NULL, &rect);
        SDL_RenderPresent(ren);
        clk.update();
        log.stream(Logger::DEBUG) << "FPS: " << clk.getFPS() << " \tFrame time: \t" << clk.getFrameTime() << endl;
    }

    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(ren);
    SDL_Quit();

    log.debug("Shutting down");

    return 0;
}
