cmake_minimum_required(VERSION 3.5)
project(maingl VERSION 0.1)

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)

add_executable(mainGL main.cpp)

target_link_libraries(mainGL GLEW::GLEW)
target_link_libraries(mainGL SDL2::SDL2)
target_link_libraries(mainGL OpenGL::GL)