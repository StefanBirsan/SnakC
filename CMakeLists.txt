cmake_minimum_required(VERSION 3.27)
project(SnakeC C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)


set(SDL2_PATH "C:/Users/daria/Documents/SDLfile/SDL2-2.30.1/x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(SnakeC main.c
        headers/snake.h
        src/snake.c
        headers/apple.h
        src/apple.c
        headers/render.h
        src/render.c)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})