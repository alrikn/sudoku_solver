#include "sudoku.h"
#include <stdio.h>
#include <stddef.h>

bool confirm_spot(spot_t *spot, int row, int col)
{
    if (spot->confirmed_num != 0 || spot->possibilities == NULL ||
        spot->possibilities->next != NULL)
        return false;
    spot->confirmed_num = spot->possibilities->possibility;
    printf("Confirmed number (elimination) %d at position (%d, %d)\n",
        spot->confirmed_num, row, col);
    free_possibilities(spot->possibilities);
    spot->possibilities = NULL;
    return true;
}

/* tries each technique on one cell, in order, stops at the first that works */
static bool confirm_cell(core_t *core, int row, int col)
{
    return confirm_spot(&core->table[row][col], row, col)
        || confirm_single_hidden_column(core, col)
        || confirm_single_hidden_block(core, row, col);
}

static bool confirm_row(core_t *core, int row)
{
    if (confirm_single_hidden_row(core, row))
        return true;
    for (int col = 0; col < 9; col++) {
        if (confirm_cell(core, row, col))
            return true;
    }
    return false;
}

int confirm_single_possibilities(core_t *core)
{
    for (int row = 0; row < 9; row++) {
        if (confirm_row(core, row))
            return true;
    }
    return false;
}
