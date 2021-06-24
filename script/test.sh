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

./script/clean.sh

cd ./$CMAKE_FOLDER/app

if [ $# -eq 1 ]; then
  FILE="../../test/example-data/$1"
  if [ -e $FILE ]; then
    echo -e "execfile \"$FILE\"; \n quit;" | ./app
    exit 0
  else
    echo "ERROR: No such file!"
    exit 1
  fi
fi

for file in ../../test/example-data/*.sql; do
  name=$(basename $file)
  base=${name%.sql}
  if [[ $base =~ "1000" ]]; then
    continue
  fi
  echo -n "Testing $name... "
  echo -e "execfile \"$file\"; \n quit;" | ./app >../../test/test-result/"$base.txt" 2>&1
  if [ $? -eq 0 ]; then
    echo "Done."
  else
    echo "FAILED!"
  fi
done
