#pragma once

#include "SDL.h"

namespace LeafDraw
{
    extern "C"
    {
        typedef void(*RenderFunction)(float);

        int StartContext(ContextOptions contextOptions);
        void AddRenderFunction(RenderFunction renderFunction);

        void SetColor(SDL_Color color);

        void Line(float x0, float y0, float x1, float y1);
        void TextLeft(float x, float y, char* text);
        void TextRight(float x, float y, char* text);
        void TextCenter(float x, float y, char* text);
    }
}