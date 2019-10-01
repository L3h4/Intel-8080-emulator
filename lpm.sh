#!/bin/bash

if [[ $1 == "build" ]]; then
  # build ...
  g++ sourceCode/main.cpp sourceCode/8080/intel8080.cpp sourceCode/8080/RAM.cpp -o bin/main
elif [[ $1 == "run" ]]; then
  # run ...
  ./bin/main $2 $3 $4 $5
else
  echo "No such command $1"
fi
