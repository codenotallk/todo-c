#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <sat.h>
#include <prompt.h>


typedef struct
{
    prompt_t prompt;
} todo_t;

typedef struct 
{
    char *filename;
} todo_args_t;

sat_status_t todo_init (todo_t *object);
sat_status_t todo_open (todo_t *object, todo_args_t *args);
sat_status_t todo_run (todo_t *object);
sat_status_t todo_close (todo_t *object);

#endif/* APPLICATION_H_ */