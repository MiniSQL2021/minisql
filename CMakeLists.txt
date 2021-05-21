# minimum required CMAKE version
cmake_minimum_required(VERSION 3.19)

project(miniSQL VERSION 0.1.0
                DESCRIPTION "Mini SQL implementation."
                LANGUAGES CXX)

# add_definitions(-DANTLR4CPP_STATIC)

set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(src)