#include "sudoku.h"
#include <stddef.h>

static void prune_spot(core_t *core, int row, int col)
{
    spot_t *spot = &core->table[row][col];
    poss_t *current = spot->possibilities;
    int num = 0;

    if (spot->confirmed_num != 0)
        return;
    while (current != NULL) {
        num = current->possibility;
        if (number_exists_in_row(core, row, num) ||
            number_exists_in_column(core, col, num) ||
            number_exists_in_block(core, row, col, num) ||
            pointing_row(core, row, col, num))
            current = remove_possibility(spot, num);
        else
            current = current->next;
    }
}

int prune_possibilities(core_t *core)
{
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++)
            prune_spot(core, row, col);
    }
    return 0;
}
