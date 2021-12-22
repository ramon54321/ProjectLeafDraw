add_library(LeafDraw SHARED General.hpp LeafDraw.hpp Extern.cpp Extern.hpp)
target_include_directories(LeafDraw PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(LeafDraw PRIVATE "/usr/local/include/SDL2" "/usr/local/Cellar/sdl2/2.0.9/include/SDL2")
target_link_libraries(LeafDraw "/usr/local/lib/libSDL2.dylib" "/usr/local/lib/libSDL2_ttf.dylib" "/usr/local/lib/libSDL2_gfx.dylib")

add_custom_command(TARGET LeafDraw POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:LeafDraw> ${PROJECT_SOURCE_DIR}/bin/$<TARGET_FILE_NAME:LeafDraw>)
