#include <menu.h>

char *menu_logo (void)
{
    static char *logo = 
    {
        " _____         _         _     _     _ \n"
        "|_   _|       | |       | |   (_)   | |\n"
        "  | | ___   __| | ___   | |    _ ___| |\n"
        "  | |/ _ \\ / _` |/ _ \\  | |   | / __| __|\n"
        "  | | (_) | (_| | (_) | | |___| \\__ \\ |_\n"
        "  \\_/\\___/ \\__,_|\\___/  \\_____/_|___/\\__|\n\n"
    };

    return logo;
}

char *menu_show (void)
{
    static char *options = 
    {
        "Add      To add a new task\n"
        "Remove   To remove a task\n"
        "Update   To update a task\n"
        "Display  To display tasks\n"
        "Complete To complete a task\n"
        "Save     To save the tasks\n"
        "Exit     To quit application\n\n"
    };

    return options;   
}