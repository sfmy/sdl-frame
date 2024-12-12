#!/bin/bash
# gcc "$1" `pkg-config --cflags --libs sdl2 sdl2_image sdl2_mixer sdl2_ttf`  
gcc -o game `ls *.c` `pkg-config --cflags --libs sdl2 sdl2_image sdl2_mixer sdl2_ttf`  
[[ $? -eq 0 ]] && ./game

