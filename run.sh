#!/usr/bin/bash

MAIN_EXEC_FILE=./main
if test -f "$MAIN_EXEC_FILE"; then
	rm $MAIN_EXEC_FILE;
fi

g++ --std=c++14 matrix.cpp main.cpp -g -o main;

if test -f "$MAIN_EXEC_FILE"; then
	./main;
fi

