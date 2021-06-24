#!/bin/bash

if [ -e build ]; then
  CMAKE_FOLDER=build
elif [ -e cmake-build-debug ]; then
  CMAKE_FOLDER=cmake-build-debug
else
  echo "ERROR: No CMake build folder."
  exit 1
fi

rm $CMAKE_FOLDER/app/database/catalog/* >/dev/null 2>&1
rm $CMAKE_FOLDER/app/database/data/* >/dev/null 2>&1
rm $CMAKE_FOLDER/app/database/index/* >/dev/null 2>&1
