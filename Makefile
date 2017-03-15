.PHONY: all

all: othello sample/libhuman.so

othello: othello-interface.c othello-ai.h othello-def.h
	gcc othello-interface.c -l dl -o othello

sample/libhuman.so: sample/human.c
	gcc -shared -fPIC sample/human.c -o sample/libhuman.so
