//
// Created by Ramon Brand on 21.12.2021.
//

#include "General.hpp"
#include "Extern.hpp"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL2_gfxPrimitives.h>
#include "iostream"

using namespace std;

namespace LeafDraw
{
    static ContextOptions _contextOptions;
    static float _xSpread;
    static float _ySpread;

    static vector <RenderFunction> _renderFunctions;
    static SDL_Renderer* _renderer;
    static TTF_Font* _font;

    static SDL_Color _color;

    struct Point
    {
        float x;
        float y;
    };

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

            _font = TTF_OpenFont("/Library/Fonts/Arial Unicode.ttf", contextOptions.fontSize);
            if (_font == NULL)
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
            contextOptions.width = windowPixelWidth;
            contextOptions.height = windowPixelHeight;
            _contextOptions = contextOptions;
            auto xDiff = _contextOptions.xMax - _contextOptions.xMin;
            auto yDiff = _contextOptions.yMax - _contextOptions.yMin;
            _xSpread = _contextOptions.width / xDiff;
            _ySpread = _contextOptions.height / yDiff;

            _color = SDL_Color {210,210,210,0 };

            auto lastFrameElapsedTicks = SDL_GetTicks();
            auto isRunning = true;
            while (isRunning)
            {
                auto currentFrameElapsedTicks = SDL_GetTicks();
                auto deltaSeconds = (currentFrameElapsedTicks - lastFrameElapsedTicks) / 1000.f;
                lastFrameElapsedTicks = currentFrameElapsedTicks;

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
            aalineRGBA(_renderer, mappedPoint0.x, mappedPoint0.y, mappedPoint1.x, mappedPoint1.y, 255, 255, 255, 255);
        }

        void TextLeft(float x, float y, char* text)
        {
            auto surface = TTF_RenderText_Solid(_font, text, _color);
            auto texture = SDL_CreateTextureFromSurface(_renderer, surface);

            int width;
            int height;
            SDL_QueryTexture(texture, NULL, NULL, &width, &height);

            auto mappedPoint = WorldToScreen({x, y});
            auto destinationRect = SDL_Rect { (int)mappedPoint.x, (int)mappedPoint.y - height/2,width,height };
            SDL_RenderCopy(_renderer, texture, NULL, &destinationRect);

            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
        }

        void TextRight(float x, float y, char* text)
        {
            auto surface = TTF_RenderText_Solid(_font, text, _color);
            auto texture = SDL_CreateTextureFromSurface(_renderer, surface);

            int width;
            int height;
            SDL_QueryTexture(texture, NULL, NULL, &width, &height);

            auto mappedPoint = WorldToScreen({x, y});
            auto destinationRect = SDL_Rect { (int)mappedPoint.x - width, (int)mappedPoint.y - height/2,width,height };
            SDL_RenderCopy(_renderer, texture, NULL, &destinationRect);

            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
        }

        void TextCenter(float x, float y, char* text)
        {
            auto surface = TTF_RenderText_Solid(_font, text, _color);
            auto texture = SDL_CreateTextureFromSurface(_renderer, surface);

            int width;
            int height;
            SDL_QueryTexture(texture, NULL, NULL, &width, &height);

            auto mappedPoint = WorldToScreen({x, y});
            auto destinationRect = SDL_Rect { (int)mappedPoint.x - width/2, (int)mappedPoint.y - height/2,width,height };
            SDL_RenderCopy(_renderer, texture, NULL, &destinationRect);

            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
        }
    }
}
