#! /bin/bash

rm -rf ./build
cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build
./build/bin/zide
