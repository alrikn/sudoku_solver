#include "sudoku.h"
#include <stdbool.h>
#include <stddef.h>

int number_exists_in_column(core_t *core, int col, int num)
{
    for (int i = 0; i < 9; i++) {
        if (core->table[i][col].confirmed_num == num)
            return true;
    }
    return false;
}

int number_exists_in_row(core_t *core, int row, int num)
{
    for (int j = 0; j < 9; j++) {
        if (core->table[row][j].confirmed_num == num)
            return true;
    }
    return false;
}

int number_exists_in_block(core_t *core, int row, int col, int num)
{
    int block_row_start = (row / 3) * 3;
    int block_col_start = (col / 3) * 3;
    spot_t *spot = NULL;

    for (int k = 0; k < 9; k++) {
        spot = &core->table[block_row_start + k / 3][block_col_start + k % 3];
        if (spot->confirmed_num == num)
            return true;
    }
    return false;
}
