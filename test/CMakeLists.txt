FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v2.13.1)
FetchContent_MakeAvailable(Catch2)

add_executable(catch-test test.cpp ConditionTest.cpp InterpreterTest.cpp APITest.cpp)

target_include_directories(catch-test PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_compile_features(catch-test PRIVATE cxx_std_20)

target_link_libraries(catch-test PRIVATE api-util interpreter Catch2::Catch2)
