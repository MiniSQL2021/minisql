add_library(buffer-manager buffer_manager.cpp Page.cpp)

target_include_directories(buffer-manager PRIVATE ${CMAKE_SOURCE_DIR}/include/buffer-manager)

target_compile_features(buffer-manager PRIVATE cxx_std_17)
