#include "sudoku.h"
#include <stdio.h>

/* one solving step: returns true if a number got confirmed */
static bool do_step(core_t *core)
{
    prune_possibilities(core);
    return confirm_single_possibilities(core);
}

static void report_stop(core_t *core)
{
    if (is_solved(core))
        printf("Solved!\n");
    else
        printf("Stuck: no more progress with the current techniques.\n");
}

cmd_status_t cmd_step(core_t *core, char **args)
{
    int count = 1;

    if (args[1] != NULL && !parse_int(args[1], 1, 81, &count)) {
        fprintf(stderr, "Invalid step count '%s': expected 1-81\n", args[1]);
        return CMD_ERROR;
    }
    for (int i = 0; i < count; i++) {
        if (!do_step(core)) {
            report_stop(core);
            break;
        }
    }
    print_table(core, stdout);
    return CMD_OK;
}

cmd_status_t cmd_solve(core_t *core, char **args)
{
    (void)args;
    while (do_step(core));
    print_table(core, stdout);
    report_stop(core);
    return CMD_OK;
}

cmd_status_t cmd_exit(core_t *core, char **args)
{
    (void)core;
    (void)args;
    return CMD_EXIT;
}
