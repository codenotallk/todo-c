#include <application.h>
#include <string.h>

sat_status_t todo_init (todo_t *object)
{
    sat_status_t status = sat_status_set (&status, false, "todo init error");

    if (object != NULL)
    {

        sat_status_set (&status, true, "");
    }

    return status;
}

sat_status_t todo_open (todo_t *object, todo_args_t *args)
{
    sat_status_t status = sat_status_set (&status, false, "todo open error");

    if (object != NULL && args != NULL)
    {

        sat_status_set (&status, true, "");
    }

    return status;
}

sat_status_t todo_run (todo_t *object)
{
    sat_status_t status = sat_status_set (&status, false, "todo run error");

    if (object != NULL)
    {

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