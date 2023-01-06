#ifndef __INPUT_H__
#define __INPUT_H__

enum actions{
    MOVE,
    ESCAPE,
    WAIT,
    MAX_ACTION
};

unsigned int read_user_position(void);
enum actions read_user_action(void);
unsigned int read_user_number(void);

#endif // __INPUT_H__
