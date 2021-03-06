#pragma once

#include "SDL.h"

namespace LeafDraw
{
    extern "C"
    {
        struct Point
        {
            float x;
            float y;
        };

        typedef void(*RenderFunction)(float);

        int StartContext(ContextOptions contextOptions);
        void AddRenderFunction(RenderFunction renderFunction);

        void SetColor(SDL_Color color);

        Point GetMouseWorldPosition();
        bool GetKeyHold(SDL_Scancode scancode);

        void Line(float x0, float y0, float x1, float y1);
        void Vector(float x0, float y0, float x1, float y1);
        void Dot(float x, float y, float radius = 4.f);
        void TextLeft(float x, float y, const char *text);
        void TextRight(float x, float y, const char *text);
        void TextCenter(float x, float y, const char *text);
    }
}