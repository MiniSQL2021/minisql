# MiniSQL

🚧 Under Construction

## Project Structure

- `include` folder contains header files of all modules. These header files are meant to be shared across modules.
- `src` folder contains source files of modules. Each module is placed in a subfolder and targets a library, with its own building instruction `CMakeLists.txt`.
- `app` folder contains source files of main executable and the `API` module, also with CMake config.
- `test` folder contains source files of tests, also with CMake config.
- `cmake` folder contains CMake config for building external packages.
- `script` folder contains utility scripts.

## Modules

- [API](docs/API.md)
- [Interpreter](docs/Interpreter.md)

## Build

To build the project, run the following commands:

```bash
mkdir build
cmake build
cd build && make
```

## Declaration

This project which serves as a coursework of _Database System Principle_ fully belongs
to [@frothywater](http://github.com/frothywater) and his teammates.

## License

GNU GPLv3.
