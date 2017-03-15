#include <stdio.h>
#include <dlfcn.h>

#include "othello-def.h"

void *black_handle, *white_handle;
extern fun_init init_black, init_white;
extern fun_turn turn_black, turn_white;

int die_dlerror(const char *msg) {
    printf("%s: %s\n", msg, dlerror());
    if(black_handle) dlclose(black_handle);
    if(white_handle) dlclose(white_handle);
    black_handle = white_handle = NULL;
    init_black = init_white = NULL;
    turn_black = turn_white = NULL;
    return 1;
}

int load_functions(char *black_libname, char *white_libname) {
    black_handle = dlopen(black_libname, RTLD_LAZY);
    if(!black_handle)
        return die_dlerror("Error occurs while loading black-lib");
    white_handle = dlopen(white_libname, RTLD_LAZY);
    if(!white_handle)
        return die_dlerror("Error occurs while loading white-lib");

    init_black = (fun_init)dlsym(black_handle, "init");
    if(!init_black)
        return die_dlerror("Error occurs while loading black-init");
    turn_black = (fun_turn)dlsym(black_handle, "turn");
    if(!turn_black)
        return die_dlerror("Error occurs while loading black-turn");

    init_white = (fun_init)dlsym(white_handle, "init");
    if(!init_white)
        return die_dlerror("Error occurs while loading white-init");
    turn_white = (fun_turn)dlsym(white_handle, "turn");
    if(!turn_white)
        return die_dlerror("Error occurs while loading white-turn");
    return 0;
}
