CC := gcc
CFLAGS := -g

.PHONY: all clean

all: libhuman.so

libhuman.so: human.c
	$(CC) -shared -fPIC human.c -o libhuman.so 

clean:
	rm libhuman.so
