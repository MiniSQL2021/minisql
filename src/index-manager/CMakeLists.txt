add_library(index-manager Index.cpp)

target_include_directories(index-manager PRIVATE ${CMAKE_SOURCE_DIR}/include/index-manager)
target_include_directories(index-manager PRIVATE ${CMAKE_SOURCE_DIR}/include/buffer-manager)
target_include_directories(index-manager PRIVATE ${CMAKE_SOURCE_DIR}/include/catalog-manager)

target_compile_features(index-manager PRIVATE cxx_std_17)
