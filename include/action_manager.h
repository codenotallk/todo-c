#ifndef ACTION_MANAGER_H_
#define ACTION_MANAGER_H_

#include <task_manager.h>
#include <action_args.h>
#include <display_base.h>

typedef struct 
{
    sat_array_t *actions;
    task_manager_t manager;
} action_manager_t;

typedef struct 
{
    uint8_t amount;
} action_manager_args_t;

bool action_manager_open (action_manager_t *object, action_manager_args_t *args);
bool action_manager_process (action_manager_t *object, action_args_t *args, display_base_t *display);

#endif/* ACTION_MANAGER_H_ */
