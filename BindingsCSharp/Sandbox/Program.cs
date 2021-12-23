using System;
using LeafDraw;

namespace Sandbox
{
    class Program
    {
        private static readonly Draw.Color White = new()
        {
            r = 210,
            g = 210,
            b = 210,
            a = 255,
        };
        private static readonly Draw.Color Red = new()
        {
            r = 255,
            g = 128,
            b = 128,
            a = 255,
        };
        
        static void Main(string[] args)
        {
            Draw.AddRenderFunction((float deltaTime) =>
            {
                Draw.SetColor(White);
                Draw.Line(0, 0, 0.5f, 0.5f);
                Draw.TextRight(0, 0, "Hello from the other side!");
                Draw.Dot(0, -0.1f);
                Draw.Dot(0, -0.2f, 8);
                if (Draw.GetKeyHold(Draw.SdlScancode.SdlScancode5) && Draw.GetMouseWorldPosition().x < 0)
                {
                    Draw.SetColor(Red);
                    Draw.Dot(0, -0.4f, 8);
                    Draw.Vector(-1, -1, 0, -0.25f);
                }
            });
            Draw.StartContext(new Draw.ContextOptions()
            {
                width = 800,
                height = 800,
                xMin = -1,
                xMax = 1,
                yMin = 1,
                yMax = -1,
                fontSize = 24,
            });
        }
    }
}