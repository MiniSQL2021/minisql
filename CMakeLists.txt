cmake_minimum_required(VERSION 3.14)

project(miniSQL VERSION 0.1.0
        DESCRIPTION "Mini SQL implementation."
        LANGUAGES CXX)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_CXX_EXTENSIONS OFF)

    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    include(CTest)
endif ()

include(FetchContent)

add_subdirectory(src)
add_subdirectory(app)

if ((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING)
        AND BUILD_TESTING)
    add_subdirectory(test)
endif ()
