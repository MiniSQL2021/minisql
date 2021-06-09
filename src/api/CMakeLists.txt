add_library(api API.cpp)

target_include_directories(api PUBLIC ${CMAKE_SOURCE_DIR}/include/api)
target_include_directories(api PUBLIC ${CMAKE_SOURCE_DIR}/include/interpreter)

target_link_libraries(api PUBLIC interpreter)

target_compile_features(api PUBLIC cxx_std_17)