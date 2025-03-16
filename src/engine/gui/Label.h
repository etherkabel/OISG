#include "SDL3_ttf/SDL_ttf.h"
#include <cstdio>
#include <string>

using namespace std;


class Label {
public:
    Label(TTF_TextEngine* engine, TTF_Font* font) : m_engine(engine) {
        m_text = TTF_CreateText(engine, font, "\0", 0);
    }
    Label(TTF_TextEngine* engine, TTF_Font* font, string text) : m_engine(engine) {
        m_text = TTF_CreateText(engine, font, text.c_str(), 0);
    }

    void setText(string text) {
        TTF_SetTextString(m_text, text.c_str(), 0);
    }
    void setText(char* text, int len) {
        TTF_SetTextString(m_text, text, len);
    }
    void format(const char* fmt, ...) {
        va_list ap;
        va_start(ap, fmt);
        char buf[maxTextLength];
        vsnprintf(buf, sizeof(buf), fmt, ap);
        va_end(ap);
        setText(buf);
    }

    void render(float x, float y) {
        TTF_DrawRendererText(m_text, x, y);
    }

    ~Label() {
        TTF_DestroyText(m_text);
    }

    int maxTextLength = 128;

private:
    TTF_TextEngine* m_engine;
    TTF_Font* m_font;
    TTF_Text* m_text;
};