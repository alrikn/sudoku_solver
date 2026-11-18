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

int confirm_single_possibilities(core_t *core)
{
    bool changed = false;

    for (int row = 0; row < 9; row++) {
        changed = confirm_single_hidden_row(core, row);
        if (changed)
            return true;
        for (int col = 0; col < 9; col++) {
            changed = confirm_spot(&core->table[row][col], row, col);
            if (changed)
                return true;
            changed = confirm_single_hidden_column(core, col);
            if (changed)
                return true;
            changed = confirm_single_hidden_block(core, row, col);
            if (changed)
                return true;
        }
    }
    return false;
}
