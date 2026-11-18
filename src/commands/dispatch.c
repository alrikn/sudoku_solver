#include "commands.h"
#include <stdio.h>
#include <string.h>

/*
** To add a command: write its handler, declare it in commands.h,
** and add one line here. help is generated from this table.
*/
static const command_t COMMANDS[] = {
    {"step", 0, 1, "step [n]",
        "run n solving steps (default 1, Enter does 1)", cmd_step},
    {"solve", 0, 0, "solve", "run steps until solved or stuck", cmd_solve},
    {"print", 0, 0, "print", "print the grid", cmd_print},
    {"pos", 1, 1, "pos <x,y>",
        "list possibilities at column x, row y (0-8)", cmd_print_pos},
    {"set", 2, 2, "set <x,y> <n>", "place n (1-9) at column x, row y",
        cmd_set},
    {"clear", 1, 1, "clear <x,y>", "empty the cell at column x, row y",
        cmd_clear},
    {"read", 1, 1, "read <file>", "load a sudoku from file", cmd_read},
    {"write", 1, 1, "write <file>", "save the current sudoku to file",
        cmd_write},
    {"help", 0, 0, "help", "show this list", cmd_help},
    {"exit", 0, 0, "exit", "quit", cmd_exit},
    {NULL, 0, 0, NULL, NULL, NULL}
};

/*
** splits line in place into args (NULL terminated).
** returns the word count, or -1 if there are more than MAX_ARGS words.
*/
static int tokenize(char *line, char **args)
{
    int count = 0;
    char *token = strtok(line, " \t\r\n");

    while (token != NULL && count < MAX_ARGS) {
        args[count] = token;
        count++;
        token = strtok(NULL, " \t\r\n");
    }
    args[count] = NULL;
    return token == NULL ? count : -1;
}

static const command_t *find_command(const char *name)
{
    for (int i = 0; COMMANDS[i].name != NULL; i++) {
        if (strcmp(COMMANDS[i].name, name) == 0)
            return &COMMANDS[i];
    }
    return NULL;
}

cmd_status_t execute_command(core_t *core, char *line)
{
    char *args[MAX_ARGS + 1] = {NULL};
    char *step_args[] = {"step", NULL};
    int count = tokenize(line, args);
    const command_t *cmd = NULL;

    if (count == 0)
        return cmd_step(core, step_args);
    cmd = count > 0 ? find_command(args[0]) : NULL;
    if (cmd == NULL) {
        fprintf(stderr, "Unknown command '%s' (type 'help')\n", args[0]);
        return CMD_ERROR;
    }
    if (count - 1 < cmd->min_args || count - 1 > cmd->max_args) {
        fprintf(stderr, "Usage: %s\n", cmd->usage);
        return CMD_ERROR;
    }
    return cmd->run(core, args);
}

cmd_status_t cmd_help(core_t *core, char **args)
{
    (void)core;
    (void)args;
    for (int i = 0; COMMANDS[i].name != NULL; i++)
        printf("  %-18s %s\n", COMMANDS[i].usage, COMMANDS[i].help);
    return CMD_OK;
}
