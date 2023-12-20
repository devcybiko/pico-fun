#!/bin/bash -v 
set -e
rm -rf build
mkdir -p build
cd build
cmake ../hello_world
make
