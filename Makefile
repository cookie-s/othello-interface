CC := gcc
CFLAGS := -g

.PHONY: all clean linux windows

all: linux

linux: othello-linux
windows: othello-windows

othello-linux: othello-interface.c othello-interface-loadlib-linux.c
	$(CC) othello-interface.c othello-interface-loadlib-linux.c -ldl -o othello 

othello-windows: othello-interface.c othello-interface-loadlib-windows.c
	$(CC) othello-interface.c othello-interface-loadlib-windows.c -o othello 

clean:
	rm othello
	cd sample && make clean
