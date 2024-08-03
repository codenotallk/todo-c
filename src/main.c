#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <application.h>

int main(int argc, char *argv[])
{
    sat_status_t status;

    todo_t todo;
    todo_args_t args =
    {
        .filename = argv [1]
    };

    do
    {
        status = todo_init (&todo);
        if (sat_status_get_result (&status) == false)
        {
            break;
        }

        status = todo_open (&todo, &args);
        if (sat_status_get_result (&status) == false)
        {
            break;
        }

        status = todo_run (&todo);
        if (sat_status_get_result (&status) == false)
        {
            break;
        }

        else
            status = todo_close (&todo);

    } while (false);

    printf ("%s\n", sat_status_get_motive (&status));

    return sat_status_get_result (&status) == true ? EXIT_SUCCESS : EXIT_FAILURE;
}