#include <application.h>
#include <stdlib.h>
#include <string.h>

static void application_read (char *buffer, uint8_t size)
{
    fgets (buffer, size, stdin);

    buffer [strlen (buffer) - 1] = 0;  // we remove the \n
}
static void application_show (char *message)
{
    fprintf (stdout, "%s", message);
}

sat_status_t todo_init (todo_t *object)
{
    sat_status_t status = sat_status_set (&status, false, "todo init error");

    if (object != NULL)
    {
        memset (object, 0, sizeof (todo_t)); // I need to remember to put this is code 
                                             // generated

        sat_status_set (&status, true, "");
    }

    return status;
}

sat_status_t todo_open (todo_t *object, todo_args_t *args)
{
    sat_status_t status = sat_status_set (&status, false, "todo open error");

    if (object != NULL && args != NULL)
    {
        static char buffer [DEFINITIONS_FIELD_SIZE];

        bool __status = prompt_open (&object->prompt, &(prompt_args_t)
                                                      {
                                                        .display.show = application_show,
                                                        .reader.read  = application_read,
                                                        .buffer = buffer,
                                                        .size = DEFINITIONS_FIELD_SIZE
                                                      });

        if (__status == true)
            sat_status_set (&status, true, "");
    }

    return status;
}

sat_status_t todo_run (todo_t *object)
{
    sat_status_t status = sat_status_set (&status, false, "todo run error");

    if (object != NULL)
    {
        prompt_run (&object->prompt);
        sat_status_set (&status, true, "");
    }

    return status;
}

sat_status_t todo_close (todo_t *object)
{
    sat_status_t status = sat_status_set (&status, false, "todo close error");

    if (object != NULL)
    {

        sat_status_set (&status, true, "");
    }

    return status;
}