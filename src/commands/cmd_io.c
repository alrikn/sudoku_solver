#include "sudoku.h"
#include <stdio.h>

cmd_status_t cmd_read(core_t *core, char **args)
{
    if (!load_file(core, args[1]))
        return CMD_ERROR;
    print_table(core, stdout);
    return CMD_OK;
}

cmd_status_t cmd_write(core_t *core, char **args)
{
    FILE *file = fopen(args[1], "w");

    if (file == NULL) {
        perror(args[1]);
        return CMD_ERROR;
    }
    print_table(core, file);
    if (fclose(file) != 0) {
        perror(args[1]);
        return CMD_ERROR;
    }
    printf("Saved to %s\n", args[1]);
    return CMD_OK;
}

cmd_status_t cmd_print(core_t *core, char **args)
{
    (void)args;
    print_table(core, stdout);
    return CMD_OK;
}
