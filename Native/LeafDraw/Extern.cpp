//
// Created by Ramon Brand on 21.12.2021.
//

#include "General.hpp"
#include "Extern.hpp"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL2_gfxPrimitives.h>
#include "iostream"
#include "math.h"

using namespace std;

namespace LeafDraw
{
    static ContextOptions _contextOptions;
    static float _xSpread;
    static float _ySpread;
    static float _arrowHeadSize;

    static float _mouseX;
    static float _mouseY;
    static const Uint8* _scancodeStates;

    static vector <RenderFunction> _renderFunctions;
    static SDL_Renderer* _renderer;
    static TTF_Font* _font;

    static SDL_Color _color;

    Point ScreenToWorld(Point point)
    {
        return
        {
            .x = point.x / _xSpread + _contextOptions.xMin,
            .y = point.y / _ySpread + _contextOptions.yMin,
        };
    }

    Point WorldToScreen(Point point)
    {
        return
        {
            .x = _xSpread * (point.x - _contextOptions.xMin),
            .y = _ySpread * (point.y - _contextOptions.yMin),
        };
    }

    Point VectorRotate(Point point, float angle)
    {
        return
        {
            .x = point.x * cos(angle) - point.y * sin(angle),
            .y = point.x * sin(angle) + point.y * cos(angle),
        };
    }

    float VectorMagnitude(Point point)
    {
        return sqrt(point.x * point.x + point.y * point.y);
    }

    Point VectorScale(Point point, float scale)
    {
        return
        {
            .x = point.x * scale,
            .y = point.y * scale,
        };
    }

    Point VectorNormalize(Point point)
    {
        auto magnitude = VectorMagnitude(point);
        return VectorScale(point, 1.f / magnitude);
    }

    extern "C"
    {
        void AddRenderFunction(RenderFunction renderFunction)
        {
            _renderFunctions.push_back(renderFunction);
        }

        int StartContext(ContextOptions contextOptions)
        {
            if (SDL_Init(SDL_INIT_VIDEO) != 0)
            {
                cout << "SDL Init failed" << endl;
                cout << SDL_GetError() << endl;
                return 1;
            }

            if (TTF_Init() != 0)
            {
                cout << "SDL TTF Init failed" << endl;
                cout << TTF_GetError() << endl;
                return 2;
            }

            _font = TTF_OpenFont("/Library/Fonts/Arial Unicode.ttf", (int32_t)contextOptions.fontSize);
            if (_font == nullptr)
            {
                cout << "TTF Font Error" << endl;
                cout << TTF_GetError() << endl;
                return 3;
            }

            SDL_Window *window;
            if (SDL_CreateWindowAndRenderer(contextOptions.width, contextOptions.height, SDL_WINDOW_ALLOW_HIGHDPI,
                                            &window, &_renderer) != 0)
            {
                cout << "SDL Window and Renderer Creation failed" << endl;
                cout << SDL_GetError() << endl;
                return 4;
            }

            int windowPixelWidth;
            int windowPixelHeight;
            SDL_GetRendererOutputSize(_renderer, &windowPixelWidth, &windowPixelHeight);
            auto scaling = windowPixelHeight / contextOptions.height;
            contextOptions.width = windowPixelWidth;
            contextOptions.height = windowPixelHeight;
            _contextOptions = contextOptions;
            auto xDiff = _contextOptions.xMax - _contextOptions.xMin;
            auto yDiff = _contextOptions.yMax - _contextOptions.yMin;
            _xSpread = (float)_contextOptions.width / xDiff;
            _ySpread = (float)_contextOptions.height / yDiff;

            _arrowHeadSize = min(abs(xDiff), abs(yDiff)) * 0.01f;

            SetColor(SDL_Color {210,210,210,255 });

            auto lastFrameElapsedTicks = SDL_GetTicks();
            auto isRunning = true;
            while (isRunning)
            {
                auto currentFrameElapsedTicks = SDL_GetTicks();
                auto deltaSeconds = (float)(currentFrameElapsedTicks - lastFrameElapsedTicks) / 1000.f;
                lastFrameElapsedTicks = currentFrameElapsedTicks;

                int mouseX;
                int mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                auto mouseWorldPoint = ScreenToWorld({(float)mouseX * scaling, (float)mouseY * scaling});
                _mouseX = mouseWorldPoint.x;
                _mouseY = mouseWorldPoint.y;

                _scancodeStates = SDL_GetKeyboardState(NULL);

                SDL_SetRenderDrawColor(_renderer, 10, 10, 10, 0);
                SDL_RenderClear(_renderer);

                for (auto &renderFunction : _renderFunctions)
                {
                    renderFunction(deltaSeconds);
                }

                SDL_RenderPresent(_renderer);

                SDL_Event event;
                while (SDL_PollEvent(&event) != 0)
                {
                    if (event.type == SDL_QUIT)
                    {
                        isRunning = false;
                    }
                }
            }

            SDL_DestroyRenderer(_renderer);
            SDL_DestroyWindow(window);
            TTF_CloseFont(_font);
            TTF_Quit();
            SDL_Quit();

            return 0;
        }

        void SetColor(SDL_Color color)
        {
            _color = color;
            SDL_SetRenderDrawColor(_renderer, _color.r, _color.g, _color.b, _color.a);
        }

        void Line(float x0, float y0, float x1, float y1)
        {
            auto mappedPoint0 = WorldToScreen({x0, y0});
            auto mappedPoint1 = WorldToScreen({x1, y1});
            aalineRGBA(_renderer, (int16_t)mappedPoint0.x, (int16_t)mappedPoint0.y, (int16_t)mappedPoint1.x, (int16_t)mappedPoint1.y, _color.r, _color.g, _color.b, _color.a);
        }

        void Vector(float x0, float y0, float x1, float y1)
        {
            Line(x0, y0, x1, y1);
            auto reverseNormalized = VectorScale(VectorNormalize({x1 - x0, y1 - y0 }), -_arrowHeadSize);
            auto leftHead = VectorRotate(reverseNormalized, M_PI_4);
            auto rightHead = VectorRotate(reverseNormalized, -M_PI_4);
            Line(x1, y1, x1 + leftHead.x, y1 + leftHead.y);
            Line(x1, y1, x1 + rightHead.x, y1 + rightHead.y);
        }

        void Dot(float x, float y, float radius)
        {
            auto mappedPoint = WorldToScreen({x, y});
            filledEllipseRGBA(_renderer, (int16_t)mappedPoint.x, (int16_t)mappedPoint.y, (int16_t)radius, (int16_t)radius, _color.r, _color.g, _color.b, _color.a);
        }

        void TextLeft(float x, float y, const char* text)
        {
            auto surface = TTF_RenderText_Solid(_font, text, _color);
            auto texture = SDL_CreateTextureFromSurface(_renderer, surface);

            int width;
            int height;
            SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

            auto mappedPoint = WorldToScreen({x, y});
            auto destinationRect = SDL_Rect { (int32_t)mappedPoint.x, (int32_t)mappedPoint.y - height/2,width,height };
            SDL_RenderCopy(_renderer, texture, nullptr, &destinationRect);

            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
        }

        void TextRight(float x, float y, const char* text)
        {
            auto surface = TTF_RenderText_Solid(_font, text, _color);
            auto texture = SDL_CreateTextureFromSurface(_renderer, surface);

            int width;
            int height;
            SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

            auto mappedPoint = WorldToScreen({x, y});
            auto destinationRect = SDL_Rect { (int32_t)mappedPoint.x - width, (int32_t)mappedPoint.y - height/2,width,height };
            SDL_RenderCopy(_renderer, texture, nullptr, &destinationRect);

            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
        }

        void TextCenter(float x, float y, const char* text)
        {
            auto surface = TTF_RenderText_Solid(_font, text, _color);
            auto texture = SDL_CreateTextureFromSurface(_renderer, surface);

            int width;
            int height;
            SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

            auto mappedPoint = WorldToScreen({x, y});
            auto destinationRect = SDL_Rect { (int32_t)mappedPoint.x - width/2, (int32_t)mappedPoint.y - height/2,width,height };
            SDL_RenderCopy(_renderer, texture, nullptr, &destinationRect);

            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
        }

        Point GetMouseWorldPosition()
        {
            return { _mouseX, _mouseY };
        }

        bool GetKeyHold(SDL_Scancode scancode)
        {
            return _scancodeStates[scancode];
        }
    }
}
