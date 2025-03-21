#include "SDL3/SDL_timer.h"

class Clock {
public:
    Clock(int framerate) {
        m_start = SDL_GetTicksNS();
        m_lastFrame = m_start;
        m_frameTime = 1'000'000'000 / framerate;
    }

    void update() {
        Uint64 current = SDL_GetTicksNS();
        Uint64 elapsed = current - m_lastFrame;

        if (elapsed < m_frameTime) {
            SDL_DelayNS(m_frameTime - elapsed);
        }

        m_lastFrame = SDL_GetTicksNS();
        m_lastFrameTime = m_lastFrame - current;
    }


    Uint64 getFrameTime() const { return m_lastFrameTime; }

    float getFPS() const {
        if (m_lastFrameTime == 0) return 0.0f;
        return 1'000'000'000.0f / static_cast<float>(m_lastFrameTime);
    }

private:
    Uint64 m_start;
    Uint64 m_lastFrame;
    Uint64 m_frameTime;
    Uint64 m_lastFrameTime;
};
