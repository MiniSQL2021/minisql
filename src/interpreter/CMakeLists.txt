set(CMAKE_POLICY_DEFAULT_CMP0114 NEW)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(ExternalAntlr4Cpp)

add_library(interpreter Interpreter.cpp
        antlr/SQLLexer.cpp antlr/SQLParser.cpp antlr/SQLVisitor.cpp antlr/SQLBaseVisitor.cpp
        parser/QueryParser.cpp parser/Clause.cpp parser/Expression.cpp
        parser/SmallParts.cpp parser/Statements.cpp
        util/Util.cpp)

target_include_directories(interpreter PRIVATE ${CMAKE_SOURCE_DIR}/include/interpreter)
target_include_directories(interpreter PRIVATE ${ANTLR4_INCLUDE_DIRS})

target_link_libraries(interpreter PRIVATE antlr4_static)

target_compile_features(interpreter PRIVATE cxx_std_17)
