list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(ExternalAntlr4Cpp)

add_library(interpreter Interpreter.cpp
        antlr/SQLLexer.cpp antlr/SQLParser.cpp antlr/SQLVisitor.cpp antlr/SQLBaseVisitor.cpp
        parser/QueryParser.cpp parser/Clause.cpp parser/Expression.cpp
        parser/SmallParts.cpp parser/Statements.cpp)

target_include_directories(interpreter PUBLIC ${CMAKE_SOURCE_DIR}/include/interpreter)
target_include_directories(interpreter PUBLIC ${CMAKE_SOURCE_DIR}/include/interpreter/antlr)
target_include_directories(interpreter PUBLIC ${CMAKE_SOURCE_DIR}/include/interpreter/query)
target_include_directories(interpreter PUBLIC ${CMAKE_SOURCE_DIR}/include/interpreter/type)
target_include_directories(interpreter PUBLIC ${CMAKE_SOURCE_DIR}/include/interpreter/parser)
target_include_directories(interpreter PUBLIC ${CMAKE_SOURCE_DIR}/include/interpreter/util)
target_include_directories(interpreter PUBLIC ${ANTLR4_INCLUDE_DIRS})

target_link_libraries(interpreter PUBLIC antlr4_static)

target_compile_features(interpreter PUBLIC cxx_std_17)