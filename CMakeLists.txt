cmake_minimum_required(VERSION 3.5)
project(maingl VERSION 0.2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED On)

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)

#add_library(FreeImage /usr/local/Cellar/freeimage/3.18.0/lib/libfreeimage.3.18.0.dylib)
#add_library(FreeImagePlus /usr/local/Cellar/freeimage/3.18.0/lib/libfreeimageplus.3.18.0.dylib)

add_executable(mainGL main.cpp)
target_include_directories(mainGL PUBLIC /usr/local/Cellar/freeimage.3.18.0/include)
target_link_libraries(mainGL /usr/local/Cellar/freeimage/3.18.0/lib/libfreeimage.3.18.0.dylib)
target_link_libraries(mainGL /usr/local/Cellar/freeimage/3.18.0/lib/libfreeimageplus.3.18.0.dylib)

target_link_libraries(mainGL GLEW::GLEW)
target_link_libraries(mainGL SDL2::SDL2)
target_link_libraries(mainGL OpenGL::GL)
