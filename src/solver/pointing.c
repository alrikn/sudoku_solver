#include "sudoku.h"
#include <stdbool.h>
#include <stddef.h>

/*
** Pointing elimination: checks whether num can be ruled out at (row, col)
** because a neighbouring block has already claimed that row for num.
**
** Look at the two other blocks in the same horizontal band (the blocks that
** share rows with ours). If, in one of them, every possibility for num lies
** on the same row, then num must end up on that row inside that block.
** So if that row is 'row', num cannot go anywhere else on it, including
** at (row, col).
**
** A block where num is already confirmed has no possibilities for it, and
** must not count as claiming the row.
**
** Returns true if num is ruled out at (row, col), false otherwise.
**
** TODO: figure out a better name for this function
** Plan: first, figure out which block we are in (block_row_start,
** block_col_start), then copy the other blocks into the block array in
** core_t, so we can work with it more easily.
** row_is_taken might need to start as true.
*/
int row_possibility_taken(core_t *core, int row, int col, int num)
{
    int block_row_start = (row / 3) * 3;
    int block_col_start = (col / 3) * 3;
    poss_t *current = NULL;
    bool row_is_taken = false;

    return 0;
}
