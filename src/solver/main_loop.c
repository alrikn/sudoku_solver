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
    size_t size = 0;
    cmd_status_t status = CMD_OK;

    print_table(core, stdout);
    printf("Press Enter to run a step, or type 'help' for commands.\n");
    while (status != CMD_EXIT) {
        printf("> ");
        fflush(stdout);
        if (getline(&line, &size, stdin) == -1) {
            printf("\n");
            break;
        }
        status = execute_command(core, line);
    }
    free(line);
    return 0;
}
