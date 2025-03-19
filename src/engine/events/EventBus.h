#ifndef EVENTBUS_H
#define EVENTBUS_H

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_stdinc.h"
#include <functional>
#include <map>


using BusEventType = Uint32;
using BusCallback = std::function<void(const SDL_Event &)>;
using CallbackID = int;


class EventBus
{
public:
    EventBus() = default;
    ~EventBus() = default;

    void emit(const SDL_Event &event) {
        if (callbacks.find(event.type) != callbacks.end()) {
            for (auto &callback : callbacks[event.type]) {
                callback.second(event);
            }
        }
    }

    CallbackID subscribe(Uint32 type, std::function<void(const SDL_Event &)> callback) {
        CallbackID id = nextID++;
        callbacks[type][id] = callback;
        return id;
    }

    template <typename T>
    int subscribe(Uint32 type, void (T::*method)(const SDL_Event &), T *instance) {
        CallbackID id = nextID++;
        auto wrappedCallback = [method, instance](const SDL_Event &event) {
            (instance->*method)(event);
        };
        callbacks[type][id] = wrappedCallback;
        return id;
    }

    bool unsubscribe(CallbackID id) {
        for (auto &pair : callbacks) {
            if (pair.second.find(id) != pair.second.end()) {
                pair.second.erase(id);
                return true;
            }
        }
        return false;
    }

private:
    CallbackID nextID = 0;
    std::map<BusEventType, std::map<CallbackID, BusCallback>> callbacks = {};
};

inline EventBus GlobalEventBus = EventBus();

#endif