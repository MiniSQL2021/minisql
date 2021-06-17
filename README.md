# MiniSQL

🚧 Under Construction

## Project Structure

- `include` folder contains header files of all modules. These header files are meant to be shared across modules.
- `src` folder contains source files of modules. Each module is placed in a subfolder and targets a library, with its
  own `CMakeLists.txt`.
- `app` folder contains source files of main executable.
- `test` folder contains source files of tests.
- `cmake` folder contains CMake config for building external packages.
- `script` folder contains utility scripts.

## Modules

- [API](docs/API.md)
- [Interpreter](docs/Interpreter.md)
- Catalog Manager
- Record Manager
- Index Manager
- Buffer Manager

## Build

To build the project, run the following commands:

```shell
mkdir build
cmake build
cd build && make
```

## Unit Test

This project uses [Catch2](https://github.com/catchorg/Catch2) as its testing framework. Target `catch-test` will build
an executable for testing. After build (as described in the previous section), you can run the following command to
test:

```shell
./test/catch-test
```

## Declaration

This project which serves as a coursework of _Database System Principle_ fully belongs
to [@frothywater](http://github.com/frothywater) and his teammates.

## Dependencies

- [Catch2](https://github.com/catchorg/Catch2): A modern, C++-native, header-only, test framework for unit-tests, TDD
  and BDD
- [ANTLR4](https://github.com/antlr/antlr4): ANother Tool for Language Recognition
- [Tabulate](https://github.com/p-ranav/tabulate): Table Maker for Modern C++

## License

GNU GPLv3.
