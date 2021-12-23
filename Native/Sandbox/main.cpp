#include "LeafDraw.hpp"
#include "iostream"

float y = 0;

void MyRender(float deltaTime)
{
    y += deltaTime * 0.25f;
//    LeafDraw::Line(-1, y, 0, 0);
//    LeafDraw::TextCenter(0, 0, "Hello world!");
//    LeafDraw::Dot(0, 0);
    LeafDraw::Vector(0, 0, 0.25f, 0.f);
}

int main()
{
    auto contextOptions = LeafDraw::ContextOptions {
        .width = 800,
        .height = 800,
        .xMin = -1,
        .xMax = 1,
        .yMin = 1,
        .yMax = -1,
    };
    LeafDraw::AddRenderFunction(MyRender);
    LeafDraw::StartContext(contextOptions);
    return 0;
}
