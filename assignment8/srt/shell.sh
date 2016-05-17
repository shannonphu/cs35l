#! /bin/bash

make clean
make
gcc -g -O0 -std=gnu99 -Wall -Wextra -Wno-unused-parameter   -c -o raymath.o raymath.c
gcc -g -O0 -std=gnu99 -Wall -Wextra -Wno-unused-parameter   -c -o shaders.o shaders.c
gcc -g -O0 -std=gnu99 -Wall -Wextra -Wno-unused-parameter -o srt main.o raymath.o shaders.o -lm -lpthread
