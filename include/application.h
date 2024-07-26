#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <sat.h>

typedef struct
{
    int dummy; // your context
} todo_t;

typedef struct 
{
    int dummy;
} todo_args_t;

sat_status_t todo_init (todo_t *object);
sat_status_t todo_open (todo_t *object, todo_args_t *args);
sat_status_t todo_run (todo_t *object);
sat_status_t todo_close (todo_t *object);

#endif/* APPLICATION_H_ */