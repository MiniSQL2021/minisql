add_executable(app main.cpp API.cpp)

target_include_directories(app PUBLIC ${CMAKE_SOURCE_DIR}/app)
target_include_directories(app PUBLIC ${CMAKE_SOURCE_DIR}/include/interpreter)

target_link_libraries(app PUBLIC interpreter)

target_compile_features(app PUBLIC cxx_std_17)