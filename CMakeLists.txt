# minimum required CMAKE version
CMAKE_MINIMUM_REQUIRED(VERSION 3.7 FATAL_ERROR)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# compiler must be 11 or 14
set(CMAKE_CXX_STANDARD 11)

# required if linking to static library
add_definitions(-DANTLR4CPP_STATIC)

# add external build for antlrcpp
include(ExternalAntlr4Cpp)
# add antrl4cpp artifacts to project environment
include_directories(${ANTLR4_INCLUDE_DIRS})

file (GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file (GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "src/*.h")

# add generated grammar to demo binary target
add_executable(main.out ${SOURCES})
target_link_libraries(main.out antlr4_static)
target_include_directories(main.out PRIVATE ${HEADERS})