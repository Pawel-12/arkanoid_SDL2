cmake_minimum_required(VERSION 3.24)
project(arkanoid_game_sdl2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -static-libstdc++ -static-libgcc")

set(SDL2_INCLUDE_DIR C:/SDL2_64/include)
set(SDL2_LIB_DIR C:/SDL2_64/lib)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})


add_executable(arkanoid_game_sdl2 main.cpp sdl_framework_files/sdl_framework.cpp sdl_framework_files/sdl_framework.h sdl_framework_files/Window.cpp sdl_framework_files/Window.h sdl_framework_files/Sprite.cpp sdl_framework_files/Sprite.h sdl_framework_files/Entity.cpp sdl_framework_files/Entity.h sdl_framework_files/logSDLerr.cpp sdl_framework_files/logSDLerr.h main.h Platform.h Ball.h)

target_link_libraries(arkanoid_game_sdl2 mingw32 SDL2main SDL2 SDL2_image zlib1 libjpeg-9 libpng16-16)