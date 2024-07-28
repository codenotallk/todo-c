#ifndef ACTION_H_
#define ACTION_H_

#include <action_handler.h>

typedef struct 
{
    const char *command;
    action_handler_t handler;
} action_t;

#endif/* ACTION_H_ */
