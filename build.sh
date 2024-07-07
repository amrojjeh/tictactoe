#/bin/sh

echo compiling
clang -Iinclude -lm -lX11 glad.c glfw-3.4/src/*.c main.c -Wall -D _GLFW_X11
