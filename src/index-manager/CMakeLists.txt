add_library(index-manager index-manager.cpp)

target_include_directories(index-manager PUBLIC ${CMAKE_SOURCE_DIR}/include/index-manager)
target_include_directories(index-manager PUBLIC ${CMAKE_SOURCE_DIR}/include/buffer-manager)
target_include_directories(index-manager PUBLIC ${CMAKE_SOURCE_DIR}/include/catalog-manager)

target_compile_features(index-manager PUBLIC cxx_std_17)