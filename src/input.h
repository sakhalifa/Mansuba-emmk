#ifndef __INPUT_H__
#define __INPUT_H__

enum actions{
    MOVE,
    ESCAPE,
    WAIT,
    MAX_ACTION
};

unsigned int read_user_position();
enum actions read_user_action();
unsigned int read_user_number();

#endif // __INPUT_H__
