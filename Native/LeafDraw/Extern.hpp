#pragma once

namespace LeafDraw
{
    extern "C"
    {
        typedef void(*RenderFunction)(float);

        int StartContext(ContextOptions contextOptions);
        void AddRenderFunction(RenderFunction renderFunction);

        void Line(float x0, float y0, float x1, float y1);
    }
}