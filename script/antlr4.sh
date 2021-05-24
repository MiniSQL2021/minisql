#!/bin/zsh
cd ./src/interpreter/
java -Xmx500M -cp "/usr/local/lib/antlr-4.9-complete.jar" org.antlr.v4.Tool \
  SQL.g4 -no-listener -visitor -Dlanguage=Cpp -o antlr
mv antlr/*.h ../../include/interpreter/antlr/
