# minimum required CMAKE version
cmake_minimum_required(VERSION 3.19)

project(miniSQL VERSION 0.1.0
                DESCRIPTION "Mini SQL implementation."
                LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(src)
add_subdirectory(app)