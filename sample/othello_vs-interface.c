#include <stdio.h>
#include <windows.h>

#include "../othello-ai.h"

char cmdline[] = "java aa";
HANDLE readPipe = NULL, writePipe = NULL;

void init(int color) {
    HANDLE childReadHandle, childWriteHandle;
    HANDLE readTemp, writeTemp;

    CreatePipe(&readTemp, &writeTemp, NULL, 0);
    DuplicateHandle(
            GetCurrentProcess(), readTemp,
            GetCurrentProcess(), &childReadHandle,
            0, TRUE, DUPLICATE_SAME_ACCESS);
    CloseHandle(&readTemp);
    writePipe = writeTemp;

    CreatePipe(&readTemp, &writeTemp, NULL, 0);
    DuplicateHandle(
            GetCurrentProcess(), writeTemp,
            GetCurrentProcess(), &childWriteHandle,
            0, TRUE, DUPLICATE_SAME_ACCESS);
    CloseHandle(&writeTemp);
    readPipe = readTemp;

    STARTUPINFO si = {};
    si.cb         = sizeof(STARTUPINFO);
    si.dwFlags    = STARTF_USESTDHANDLES;
    si.hStdInput  = childReadHandle;
    si.hStdOutput = childWriteHandle;
    si.hStdError  = GetStdHandle(STD_ERROR_HANDLE);

    PROCESS_INFORMATION pi = {};
    if(!CreateProcess(NULL, cmdline, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
        puts("Error occurs while invoking process..");
        puts("This command works?: ");
        puts(cmdline);
        return;
    };

    puts("invoke process");

    return;
}

Point turn(State state, int color, Point last_move) {
    char buf[256];

    puts("writing to java stdin...");
    sprintf(buf, "%d\n", 10000000);
    WriteFile(writePipe, buf, strlen(buf), NULL, NULL);

    sprintf(buf, "%d %d\n", (color == COLOR_BLACK ? 1 : 0), -1);
    WriteFile(writePipe, buf, strlen(buf), NULL, NULL);

    for(int y=0; y<BOARD_HEIGHT; y++) {
        *buf = 0;
        for(int x=0; x<BOARD_WIDTH; x++) {
            switch(state.board[y][x]) {
                case COLOR_NONE:
                    strcat(buf, ".");
                    break;
                case COLOR_BLACK:
                    strcat(buf, "x");
                    break;
                case COLOR_WHITE:
                    strcat(buf, "o");
                    break;
            }
            strcat(buf, x==BOARD_WIDTH-1 ? '\n' : ' ');
        }
        WriteFile(writePipe, buf, strlen(buf), NULL, NULL);
    }
    FlushFileBuffers(writePipe);

    puts("reading from java stdout...");
    ReadFile(readPipe, buf, 10, NULL, NULL);

    puts("read: ");
    puts(buf);

    Point pt;
    sscanf(buf,"%d%d",&pt.x,&pt.y);
    return pt;
}

