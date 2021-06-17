add_library(api API.cpp Adapter.cpp APIHelpers.cpp
        helper/Util.cpp helper/Condition.cpp
        ${CMAKE_SOURCE_DIR}/include/api/helper/Interval.hpp)

add_library(api-util helper/Condition.cpp ${CMAKE_SOURCE_DIR}/include/api/helper/Interval.hpp)

target_include_directories(api PRIVATE ${CMAKE_SOURCE_DIR}/include/api)
target_include_directories(api PRIVATE ${CMAKE_SOURCE_DIR}/include/api/helper)
target_include_directories(api PUBLIC ${CMAKE_SOURCE_DIR}/include/record-manager)
target_include_directories(api PUBLIC ${CMAKE_SOURCE_DIR}/include/catalog-manager)
target_include_directories(api PUBLIC ${CMAKE_SOURCE_DIR}/include/buffer-manager)

target_include_directories(api-util PRIVATE ${CMAKE_SOURCE_DIR}/include/api)
target_include_directories(api-util PRIVATE ${CMAKE_SOURCE_DIR}/include/api/helper)

target_compile_features(api PRIVATE cxx_std_20)
target_compile_features(api-util PRIVATE cxx_std_20)
