#ifndef _OTHELLO_AI_
#define _OTHELLO_AI_

#include "othello-def.h"

void init(int color);
Point turn(State state, int color, Point last_move);

#endif
