#ifndef _OTHELLO_DEF_
#define _OTHELLO_DEF_

#define COLOR_NONE  0
#define COLOR_WHITE 1
#define COLOR_BLACK 2
#define OPPONENT(col) (col ^ 0b11)

#define BOARD_WIDTH  8
#define BOARD_HEIGHT 8

typedef struct _Point {
    int x, y;
} Point;

typedef int Board[BOARD_HEIGHT][BOARD_WIDTH];

typedef struct _State {
    Board board;
    int black_count, white_count, count;
} State;

typedef void (*fun_init)(int);
typedef Point (*fun_turn)(State,int,Point);

#endif
