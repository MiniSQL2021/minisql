FetchContent_Declare(
        tabulate
        GIT_REPOSITORY https://github.com/p-ranav/tabulate
        GIT_TAG v1.4)
FetchContent_MakeAvailable(tabulate)

add_library(api API.cpp Checking.cpp Helpers.cpp IndexRelated.cpp Selection.cpp Adapter.cpp
        helper/API_Util.cpp helper/Condition.cpp)

target_include_directories(api PRIVATE ${CMAKE_SOURCE_DIR}/include/api)
target_include_directories(api PRIVATE ${CMAKE_SOURCE_DIR}/include/api/helper)
target_include_directories(api PRIVATE ${CMAKE_SOURCE_DIR}/include/catalog-manager)
target_include_directories(api PRIVATE ${CMAKE_SOURCE_DIR}/include/record-manager)
target_include_directories(api PRIVATE ${CMAKE_SOURCE_DIR}/include/index-manager)
target_include_directories(api PRIVATE ${CMAKE_SOURCE_DIR}/include/buffer-manager)
target_include_directories(api PRIVATE ${TABULATE_INCLUDE_DIR})

target_link_libraries(api PRIVATE tabulate::tabulate)

target_compile_features(api PRIVATE cxx_std_20)

add_library(api-util helper/Condition.cpp)
target_include_directories(api-util PRIVATE ${CMAKE_SOURCE_DIR}/include/api)
target_compile_features(api-util PRIVATE cxx_std_20)
