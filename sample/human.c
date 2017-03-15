#include <stdio.h>

#include "../othello-ai.h"

void init(int color) {
    puts("Game Start!");
    printf("I'm %s.\n\n", color == COLOR_BLACK ? "black" : "white");
    return;
}

Point turn(State state, int color, Point last_move) {
    for(int y=0; y<BOARD_HEIGHT; y++) {
        for(int x=0; x<BOARD_WIDTH; x++) {
            printf("%c", state.board[y][x] == COLOR_BLACK ? 'x' : state.board[y][x] == COLOR_WHITE ? 'o' : ' ');
        }
        puts("");
    }

    Point pt;
    scanf("%d%d",&pt.x,&pt.y);
    return pt;
}
