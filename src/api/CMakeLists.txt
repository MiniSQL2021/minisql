add_library(api API.cpp Adapter.cpp APIHelpers.cpp
        helper/Util.cpp helper/Interval.cpp helper/Condition.cpp)

target_include_directories(api PRIVATE ${CMAKE_SOURCE_DIR}/include/api)
target_include_directories(api PRIVATE ${CMAKE_SOURCE_DIR}/include/api/helper)
target_include_directories(api PUBLIC ${CMAKE_SOURCE_DIR}/include/record-manager)
target_include_directories(api PUBLIC ${CMAKE_SOURCE_DIR}/include/catalog-manager)
target_include_directories(api PUBLIC ${CMAKE_SOURCE_DIR}/include/buffer-manager)

target_compile_features(api PRIVATE cxx_std_20)
