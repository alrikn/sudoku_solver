#include "sudoku.h"
#include <stdbool.h>
#include <stdio.h>

/*
** Pointing elimination: num can be ruled out at (row, col) when another
** block sharing its row (or column) has every possibility for num on that
** same row (or column). num must end up there inside that block, so it
** cannot go anywhere else on the line, including at (row, col).
**
** A block where num is already confirmed does not claim anything.
*/

/*
** true if every possibility for num in core->block lies on 'line'
** (a row of the block, or a column if is_col), with at least two of them.
** a single one is a hidden single, already handled by hidden.c.
*/
static bool block_points(core_t *core, int num, int line, bool is_col)
{
    int count = 0;
    int cell_line = 0;

    for (int i = 0; i < 9; i++) {
        if (!has_possibility(&core->block[i / 3][i % 3], num))
            continue;
        cell_line = is_col ? i % 3 : i / 3;
        if (cell_line != line)
            return false;
        count++;
    }
    return count > 1;
}

/* checks the other blocks of the horizontal band */
bool pointing_row(core_t *core, int row, int col, int num)
{
    for (int block_col = 0; block_col < 3; block_col++) {
        if (block_col == col / 3 ||
            number_exists_in_block(core, row, block_col * 3, num))
            continue;
        load_block(core, row, block_col * 3);
        if (block_points(core, num, row % 3, false))
            return true;
    }
    return false;
}

/* checks the other blocks of the vertical stack */
bool pointing_col(core_t *core, int row, int col, int num)
{
    for (int block_row = 0; block_row < 3; block_row++) {
        if (block_row == row / 3 ||
            number_exists_in_block(core, block_row * 3, col, num))
            continue;
        load_block(core, block_row * 3, col);
        if (block_points(core, num, col % 3, true)) {
            return true;
        }
    }
    return false;
}
