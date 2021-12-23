﻿using System.Runtime.InteropServices;

namespace LeafDraw
{
    public static class Draw
    {
        [StructLayout(LayoutKind.Sequential)]
        public struct ContextOptions
        {
            public ushort width;
            public ushort height;
            public float xMin;
            public float xMax;
            public float yMin;
            public float yMax;
            public float fontSize;
        }
        
        [StructLayout(LayoutKind.Sequential)]
        public struct Color
        {
            public byte r;
            public byte g;
            public byte b;
            public byte a;
        }
        
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void RenderFunction(float deltaTime);

        [DllImport("LeafDraw", CallingConvention = CallingConvention.Cdecl)]
        public static extern int StartContext(ContextOptions contextOptions);
        
        [DllImport("LeafDraw", CallingConvention = CallingConvention.Cdecl)]
        public static extern void AddRenderFunction(RenderFunction renderFunction);
        
        [DllImport("LeafDraw", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetColor(Color color);

        [DllImport("LeafDraw", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Line(float x0, float y0, float x1, float y1);
        
        [DllImport("LeafDraw", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Vector(float x0, float y0, float x1, float y1);
        
        [DllImport("LeafDraw", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Dot(float x, float y, float radius = 4);

        [DllImport("LeafDraw", CallingConvention = CallingConvention.Cdecl)]
        public static extern void TextLeft(float x, float y, string text);
        
        [DllImport("LeafDraw", CallingConvention = CallingConvention.Cdecl)]
        public static extern void TextRight(float x, float y, string text);
        
        [DllImport("LeafDraw", CallingConvention = CallingConvention.Cdecl)]
        public static extern void TextCenter(float x, float y, string text);
    }
}
