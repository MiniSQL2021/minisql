# MiniSQL

🚧 Under Construction

## Project Structure

- `include` folder contains header files of all modules. These header files are meant to be shared across modules.
- `src` folder contains source files of modules. Each module is placed in a subfolder and targets a library, with its
  own building instruction `CMakeLists.txt`.
- `app` folder contain source files of main executable, also with CMake config.
- `test` folder contain source files of tests, also with CMake config.
- `cmake` folder contain CMake config for building external packages.

## Modules

- [Interpreter](docs/Interpreter.md)

## Declaration

This project which serves as a coursework of _Database System Principle_ fully belongs
to [@frothywater](http://github.com/frothywater) and his teammates.

## License

GNU GPLv3.
