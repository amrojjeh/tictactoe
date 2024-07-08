#/bin/sh

echo compiling
clang -Wall -D _GLFW_X11 -Iinclude -lm -lX11 glad.c glfw-3.4/src/*.c main.c
