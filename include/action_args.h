#ifndef ACTION_ARGS_H_
#define ACTION_ARGS_H_

#include <definitions.h>

typedef struct 
{
    char command [DEFINITIONS_FIELD_SIZE + 1];

    struct 
    {
        char first [DEFINITIONS_FIELD_SIZE + 1];
        char second [DEFINITIONS_FIELD_SIZE + 1];
        char third [DEFINITIONS_FIELD_SIZE + 1];
    } parameters;
    
} action_args_t;

#endif/* ACTION_ARGS_H_ */
