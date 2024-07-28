#ifndef PROMPT_H_
#define PROMPT_H_

#include <display_base.h>
#include <reader_base.h>
#include <action_manager.h>

typedef struct
{
    display_base_t display;
    reader_base_t reader;
    action_manager_t manager;
    char *buffer;
    uint8_t size;
    bool run;
    bool modified;
} prompt_t;

typedef struct
{
    display_base_t display;
    reader_base_t reader;
    char *buffer;
    uint8_t size;
} prompt_args_t;

bool prompt_open (prompt_t *object, prompt_args_t *args);
bool prompt_run (prompt_t *object);

#endif/* PROMPT_H_ */
