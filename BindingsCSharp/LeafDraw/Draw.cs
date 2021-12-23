using System.Runtime.InteropServices;

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
        
        [StructLayout(LayoutKind.Sequential)]
        public struct Point
        {
	        public float x;
	        public float y;
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
        public static extern Point GetMouseWorldPosition();
        
        [DllImport("LeafDraw", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool GetKeyHold(SdlScancode scancode);

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
        
        public enum SdlScancode
		{
			SdlScancodeUnknown = 0,

			SdlScancodeA = 4,
			SdlScancodeB = 5,
			SdlScancodeC = 6,
			SdlScancodeD = 7,
			SdlScancodeE = 8,
			SdlScancodeF = 9,
			SdlScancodeG = 10,
			SdlScancodeH = 11,
			SdlScancodeI = 12,
			SdlScancodeJ = 13,
			SdlScancodeK = 14,
			SdlScancodeL = 15,
			SdlScancodeM = 16,
			SdlScancodeN = 17,
			SdlScancodeO = 18,
			SdlScancodeP = 19,
			SdlScancodeQ = 20,
			SdlScancodeR = 21,
			SdlScancodeS = 22,
			SdlScancodeT = 23,
			SdlScancodeU = 24,
			SdlScancodeV = 25,
			SdlScancodeW = 26,
			SdlScancodeX = 27,
			SdlScancodeY = 28,
			SdlScancodeZ = 29,

			SdlScancode1 = 30,
			SdlScancode2 = 31,
			SdlScancode3 = 32,
			SdlScancode4 = 33,
			SdlScancode5 = 34,
			SdlScancode6 = 35,
			SdlScancode7 = 36,
			SdlScancode8 = 37,
			SdlScancode9 = 38,
			SdlScancode0 = 39,

			SdlScancodeReturn = 40,
			SdlScancodeEscape = 41,
			SdlScancodeBackspace = 42,
			SdlScancodeTab = 43,
			SdlScancodeSpace = 44,

			SdlScancodeMinus = 45,
			SdlScancodeEquals = 46,
			SdlScancodeLeftbracket = 47,
			SdlScancodeRightbracket = 48,
			SdlScancodeBackslash = 49,
			SdlScancodeNonushash = 50,
			SdlScancodeSemicolon = 51,
			SdlScancodeApostrophe = 52,
			SdlScancodeGrave = 53,
			SdlScancodeComma = 54,
			SdlScancodePeriod = 55,
			SdlScancodeSlash = 56,

			SdlScancodeCapslock = 57,

			SdlScancodeF1 = 58,
			SdlScancodeF2 = 59,
			SdlScancodeF3 = 60,
			SdlScancodeF4 = 61,
			SdlScancodeF5 = 62,
			SdlScancodeF6 = 63,
			SdlScancodeF7 = 64,
			SdlScancodeF8 = 65,
			SdlScancodeF9 = 66,
			SdlScancodeF10 = 67,
			SdlScancodeF11 = 68,
			SdlScancodeF12 = 69,

			SdlScancodePrintscreen = 70,
			SdlScancodeScrolllock = 71,
			SdlScancodePause = 72,
			SdlScancodeInsert = 73,
			SdlScancodeHome = 74,
			SdlScancodePageup = 75,
			SdlScancodeDelete = 76,
			SdlScancodeEnd = 77,
			SdlScancodePagedown = 78,
			SdlScancodeRight = 79,
			SdlScancodeLeft = 80,
			SdlScancodeDown = 81,
			SdlScancodeUp = 82,

			SdlScancodeNumlockclear = 83,
			SdlScancodeKpDivide = 84,
			SdlScancodeKpMultiply = 85,
			SdlScancodeKpMinus = 86,
			SdlScancodeKpPlus = 87,
			SdlScancodeKpEnter = 88,
			SdlScancodeKp1 = 89,
			SdlScancodeKp2 = 90,
			SdlScancodeKp3 = 91,
			SdlScancodeKp4 = 92,
			SdlScancodeKp5 = 93,
			SdlScancodeKp6 = 94,
			SdlScancodeKp7 = 95,
			SdlScancodeKp8 = 96,
			SdlScancodeKp9 = 97,
			SdlScancodeKp0 = 98,
			SdlScancodeKpPeriod = 99,

			SdlScancodeNonusbackslash = 100,
			SdlScancodeApplication = 101,
			SdlScancodePower = 102,
			SdlScancodeKpEquals = 103,
			SdlScancodeF13 = 104,
			SdlScancodeF14 = 105,
			SdlScancodeF15 = 106,
			SdlScancodeF16 = 107,
			SdlScancodeF17 = 108,
			SdlScancodeF18 = 109,
			SdlScancodeF19 = 110,
			SdlScancodeF20 = 111,
			SdlScancodeF21 = 112,
			SdlScancodeF22 = 113,
			SdlScancodeF23 = 114,
			SdlScancodeF24 = 115,
			SdlScancodeExecute = 116,
			SdlScancodeHelp = 117,
			SdlScancodeMenu = 118,
			SdlScancodeSelect = 119,
			SdlScancodeStop = 120,
			SdlScancodeAgain = 121,
			SdlScancodeUndo = 122,
			SdlScancodeCut = 123,
			SdlScancodeCopy = 124,
			SdlScancodePaste = 125,
			SdlScancodeFind = 126,
			SdlScancodeMute = 127,
			SdlScancodeVolumeup = 128,
			SdlScancodeVolumedown = 129,
			SdlScancodeLockingcapslock = 130,
			SdlScancodeLockingnumlock = 131,
			SdlScancodeLockingscrolllock = 132,
			SdlScancodeKpComma = 133,
			SdlScancodeKpEqualsas400 = 134,

			SdlScancodeInternational1 = 135,
			SdlScancodeInternational2 = 136,
			SdlScancodeInternational3 = 137,
			SdlScancodeInternational4 = 138,
			SdlScancodeInternational5 = 139,
			SdlScancodeInternational6 = 140,
			SdlScancodeInternational7 = 141,
			SdlScancodeInternational8 = 142,
			SdlScancodeInternational9 = 143,
			SdlScancodeLang1 = 144,
			SdlScancodeLang2 = 145,
			SdlScancodeLang3 = 146,
			SdlScancodeLang4 = 147,
			SdlScancodeLang5 = 148,
			SdlScancodeLang6 = 149,
			SdlScancodeLang7 = 150,
			SdlScancodeLang8 = 151,
			SdlScancodeLang9 = 152,

			SdlScancodeAlterase = 153,
			SdlScancodeSysreq = 154,
			SdlScancodeCancel = 155,
			SdlScancodeClear = 156,
			SdlScancodePrior = 157,
			SdlScancodeReturn2 = 158,
			SdlScancodeSeparator = 159,
			SdlScancodeOut = 160,
			SdlScancodeOper = 161,
			SdlScancodeClearagain = 162,
			SdlScancodeCrsel = 163,
			SdlScancodeExsel = 164,

			SdlScancodeKp00 = 176,
			SdlScancodeKp000 = 177,
			SdlScancodeThousandsseparator = 178,
			SdlScancodeDecimalseparator = 179,
			SdlScancodeCurrencyunit = 180,
			SdlScancodeCurrencysubunit = 181,
			SdlScancodeKpLeftparen = 182,
			SdlScancodeKpRightparen = 183,
			SdlScancodeKpLeftbrace = 184,
			SdlScancodeKpRightbrace = 185,
			SdlScancodeKpTab = 186,
			SdlScancodeKpBackspace = 187,
			SdlScancodeKpA = 188,
			SdlScancodeKpB = 189,
			SdlScancodeKpC = 190,
			SdlScancodeKpD = 191,
			SdlScancodeKpE = 192,
			SdlScancodeKpF = 193,
			SdlScancodeKpXor = 194,
			SdlScancodeKpPower = 195,
			SdlScancodeKpPercent = 196,
			SdlScancodeKpLess = 197,
			SdlScancodeKpGreater = 198,
			SdlScancodeKpAmpersand = 199,
			SdlScancodeKpDblampersand = 200,
			SdlScancodeKpVerticalbar = 201,
			SdlScancodeKpDblverticalbar = 202,
			SdlScancodeKpColon = 203,
			SdlScancodeKpHash = 204,
			SdlScancodeKpSpace = 205,
			SdlScancodeKpAt = 206,
			SdlScancodeKpExclam = 207,
			SdlScancodeKpMemstore = 208,
			SdlScancodeKpMemrecall = 209,
			SdlScancodeKpMemclear = 210,
			SdlScancodeKpMemadd = 211,
			SdlScancodeKpMemsubtract = 212,
			SdlScancodeKpMemmultiply = 213,
			SdlScancodeKpMemdivide = 214,
			SdlScancodeKpPlusminus = 215,
			SdlScancodeKpClear = 216,
			SdlScancodeKpClearentry = 217,
			SdlScancodeKpBinary = 218,
			SdlScancodeKpOctal = 219,
			SdlScancodeKpDecimal = 220,
			SdlScancodeKpHexadecimal = 221,

			SdlScancodeLctrl = 224,
			SdlScancodeLshift = 225,
			SdlScancodeLalt = 226,
			SdlScancodeLgui = 227,
			SdlScancodeRctrl = 228,
			SdlScancodeRshift = 229,
			SdlScancodeRalt = 230,
			SdlScancodeRgui = 231,

			SdlScancodeMode = 257,

			SdlScancodeAudionext = 258,
			SdlScancodeAudioprev = 259,
			SdlScancodeAudiostop = 260,
			SdlScancodeAudioplay = 261,
			SdlScancodeAudiomute = 262,
			SdlScancodeMediaselect = 263,
			SdlScancodeWww = 264,
			SdlScancodeMail = 265,
			SdlScancodeCalculator = 266,
			SdlScancodeComputer = 267,
			SdlScancodeAcSearch = 268,
			SdlScancodeAcHome = 269,
			SdlScancodeAcBack = 270,
			SdlScancodeAcForward = 271,
			SdlScancodeAcStop = 272,
			SdlScancodeAcRefresh = 273,
			SdlScancodeAcBookmarks = 274,

			SdlScancodeBrightnessdown = 275,
			SdlScancodeBrightnessup = 276,
			SdlScancodeDisplayswitch = 277,
			SdlScancodeKbdillumtoggle = 278,
			SdlScancodeKbdillumdown = 279,
			SdlScancodeKbdillumup = 280,
			SdlScancodeEject = 281,
			SdlScancodeSleep = 282,
			SdlScancodeApp1 = 283,
			SdlScancodeApp2 = 284,
			SdlScancodeAudiorewind = 285,
			SdlScancodeAudiofastforward = 286,
		}
    }
}
