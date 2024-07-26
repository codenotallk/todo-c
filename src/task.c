#include <task.h>
#include <string.h>

static bool task_args_is_valid (char *name, char *description);
static void task_copy_args (task_t *object, char *name, char *description);

bool task_create (task_t *object, char *name, char *description)
{
    bool status = false;

    if (object != NULL && task_args_is_valid (name, description) == true)    
    {
        memset (object, 0, sizeof (task_t));

        static uint32_t id = 0;

        object->id = ++id;

        task_copy_args (object, name, description);

        status = true;
    }

    return status;
}

bool task_update (task_t *object, char *name, char *description)
{
    bool status = false;

    if (object != NULL && task_args_is_valid (name, description) == true)    
    {

        task_copy_args (object, name, description);

        status = true;
    }

    return status;
}

bool task_set_done (task_t *object, bool done)
{
    bool status = false;

    if (object != NULL)
    {
        object->done = done;
        
        status = true;
    }

    return status;
}

static bool task_args_is_valid (char *name, char * description)
{
    bool status = false;

    if (name != NULL &&
        strlen (name) > 0 &&
        description != NULL &&
        strlen (description) > 0)  
    {
        status = true;
    }

    return status;
}

static void task_copy_args (task_t *object, char *name, char *description)
{
    strncpy (object->name, name, DEFINITIONS_FIELD_SIZE);
    strncpy (object->description, description, DEFINITIONS_FIELD_SIZE);
    object->done = false;
}