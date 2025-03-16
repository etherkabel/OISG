#ifndef BUTTON_H
#define BUTTON_H

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_rect.h"
#include <iostream>
#include "../EventBus.h"
#include "SDL3/SDL_render.h"

class Button {
public:
    Button(const SDL_FRect& rect) : rect(rect) {
        EventBus::instance().subscribe(SDL_EVENT_MOUSE_BUTTON_DOWN, &Button::clickEvent, this);
        EventBus::instance().subscribe(SDL_EVENT_MOUSE_MOTION, &Button::mouseMoveEvent, this);
    }

    void clickEvent(const SDL_Event& event) {
        SDL_FPoint mousePos = {event.button.x, event.button.y};
        if (SDL_PointInRectFloat(&mousePos, &rect)) {
            std::cout << "Button clicked!" << std::endl;
        }
    }

    void mouseMoveEvent(const SDL_Event& event) {
        SDL_FPoint mousePos = {event.motion.x, event.motion.y};
        mouseOver = SDL_PointInRectFloat(&mousePos, &rect);
    }

    void render(SDL_Renderer* renderer) {
        if (mouseOver) {
            SDL_SetRenderDrawColor(renderer, 112, 128, 144, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, 96, 112, 128, 255);
        }
        SDL_RenderFillRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, 192, 192, 192, 255);
        SDL_RenderRect(renderer, &rect);
    }

private:
    SDL_FRect rect;
    bool mouseOver = false;
};

#endif