add_library(catalog-manager Catalog_Manager.cpp catalogPage.cpp Attribute.cpp tableInfo.cpp)

target_include_directories(catalog-manager PUBLIC ${CMAKE_SOURCE_DIR}/include/catalog-manager)
target_include_directories(catalog-manager PUBLIC ${CMAKE_SOURCE_DIR}/include/record-manager)
target_include_directories(catalog-manager PUBLIC ${CMAKE_SOURCE_DIR}/include/buffer-manager)

target_compile_features(catalog-manager PUBLIC cxx_std_17)
