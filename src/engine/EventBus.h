#ifndef EVENTBUS_H
#define EVENTBUS_H

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_stdinc.h"
#include <functional>
#include <map>


class EventBus
{
public:
    EventBus() = default;
    ~EventBus() = default;

    void emit(const SDL_Event &event) {
        auto range = callbacks.equal_range(event.type);
        if (range.first == range.second) {
            return;
        }
        for (auto it = range.first; it != range.second; ++it) {
            it->second(event);
        }
    }
    void subscribe(Uint32 type, std::function<void(const SDL_Event &)> callback) {
        callbacks.insert(std::make_pair(type, callback));
    }

    template <typename T>
    void subscribe(Uint32 type, void (T::*method)(const SDL_Event &), T *instance) {
        callbacks.insert(std::make_pair(type, [method, instance](const SDL_Event &event) {
            (instance->*method)(event);
        }));
    }
    
    static EventBus &instance() {
        static EventBus instance;
        return instance;
    }

    EventBus(const EventBus &) = delete;
    EventBus &operator=(const EventBus &) = delete;

private:
    std::multimap<Uint32, std::function<void(const SDL_Event &)>> callbacks{};
};

#endif