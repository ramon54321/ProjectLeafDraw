using LeafDraw;

namespace Sandbox
{
    class Program
    {
        static void Main(string[] args)
        {
            Draw.AddRenderFunction((float deltaTime) =>
            {
                Draw.Line(0, 0, 0.5f, 0.5f);
            });
            Draw.StartContext(new Draw.ContextOptions()
            {
                width = 800,
                height = 800,
                xMin = -1,
                xMax = 1,
                yMin = 1,
                yMax = -1,
            });
        }
    }
}