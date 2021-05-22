add_executable(app main.cpp)

target_include_directories(app PUBLIC ${CMAKE_SOURCE_DIR}/include/interpreter)
target_include_directories(app PUBLIC ${CMAKE_SOURCE_DIR}/include/interpreter/antlr)
target_include_directories(app PUBLIC ${CMAKE_SOURCE_DIR}/include/interpreter/query)
target_include_directories(app PUBLIC ${CMAKE_SOURCE_DIR}/include/interpreter/type)
target_include_directories(app PUBLIC ${CMAKE_SOURCE_DIR}/include/interpreter/parser)
# target_include_directories(interpreter PUBLIC ${ANTLR4_INCLUDE_DIRS})

target_link_libraries(app PUBLIC interpreter)

target_compile_features(app PUBLIC cxx_std_17)