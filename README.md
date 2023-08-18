# Pong_SDL2

## About
This is a reproduction of classic Atari video-game Pong using SDL2.
I wanted to build from "scratch" the game using the bare minimum to 
understand the basic logic of a game, from the game loop to handling
input.
I only tested this on Windows (might not work with all OS and compilers)
and you can find the zip folder containing the .exe file in /pkg.

## Build
To correctly build the project you will need to import to this project (or use a package manager):
- SDL2
- SDL2_image
- SDL2_ttf
- SDL2_mixer
- 
To build just do:
```
    cmake .
    mkdir build
    cd build
    cmake --build .
```
To install the game do:
```
    cd build
    cmake --install .
```
