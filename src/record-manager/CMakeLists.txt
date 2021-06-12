add_library(record-manager RecordManager.cpp
        Attribute.cpp tableInfo.cpp tablePage.cpp tuple.cpp)

target_include_directories(record-manager PUBLIC ${CMAKE_SOURCE_DIR}/include/record-manager)
target_include_directories(record-manager PUBLIC ${CMAKE_SOURCE_DIR}/include/catalog-manager)

target_compile_features(record-manager PUBLIC cxx_std_17)