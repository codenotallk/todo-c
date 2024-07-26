#ifndef TASK_MANAGER_H_
#define TASK_MANAGER_H_

#include <sat.h>
#include <task.h>

typedef struct 
{
    sat_array_t *tasks;
} task_manager_t;

bool task_manager_open (task_manager_t *object);
bool task_manager_add (task_manager_t *object, task_t *task);
bool task_manager_get_by (task_manager_t *object, uint32_t index, task_t *task);
bool task_manager_find_by (task_manager_t *object, uint32_t id, task_t *task, uint32_t *index);
bool task_manager_update_by (task_manager_t *object, uint32_t index, task_t *task);
bool task_manager_remove_by (task_manager_t *object, uint32_t index);
bool task_manager_close (task_manager_t *object);
uint32_t task_manager_get_tasks_amount (task_manager_t *object);

#endif/* TASK_MANAGER_H_ */
