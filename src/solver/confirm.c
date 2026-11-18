#include "sudoku.h"
#include <stdio.h>
#include <stddef.h>

static void confirm_spot(spot_t *spot, int row, int col)
{
    if (spot->confirmed_num != 0 || spot->possibilities == NULL ||
        spot->possibilities->next != NULL)
        return;
    spot->confirmed_num = spot->possibilities->possibility;
    printf("Confirmed number (elimination) %d at position (%d, %d)\n",
        spot->confirmed_num, row, col);
    free_possibilities(spot->possibilities);
    spot->possibilities = NULL;
}

int confirm_single_possibilities(core_t *core)
{
    for (int row = 0; row < 9; row++) {
        confirm_single_hidden_row(core, row);
        for (int col = 0; col < 9; col++) {
            confirm_spot(&core->table[row][col], row, col);
            confirm_single_hidden_column(core, col);
        }
    }
    return 0;
}
