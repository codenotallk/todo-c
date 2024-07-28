#include <prompt.h>
#include <string.h>
#include <command.h>
#include <common.h>

static void prompt_show (prompt_t *object);
static void prompt_read (prompt_t *object);
static void prompt_read_command (prompt_t *object);
static bool prompt_command_process (prompt_t *object);

static void prompt_add (prompt_t *object);
static void prompt_display (prompt_t *object);
static void prompt_exit (prompt_t *object);
static void prompt_remove (prompt_t *object);
static void prompt_update (prompt_t *object);
static void prompt_complete (prompt_t *object);
static void prompt_save (prompt_t *object);

static action_args_t prompt_fill_action_args (prompt_t *object);
static bool prompt_wanna_proceed (prompt_t *object, char *text);
static bool prompt_asks_for_id (prompt_t *object, char *text);

typedef struct 
{
    const char *name;
    void (*handler) (prompt_t *object);
} prompt_command_t;

static prompt_command_t commands [] = 
{
    {.name = COMMAND_ADD,      .handler = prompt_add},
    {.name = COMMAND_DISPLAY,  .handler = prompt_display},
    {.name = COMMAND_EXIT,     .handler = prompt_exit},
    {.name = COMMAND_REMOVE,   .handler = prompt_remove},
    {.name = COMMAND_UPDATE,   .handler = prompt_update},
    {.name = COMMAND_COMPLETE, .handler = prompt_complete},
    {.name = COMMAND_SAVE,     .handler = prompt_save},
};

static uint8_t prompt_command_amount = sizeof (commands) / sizeof (commands [0]);

bool prompt_open (prompt_t *object, prompt_args_t *args)
{
    bool status = false;

    memset (object, 0, sizeof (prompt_t));

    object->display = args->display;
    object->reader  = args->reader;
    object->buffer  = args->buffer;
    object->size    = args->size;

    object->run = true;
    object->modified = false;

    status = action_manager_open (&object->manager, &(action_manager_args_t){});

    return status;
}

bool prompt_run (prompt_t *object)
{
    while (object->run == true)
    {
        // show logo 
        // show menu

        prompt_show (object);

        prompt_read_command (object);

        if (prompt_command_process (object) == false)
        {
            // error message
        }
    }

    return object->run;
}

static void prompt_show (prompt_t *object)
{
    object->display->show ("(todo) > ");
}

static void prompt_read (prompt_t *object)
{
    memset (object->buffer, 0, object->size);

    object->reader->read (object->buffer, object->size);
}

static void prompt_read_command (prompt_t *object)
{
    prompt_read (object);

    common_string_to_lower (object->buffer);
}

static bool prompt_command_process (prompt_t *object)
{
    bool status = false;

    for (uint8_t i = 0; i < prompt_command_amount; i ++)
    {
        prompt_command_t *command = &commands [i];

        if (strncmp (object->buffer, command->name, strlen (command->name)) == 0)
        {
            command->handler (object);

            status = true;
            break;
        }
    }

    return status;
}

static void prompt_add (prompt_t *object)
{
    char *text = "You are about to add a new task. Are you sure? (yes/no): ";

    action_args_t args = prompt_fill_action_args (object);

    if (prompt_wanna_proceed (object, text) == true)
    {
        strncpy (args.command, COMMAND_ADD, strlen (COMMAND_ADD) + 1);

        if (action_manager_process (&object->manager, &args, object->display) == true)
        {
            // success message
            object->modified = true;
        }

        else
        {
            // error message
        }
    }
}

static void prompt_display (prompt_t *object)
{
    action_args_t args;

    memset (&args, 0, sizeof (action_args_t));

    strncpy (args.command, COMMAND_DISPLAY, strlen (COMMAND_DISPLAY) + 1);

    action_manager_process (&object->manager, &args, object->display);
}

static void prompt_exit (prompt_t *object)
{
    char *text = "You have did some modifications. Do you want to quit anyway? (yes/no): ";

    if (object->modified == false)
    {
        object->run = false;
    }

    else if (prompt_wanna_proceed (object, text) == true)
    {
        object->run = false;
    }
}

static void prompt_remove (prompt_t *object)
{
    char *text = "Would you like to remove? (yes/no): ";
    char *text_id = "Type the task id to delete or exit to cancel: ";

    if (prompt_asks_for_id (object, text_id) == true)
    {
        action_args_t args;

        memset (&args, 0, sizeof (action_args_t));

        strncpy (args.command, COMMAND_REMOVE, strlen (COMMAND_REMOVE) + 1);
        strncpy (args.parameters.first, object->buffer, strlen (object->buffer));

        if (prompt_wanna_proceed (object, text) == true)
        {
            if (action_manager_process (&object->manager, &args, object->display) == true)
            {
                // success message
                object->modified = true;
            }

            else
            {
                // error message
            }
        }
    }
}

static void prompt_update (prompt_t *object)
{
    char *text = "Would you like to update? (yes/no): ";
    char *text_id = "Type the task id to update or exit to cancel: ";

    if (prompt_asks_for_id (object, text_id) == true)
    {

        char buffer [DEFINITIONS_FIELD_SIZE + 1] = {0};

        strncpy (buffer, object->buffer, strlen (object->buffer));

        action_args_t args = prompt_fill_action_args (object);

        if (prompt_wanna_proceed (object, text) == true)
        {
            strncpy (args.command, COMMAND_UPDATE, strlen (COMMAND_UPDATE) + 1);
            strncpy (args.parameters.first, object->buffer, strlen (object->buffer));

            if (action_manager_process (&object->manager, &args, object->display) == true)
            {
                // success message
                object->modified = true;
            }

            else
            {
                // error message
            }
        }
    }
}

static void prompt_complete (prompt_t *object)
{
    char *text = "Would you like to complete? (yes/no): ";
    char *text_id = "Type the task id to complete or exit to cancel: ";

    if (prompt_asks_for_id (object, text_id) == true)
    {
        action_args_t args;

        memset (&args, 0, sizeof (action_args_t));

        strncpy (args.command, COMMAND_COMPLETE, strlen (COMMAND_COMPLETE) + 1);
        strncpy (args.parameters.first, object->buffer, strlen (object->buffer));

        if (prompt_wanna_proceed (object, text) == true)
        {
            if (action_manager_process (&object->manager, &args, object->display) == true)
            {
                // success message
                object->modified = true;
            }

            else
            {
                // error message
            }
        }
    }
}

static void prompt_save (prompt_t *object)
{
    action_args_t args;

    memset (&args, 0, sizeof (action_args_t));

    strncpy (args.command, COMMAND_SAVE, strlen (COMMAND_SAVE) + 1);

    action_manager_process (&object->manager, &args, object->display);

    object->modified = false;
}

static action_args_t prompt_fill_action_args (prompt_t *object)
{
    action_args_t args;

    memset (&args, 0, sizeof (action_args_t));

    object->display->show ("Type the task name: ");
    object->reader->read (args.parameters.first, DEFINITIONS_FIELD_SIZE);

    object->display->show ("Type the task description: ");
    object->reader->read (args.parameters.second, DEFINITIONS_FIELD_SIZE);

    return args;
}

static bool prompt_wanna_proceed (prompt_t *object, char *text)
{
    bool status = false;

    while (true)
    {
        object->display->show (text);

        char buffer [11] = {0};
        object->reader->read (buffer, 10);

        if (strncmp (buffer, "yes", strlen ("yes")) == 0)
        {
            status = true;
            break;
        }

        if (strncmp (buffer, "no", strlen ("no")) == 0)
        {
            // message cancel
            break;
        }

        else
        {
            // message invalid entry
        }
    }

    return status;
}

static bool prompt_asks_for_id (prompt_t *object, char *text)
{
    bool status = false;

    while (true)
    {
        object->display->show (text);

        char buffer [11] = {0};
        object->reader->read (buffer, 10);

        if (common_is_a_number (object->buffer) == true)
        {
            status = true;
            break;
        }

        if (strncmp (buffer, "exit", strlen ("exit")) == 0)
        {
            // message cancel
            break;
        }

        else
        {
            // message invalid entry
        }
    }

    return status;
}