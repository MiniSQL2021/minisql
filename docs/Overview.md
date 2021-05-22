# MiniSQL

## Project Structure

- `include` folder contains header files of all modules. These header files are meant to be shared across modules.
- `src` folder contains source files of modules. Each module is placed in a subfolder and targets a library, with its own building instruction `CMakeLists.txt`.
- `app` folder contain source files of main executable, also with CMake config.
- `test` folder contain source files of tests, also with CMake config.
- `cmake` folder contain CMake config for building external packages.
