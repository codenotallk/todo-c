#include <translate.h>
#include <string.h>

static text_t texts [] = 
{
    {.type = type_error_command,          .tag = "error.command",          .content = "Invalid command\n\n"},
    {.type = type_error_option,           .tag = "error.option",           .content = "Invalid option.\n\n"},
    {.type = type_error_canceled,         .tag = "error.canceled",         .content = "Canceled\n\n"},
    {.type = type_error_task_add,         .tag = "error.task.add",         .content = "Couldn't add a new Task\n\n"},
    {.type = type_error_task_remove,      .tag = "error.task.remove",      .content = "Couldn't remove the Task\n\n"},
    {.type = type_error_task_update,      .tag = "error.task.update",      .content = "Couldn't update the Task\n\n"},
    {.type = type_error_task_complete,    .tag = "error.task.complete",    .content = "Couldn't complete the Task\n\n"},
    {.type = type_error_task_id,          .tag = "error.task.id",          .content = "Please. Type a valid ID number.\n\n"},
    {.type = type_question_modification,  .tag = "question.modification",  .content = "You have did some modifications. Do you want to quit anyway? (yes/no): "},
    {.type = type_question_task_add,      .tag = "question.task.add",      .content = "You are about to add a new task. Are you sure? (yes/no): "},
    {.type = type_question_task_remove,   .tag = "question.task.remove",   .content = "Would you like to remove? (yes/no): "},
    {.type = type_question_task_update,   .tag = "question.task.update",   .content = "Would you like to update? (yes/no): "},
    {.type = type_question_task_complete, .tag = "question.task.complete", .content = "Would you like to complete? (yes/no): "},
    {.type = type_success_task_add,       .tag = "success.task.add",       .content = "New Task added successfully\n\n"},
    {.type = type_success_task_remove,    .tag = "success.task.remove",    .content = "Task removed successfully\n\n"},
    {.type = type_success_task_update,    .tag = "success.task.update",    .content = "Task updated successfully\n\n"},
    {.type = type_success_task_complete,  .tag = "success.task.complete",  .content = "Task completed successfully\n\n"},
    {.type = type_id_remove,              .tag = "id.remove",              .content = "Type the task id to delete or exit to cancel: "},
    {.type = type_id_update,              .tag = "id.update",              .content = "Type the task id to update or exit to cancel: "},
    {.type = type_id_complete,            .tag = "id.complete",            .content = "Type the task id to complete or exit to cancel: "},
    {.type = type_task_name,              .tag = "task.name",              .content = "Type the task name: "},
    {.type = type_task_description,       .tag = "task.description",       .content = "Type the task description: "},
    {.type = type_input_yes,              .tag = "input.yes",              .content = "yes"},
    {.type = type_input_no,               .tag = "input.no",               .content = "no"},
    {.type = type_input_exit,             .tag = "input.exit",             .content = "exit"},
    {.type = type_menu_add,               .tag = "menu.add",               .content = "Add      To add a new task\n"},
    {.type = type_menu_remove,            .tag = "menu.remove",            .content = "Remove   To remove a task\n"},
    {.type = type_menu_update,            .tag = "menu.update",            .content = "Update   To update a task\n"},
    {.type = type_menu_display,           .tag = "menu.display",           .content = "Display  To display tasks\n"},
    {.type = type_menu_complete,          .tag = "menu.complete",          .content = "Complete To complete a task\n"},
    {.type = type_menu_save,              .tag = "menu.save",              .content = "Save     To save the tasks\n"},
    {.type = type_menu_exit,              .tag = "menu.exit",              .content = "Exit     To quit application\n\n"},
};

// static unsigned char text_amount = sizeof (texts) / sizeof (texts [0]);

bool translate_init (translate_t *object)
{
    bool status = false;

    if (object != NULL)
    {
        object->texts = texts;
        object->initialized = true;

        status = true;
    }

    return status;
}

char *translate_get_text_by (translate_t *object, type_t type)
{
    char *content = "Not Found";

    if (type >= type_error_command && type <= type_menu_exit)
    {
        content = object->texts [type].content;
    }

    return content;
}

