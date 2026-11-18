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
bool pointing_row(core_t *core, int row, int col, int num)
{
    int block_row_start = (row / 3);
    int block_col_start = (col / 3);
    int pointing_row = row % 3; //the row inside core->block that is the same row as (row, col)
    int temp_row = 0;
    int temp_col = 0;
    poss_t *current = NULL;
    bool row_is_pointing = true; //assume the row is taken until we find a block that doesn't take it
    int count = 0;
    bool confirmed = false;

    //look at the other blocks in the same horizontal band. if one of them has
    //all its possibilities for num on our row, num cannot be at (row, col)
    for (int block_col = 0; block_col < 3; block_col++) {
        if (block_col == block_col_start)
            continue;
        load_block(core, block_row_start * 3, block_col * 3);
        row_is_pointing = true;
        count = 0;
        confirmed = false;
        //first we check that the num is not already confirmed in the block
        for (int i = 0; i < 9; i++) {
            if (core->block[i / 3][i % 3].confirmed_num == num)
                confirmed = true;
        }
        if (confirmed)
            continue;
        //then we check that all the possibilities for num in the block are on the same row
        for (int i = 0; i < 9 && row_is_pointing; i++) {
            temp_row = i / 3;
            temp_col = i % 3;
            current = core->block[temp_row][temp_col].possibilities;
            while (current != NULL) {
                if (current->possibility == num) {
                    if (temp_row != pointing_row) {
                        row_is_pointing = false;
                        break;
                    }
                    count++;
                }
                current = current->next;
            }
        }
        if (row_is_pointing && count > 1) { //if its 1 then its a hidden single and thats already taken care of
            return true;
        }
    }
    return false;
}
