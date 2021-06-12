add_library(catalog-manager CatalogManager.cpp)

target_include_directories(catalog-manager PUBLIC ${CMAKE_SOURCE_DIR}/include/catalog-manager)
target_include_directories(catalog-manager PUBLIC ${CMAKE_SOURCE_DIR}/include/record-manager)

target_compile_features(catalog-manager PUBLIC cxx_std_17)