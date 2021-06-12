add_executable(app main.cpp API.cpp Adapter.cpp Util.cpp Util.h)

target_include_directories(app PUBLIC ${CMAKE_SOURCE_DIR}/app)
target_include_directories(app PUBLIC ${CMAKE_SOURCE_DIR}/include/interpreter)
target_include_directories(app PUBLIC ${CMAKE_SOURCE_DIR}/include/record-manager)
target_include_directories(app PUBLIC ${CMAKE_SOURCE_DIR}/include/catalog-manager)
target_include_directories(app PUBLIC ${CMAKE_SOURCE_DIR}/include/index-manager)

target_link_libraries(app PUBLIC interpreter)
target_link_libraries(app PUBLIC record-manager)
target_link_libraries(app PUBLIC catalog-manager)

target_compile_features(app PUBLIC cxx_std_17)