#!/bin/zsh
if [ "$#" -ne 1 ] || ! [ -r "$1" ]; then
  echo "Usage: $0 file1"
  exit 1
fi

x=$(file -bi $1 | grep 'utf' | wc -l)
if [ $x -eq 1 ]; then
  echo "$1 already converted"
else
  echo converting $1 to UTF8
  iconv -f "gb2312" -t "UTF-8" $1 >"$1.new"
  mv -f "$1.new" $1
fi
