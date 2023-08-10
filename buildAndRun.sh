#!/bin/bash

g++ main.cpp -o main -O1 -Wno-missing-braces -I ./include/ -L ./lib/libraylib.a -lraylib
./main
