cmake_minimum_required(VERSION 3.16)
project(renderer)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

find_package(SDL3 REQUIRED)
find_package(SDL3_ttf REQUIRED)

add_executable(renderer
    src/main.c
    src/render.c
    src/raycast.c
    src/vector4.c
    src/input.c
)

target_link_libraries(renderer PRIVATE SDL3::SDL3 SDL3_ttf::SDL3_ttf)