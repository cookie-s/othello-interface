#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "othello-interface-loadlib.h"

#include "othello-def.h"

fun_init init_black, init_white;
fun_turn turn_black, turn_white;
Board board;

int valid_point(Point pt) {
    return 0 <= pt.x && pt.x < BOARD_WIDTH && 0 <= pt.y && pt.y < BOARD_HEIGHT;
}

void place(Point place, int color) {
    int dx[] = {-1,0,1,-1,1,-1,0,1}, dy[] = {-1,-1,-1,0,0,1,1,1};

    board[place.y][place.x] = color;
    for(int d=0; d<8; d++) {
        Point pt = {.x = place.x+dx[d], .y = place.y+dy[d]};
        if(!valid_point(pt) || board[place.y+dy[d]][place.x+dx[d]] != OPPONENT(color)) continue;
        while(valid_point(pt) && board[pt.y][pt.x] == OPPONENT(color)) pt.x+=dx[d], pt.y+=dy[d];
        if(valid_point(pt) && board[pt.y][pt.x] == color) {
            Point pt = {.x = place.x+dx[d], .y = place.y+dy[d]};
            while(valid_point(pt) && board[pt.y][pt.x] == OPPONENT(color)) board[pt.y][pt.x] = color, pt.x+=dx[d], pt.y+=dy[d];
        }
    }
}

int can_place(Point place, int color) {
    int dx[] = {-1,0,1,-1,1,-1,0,1}, dy[] = {-1,-1,-1,0,0,1,1,1};
    for(int d=0; d<8; d++) {
        if(board[place.y][place.x] != COLOR_NONE) continue;
        Point pt = {.x = place.x+dx[d], .y = place.y+dy[d]};
        if(!valid_point(pt) || board[place.y+dy[d]][place.x+dx[d]] != OPPONENT(color)) continue;
        while(valid_point(pt) && board[pt.y][pt.x] == OPPONENT(color)) pt.x+=dx[d], pt.y+=dy[d];
        if(valid_point(pt) && board[pt.y][pt.x] == color)
            return 1;
    }
    return 0;
}
int has_move(int color) {
    for(int y=0; y<BOARD_HEIGHT; y++)
        for(int x=0; x<BOARD_WIDTH; x++) {
            Point pt = {.x = x, .y = y};
            if(can_place(pt, color)) return 1;
        }
    return 0;
}


int main(int argc, char**argv) {
    if(argc != 3) {
        printf("Usage:\n");
        printf("\t%s black-libname white-libname\n", argv[0]);
        return 1;
    }

    int load_error = load_functions(argv[1], argv[2]);
    if(load_error) return load_error;

    init_black(COLOR_BLACK);
    init_white(COLOR_WHITE);

    memset(board, 0, sizeof(board));
    board[3][3] = board[4][4] = COLOR_WHITE;
    board[3][4] = board[4][3] = COLOR_BLACK;



    Point last_move = {.x = -1, .y = -1};

    int win = COLOR_NONE, turn = COLOR_BLACK;
    while(1) {
        if(!has_move(COLOR_BLACK) && !has_move(COLOR_WHITE)) break;
        if(has_move(turn)) {
            State state = {.black_count = 0, .white_count = 0};
            for(int y=0; y<BOARD_HEIGHT; y++)
                for(int x=0; x<BOARD_WIDTH; x++)
                    if(board[y][x] == COLOR_BLACK) state.black_count++;
                    else if(board[y][x] == COLOR_WHITE) state.white_count++;
            state.count = state.black_count + state.white_count;
            memcpy(state.board, board, sizeof(board));

            fun_turn nowturn = turn == COLOR_BLACK ? turn_black : turn_white;
            last_move = nowturn(state, turn, last_move);
            if(!can_place(last_move, turn)) {
                puts("noooooooooooooo");
                win = OPPONENT(turn);
                break;
            }

            place(last_move, turn);
        }
        turn = OPPONENT(turn);
    }
    if(win != COLOR_NONE) {
        if(win == COLOR_BLACK)
            puts("BLACK won!");
        else
            puts("WHITE won!");
    }
    else {
        int black_count, white_count;
        for(int y=0; y<BOARD_HEIGHT; y++)
            for(int x=0; x<BOARD_WIDTH; x++)
                if(board[y][x] == COLOR_BLACK) black_count++;
                else if(board[y][x] == COLOR_WHITE) white_count++;
        if(black_count > white_count)
            puts("BLACK won!");
        else if(black_count < white_count)
            puts("WHITE won!");
        else
            puts("DRAW!");
    }
    return 0;
}
