add_executable(app main.cpp)

target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR}/app)
target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR}/include/api)

target_link_libraries(app PRIVATE api interpreter catalog-manager record-manager index-manager buffer-manager)

target_compile_features(app PRIVATE cxx_std_20)
