cmake_minimum_required(VERSION 3.24)
project(arkanoid_game_sdl2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -static-libstdc++ -static-libgcc")

set(SDL2_INCLUDE_DIR C:/SDL2_64/include)
set(SDL2_LIB_DIR C:/SDL2_64/lib)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})


file(
        GLOB_RECURSE SOURCES LIST_DIRECTORIES true
        ${CMAKE_CURRENT_LIST_DIR}/*.h
        ${CMAKE_CURRENT_LIST_DIR}/sdl_framework_files/*.h
        ${CMAKE_CURRENT_LIST_DIR}/sdl_framework_files/*.cpp
)

add_executable(arkanoid_game_sdl2 main.cpp  ${SOURCES})
set_target_properties(arkanoid_game_sdl2 PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/bin")


target_link_libraries(arkanoid_game_sdl2 mingw32 SDL2main SDL2 SDL2_image zlib1 libjpeg-9 libpng16-16)
