add_executable(Sandbox main.cpp)

target_include_directories(Sandbox PRIVATE "/usr/local/include/SDL2" "/usr/local/Cellar/sdl2/2.0.9/include/SDL2")
target_link_libraries(Sandbox LeafDraw "/usr/local/lib/libSDL2.dylib" "/usr/local/lib/libSDL2_ttf.dylib" "/usr/local/lib/libSDL2_gfx.dylib")
