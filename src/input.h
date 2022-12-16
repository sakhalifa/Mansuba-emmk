#ifndef __INPUT_H__
#define __INPUT_H__
#include "util.h"

enum actions{
    MOVE,
    ESCAPE,
    WAIT,
    MAX_ACTION
};

uint read_user_position();
enum actions read_user_action();

#endif // __INPUT_H__
