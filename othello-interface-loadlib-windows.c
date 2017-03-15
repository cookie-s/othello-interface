#include <stdio.h>
#include <windows.h>

#include "othello-def.h"

HMODULE black_handle, white_handle;
extern fun_init init_black, init_white;
extern fun_turn turn_black, turn_white;

int die_dlerror(const char *msg) {
    printf("%s: GetLastError: %d\n", msg, GetLastError());
    if(black_handle) FreeLibrary(black_handle);
    if(white_handle) FreeLibrary(white_handle);
    black_handle = white_handle = NULL;
    init_black = init_white = NULL;
    turn_black = turn_white = NULL;
    return 1;
}

int load_functions(char *black_libname, char *white_libname) {
    black_handle = LoadLibrary(black_libname);
    if(!black_handle)
        return die_dlerror("Error occurs while loading black-lib");
    white_handle = LoadLibrary(white_libname);
    if(!white_handle)
        return die_dlerror("Error occurs while loading white-lib");

    init_black = (fun_init)GetProcAddress(black_handle, "init");
    if(!init_black)
        return die_dlerror("Error occurs while loading black-init");
    turn_black = (fun_turn)GetProcAddress(black_handle, "turn");
    if(!turn_black)
        return die_dlerror("Error occurs while loading black-turn");

    init_white = (fun_init)GetProcAddress(white_handle, "init");
    if(!init_white)
        return die_dlerror("Error occurs while loading white-init");
    turn_white = (fun_turn)GetProcAddress(white_handle, "turn");
    if(!turn_white)
        return die_dlerror("Error occurs while loading white-turn");
    return 0;
}
