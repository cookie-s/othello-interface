CC := gcc
CFLAGS := -g

.PHONY: all clean

all: libhuman.so libothellovs.so

libhuman.so: human.c
	$(CC) -shared -fPIC human.c -o libhuman.so 

libothellovs.so: othello_vs-interface.c
	$(CC) -shared -fPIC othello_vs-interface.c -o libothellovs.so

clean:
	rm libhuman.so
