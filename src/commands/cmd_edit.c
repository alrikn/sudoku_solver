#include "sudoku.h"
#include <stdio.h>

/* checks num against the other cells, ignoring the cell itself */
static bool has_conflict(core_t *core, int row, int col, int num)
{
    int old = core->table[row][col].confirmed_num;
    bool conflict = false;

    core->table[row][col].confirmed_num = 0;
    conflict = number_exists_in_row(core, row, num) ||
        number_exists_in_column(core, col, num) ||
        number_exists_in_block(core, row, col, num);
    core->table[row][col].confirmed_num = old;
    return conflict;
}

cmd_status_t cmd_set(core_t *core, char **args)
{
    int row = 0;
    int col = 0;
    int num = 0;

    if (!parse_coords(args[1], &row, &col))
        return CMD_ERROR;
    if (!parse_int(args[2], 1, 9, &num)) {
        fprintf(stderr, "Invalid number '%s': expected 1-9\n", args[2]);
        return CMD_ERROR;
    }
    if (has_conflict(core, row, col, num)) {
        fprintf(stderr, "%d is already in that row, column or block\n", num);
        return CMD_ERROR;
    }
    core->table[row][col].confirmed_num = num;
    refresh_possibilities(core);
    print_table(core, stdout);
    return CMD_OK;
}

cmd_status_t cmd_clear(core_t *core, char **args)
{
    int row = 0;
    int col = 0;

    if (!parse_coords(args[1], &row, &col))
        return CMD_ERROR;
    core->table[row][col].confirmed_num = 0;
    refresh_possibilities(core);
    print_table(core, stdout);
    return CMD_OK;
}
