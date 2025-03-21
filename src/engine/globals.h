#ifndef GLOBALS_H
#define GLOBALS_H

#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "events/EventBus.h"

inline EventBus GlobalEventBus = EventBus();
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern TTF_TextEngine *textEngine;

#endif