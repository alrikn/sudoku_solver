#include "sudoku.h"

static void populate_spot(core_t *core, int row, int col)
{
    spot_t *spot = &core->table[row][col];

    if (spot->confirmed_num != 0)
        return;
    for (int num = 1; num <= 9; num++) {
        if (!number_exists_in_row(core, row, num) &&
            !number_exists_in_column(core, col, num) &&
            !number_exists_in_block(core, row, col, num))
            add_possibility(spot, num);
    }
}

/*
** this does the logic. every spot that could have a number
** gets added to possibilities list.
*/
int populate_possibilities(core_t *core)
{
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            populate_spot(core, row, col);
        }
    }
    return 0;
}
