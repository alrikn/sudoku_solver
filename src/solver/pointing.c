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
    int pointing_row = block_row_start + (row % 3); //gives the row of the block that is in the same row as (row, col)
    int temp_row = 0;
    int temp_col = 0;
    poss_t *current = NULL;
    bool row_is_pointing = true; //assume the row is taken until we find a block that doesn't take it
    int count = 0;

    load_block(core, row, col);
    //first we check that the num is not already confirmed in the block
    for (int i = 0; i < 9; i++) {
        if (core->block[i / 3][i % 3].confirmed_num == num)
            return false;
    }
    //then we check that all the possibilities for num in the block are on the same row
    for (int i = 0; i < 9; i++) {
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
    //then we check that there are more than 2 possibilities for num in the block, otherwise it is not a pointing row
    // (if that doesn't happen, smth has gone very wron g somehwre, this just sanity check)
    if (count > 3) {
        printf("Error: pointing_row: count of possibilities for num %d in block is %d, expected 2 or 3\n", num, count);
        return false;
    }
    if (!row_is_pointing)
        return false;
    //now we go look at the other blocks in the same horizontal band,
    // and check if they have any possibilities for num on the same row
    //and if they do, we remove them, because the row is already taken by the block that is pointing
    for (int block_col = 0; block_col < 3; block_col++) {
        if (block_col == block_col_start)
            continue;
        load_block(core, block_row_start * 3, block_col * 3);
        for (int i = 0; i < 9; i++) {
            temp_row = i / 3;
            temp_col = i % 3;
            if (temp_row == pointing_row) {
                current = core->block[temp_row][temp_col].possibilities;
                while (current != NULL) {
                    if (current->possibility == num) {
                        printf("Pointing elimination: %d is already in block (%d, %d), so it cannot be at (%d, %d)\n", num, block_row_start, block_col, row, col);
                        return true;
                    }
                    current = current->next;
                }
            }
        }
    }
    return false;
}
