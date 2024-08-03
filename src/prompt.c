#include <prompt.h>
#include <string.h>
#include <command.h>
#include <common.h>
#include <menu.h>
#include <style.h>

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

static void prompt_display_style (prompt_t *object, char *message, style_t style);

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

    if (action_manager_open (&object->manager, &(action_manager_args_t){}) == true && 
        translate_init (&object->translate) == true)
    {
        status = true;
    }

    return status;
}

bool prompt_run (prompt_t *object)
{
    while (object->run == true)
    {
        prompt_display_style (object, menu_logo (), style_fancy);
        prompt_display_style (object, menu_show (&object->translate), style_default);

        prompt_show (object);

        prompt_read_command (object);

        if (prompt_command_process (object) == false)
        {
            prompt_display_style (object,
                                  translate_get_text_by (&object->translate, type_error_command),
                                  style_error);
        }
    }

    return object->run;
}

static void prompt_show (prompt_t *object)
{
    prompt_display_style (object, "(todo) > ", style_fancy);
}

static void prompt_read (prompt_t *object)
{
    memset (object->buffer, 0, object->size);

    object->reader.read (object->buffer, object->size);
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
    action_args_t args = prompt_fill_action_args (object);

    if (prompt_wanna_proceed (object,
                              translate_get_text_by (&object->translate, type_question_task_add)) == true)
    {
        strncpy (args.command, COMMAND_ADD, strlen (COMMAND_ADD) + 1);

        if (action_manager_process (&object->manager, &args, &object->display) == true)
        {
            prompt_display_style (object,
                                  translate_get_text_by (&object->translate, type_success_task_add),
                                  style_success);

            object->modified = true;
        }

        else
        {
            prompt_display_style (object,
                                  translate_get_text_by (&object->translate, type_error_task_add),
                                  style_error);
        }
    }
}

static void prompt_display (prompt_t *object)
{
    action_args_t args;

    memset (&args, 0, sizeof (action_args_t));

    strncpy (args.command, COMMAND_DISPLAY, strlen (COMMAND_DISPLAY) + 1);

    action_manager_process (&object->manager, &args, &object->display);
}

static void prompt_exit (prompt_t *object)
{
    if (object->modified == false)
    {
        object->run = false;
    }

    else if (prompt_wanna_proceed (object,
                                   translate_get_text_by (&object->translate, type_question_modification)) == true)
    {
        object->run = false;
    }
}

static void prompt_remove (prompt_t *object)
{
    if (prompt_asks_for_id (object,
                            translate_get_text_by (&object->translate, type_id_remove)) == true)
    {
        action_args_t args;

        memset (&args, 0, sizeof (action_args_t));

        strncpy (args.command, COMMAND_REMOVE, strlen (COMMAND_REMOVE) + 1);
        strncpy (args.parameters.first, object->buffer, strlen (object->buffer));

        if (prompt_wanna_proceed (object,
                                  translate_get_text_by (&object->translate, type_question_task_remove)) == true)
        {
            if (action_manager_process (&object->manager, &args, &object->display) == true)
            {
                prompt_display_style (object,
                                      translate_get_text_by (&object->translate, type_success_task_remove),
                                      style_success);

                object->modified = true;
            }

            else
            {
                prompt_display_style (object,
                                      translate_get_text_by (&object->translate, type_error_task_remove),
                                      style_error);
            }
        }
    }
}

static void prompt_update (prompt_t *object)
{
    if (prompt_asks_for_id (object,
                            translate_get_text_by (&object->translate, type_id_update)) == true)
    {

        char buffer [DEFINITIONS_FIELD_SIZE + 1] = {0};

        strncpy (buffer, object->buffer, strlen (object->buffer));

        action_args_t args = prompt_fill_action_args (object);

        if (prompt_wanna_proceed (object,
                                  translate_get_text_by (&object->translate, type_question_task_update)) == true)
        {
            strncpy (args.command, COMMAND_UPDATE, strlen (COMMAND_UPDATE) + 1);
            strncpy (args.parameters.third, buffer, strlen (buffer));

            if (action_manager_process (&object->manager, &args, &object->display) == true)
            {
                prompt_display_style (object,
                                      translate_get_text_by (&object->translate, type_success_task_update),
                                      style_success);

                object->modified = true;
            }

            else
            {
                prompt_display_style (object,
                                      translate_get_text_by (&object->translate, type_error_task_update),
                                      style_error);
            }
        }
    }
}

static void prompt_complete (prompt_t *object)
{
    if (prompt_asks_for_id (object,
                            translate_get_text_by (&object->translate, type_id_complete)) == true)
    {
        action_args_t args;

        memset (&args, 0, sizeof (action_args_t));

        strncpy (args.command, COMMAND_COMPLETE, strlen (COMMAND_COMPLETE) + 1);
        strncpy (args.parameters.first, object->buffer, strlen (object->buffer));

        if (prompt_wanna_proceed (object,
                                  translate_get_text_by (&object->translate, type_question_task_complete)) == true)
        {
            if (action_manager_process (&object->manager, &args, &object->display) == true)
            {
                prompt_display_style (object,
                                      translate_get_text_by (&object->translate, type_success_task_complete),
                                      style_success);

                object->modified = true;
            }

            else
            {
                prompt_display_style (object,
                                      translate_get_text_by (&object->translate, type_error_task_complete),
                                      style_error);
            }
        }
    }
}

static void prompt_save (prompt_t *object)
{
    action_args_t args;

    memset (&args, 0, sizeof (action_args_t));

    strncpy (args.command, COMMAND_SAVE, strlen (COMMAND_SAVE) + 1);

    action_manager_process (&object->manager, &args, &object->display);

    object->modified = false;
}

static action_args_t prompt_fill_action_args (prompt_t *object)
{
    action_args_t args;

    memset (&args, 0, sizeof (action_args_t));

    prompt_display_style (object,
                          translate_get_text_by (&object->translate, type_task_name),
                          style_default);

    object->reader.read (args.parameters.first, DEFINITIONS_FIELD_SIZE);

    prompt_display_style (object,
                          translate_get_text_by (&object->translate, type_task_description),
                          style_default);

    object->reader.read (args.parameters.second, DEFINITIONS_FIELD_SIZE);

    return args;
}

static bool prompt_wanna_proceed (prompt_t *object, char *text)
{
    bool status = false;

    while (true)
    {
        prompt_display_style (object, text, style_default);

        char buffer [11] = {0};
        object->reader.read (buffer, 10);

        if (strncmp (buffer,
                     translate_get_text_by (&object->translate, type_input_yes),
                     strlen (translate_get_text_by (&object->translate, type_input_yes))) == 0)
        {
            status = true;
            break;
        }

        if (strncmp (buffer,
                     translate_get_text_by (&object->translate, type_input_no),
                     strlen (translate_get_text_by (&object->translate, type_input_no))) == 0)
        {
            prompt_display_style (object,
                                  translate_get_text_by (&object->translate, type_error_canceled),
                                  style_error);
            break;
        }

        else
        {
            prompt_display_style (object,
                                  translate_get_text_by (&object->translate, type_error_option),
                                  style_error);
        }
    }

    return status;
}

static bool prompt_asks_for_id (prompt_t *object, char *text)
{
    bool status = false;

    while (true)
    {
        prompt_display_style (object, text, style_default);

        object->reader.read (object->buffer, 10);

        if (common_is_a_number (object->buffer) == true)
        {
            status = true;
            break;
        }

        if (strncmp (object->buffer,
                     translate_get_text_by (&object->translate, type_input_exit),
                     strlen (translate_get_text_by (&object->translate, type_input_exit))) == 0)
        {
            prompt_display_style (object,
                                  translate_get_text_by (&object->translate, type_error_canceled),
                                  style_error);
            break;
        }

        else
        {
            prompt_display_style (object,
                                  translate_get_text_by (&object->translate, type_error_task_id),
                                  style_error);
        }
    }

    return status;
}

static void prompt_display_style (prompt_t *object, char *message, style_t style)
{
    style_set (style);
    object->display.show (message);
    style_reset ();
}