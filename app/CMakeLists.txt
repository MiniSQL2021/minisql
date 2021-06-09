add_executable(app main.cpp)

target_include_directories(app PUBLIC ${CMAKE_SOURCE_DIR}/include/api)

target_link_libraries(app PUBLIC api)

target_compile_features(app PUBLIC cxx_std_17)