#include "sudoku.h"
#include <stdio.h>
#include <stdlib.h>

/*
** reads commands until 'exit' or end of input (Ctrl+D).
** the actual work is done by the handlers in src/commands/.
*/
int main_loop(core_t *core)
{
    char *line = NULL;
    command_history_t *entry = NULL;
    cmd_status_t status = CMD_OK;

    print_table(core, stdout);
    printf("Press Enter to run a step, or type 'help' for commands.\n");
    while (status != CMD_EXIT) {
        line = read_input(core);
        if (line == NULL)
            break;
        entry = history_add(core, line);
        status = execute_command(core, line);
        if (entry != NULL)
            entry->status = status;
        free(line);
    }
    history_free(core);
    return 0;
}
