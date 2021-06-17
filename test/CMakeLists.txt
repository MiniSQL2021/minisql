FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v2.13.1)
FetchContent_MakeAvailable(Catch2)

add_executable(Catch2_tests test.cpp)

target_compile_features(Catch2_tests PRIVATE cxx_std_20)

target_link_libraries(Catch2_tests PRIVATE api interpreter Catch2::Catch2)
