#!/bin/bash

if [ -e build ]; then
  CMAKE_FOLDER=build
elif [ -e cmake-build-debug ]; then
  CMAKE_FOLDER=cmake-build-debug
else
  echo "ERROR: No CMake build folder."
  exit 1
fi

if [ ! -e test/test-result ]; then
  mkdir test/test-result
fi

cd ./$CMAKE_FOLDER/app
rm database/catalog/*
rm database/data/*
rm database/index/*

for file in ../../test/example-data/*.sql; do
  name=$(basename $file)
  base=${name%.sql}
  if [[ $base =~ "index" ]]; then
    continue
  fi
  echo -n "Testing $name... "
  echo -e "execfile \"$file\"; \n quit;" | ./app >../../test/test-result/"$base.txt" 2>&1
  if [ $? == 0 ]; then
    echo "Done."
  else
    echo "FAILED!"
  fi
done
