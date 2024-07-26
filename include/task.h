#ifndef TASK_H_
#define TASK_H_

#include <definitions.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct 
{
    uint32_t id;
    char name [DEFINITIONS_FIELD_SIZE + 1];
    char description [DEFINITIONS_FIELD_SIZE + 1];
    bool done;
} task_t;

bool task_create (task_t *object, char *name, char *definition);
bool task_update (task_t *object, char *name, char *description);
bool task_set_done (task_t *object, bool done);

#endif/* TASK_H_ */
