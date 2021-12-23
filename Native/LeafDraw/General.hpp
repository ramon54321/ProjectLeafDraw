#pragma once

#include <cstdint>
#include <vector>

namespace LeafDraw
{
    struct ContextOptions
    {
        uint16_t width;
        uint16_t height;
        float xMin;
        float xMax;
        float yMin;
        float yMax;
        float fontSize = 24;
    };
}
