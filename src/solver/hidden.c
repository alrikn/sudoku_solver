#include "sudoku.h"
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>

static bool has_possibility(spot_t *spot, int num)
{
    poss_t *current = spot->possibilities;

    while (current != NULL) {
        if (current->possibility == num)
            return true;
        current = current->next;
    }
    return false;
}

static void place_number(spot_t *spot, int num)
{
    spot->confirmed_num = num;
    free_possibilities(spot->possibilities);
    spot->possibilities = NULL;
}

int find_last_col_for_hidden_row(core_t *core, int row, int num, int *count)
{
    int last_col = -1;

    for (int col = 0; col < 9; col++) {
        if (has_possibility(&core->table[row][col], num)) {
            last_col = col;
            *count += 1;
        }
    }
    return last_col;
}

/*
if there there is a number that is not on the row,
and the number has only a single possibility on that row,
then that number must be confirmed at that position.
*/
bool confirm_single_hidden_row(core_t *core, int row)
{
    int count = 0;
    int last_col = -1;

    for (int num = 1; num <= 9; num++) {
        if (number_exists_in_row(core, row, num))
            continue;
        count = 0;
        last_col = find_last_col_for_hidden_row(core, row, num, &count);
        if (count == 1) {
            printf("Confirmed number (hidden row) %d at position (%d, %d)\n",
                num, row, last_col);
            place_number(&core->table[row][last_col], num);
            return true;
        }
    }
    return false;
}

int find_last_row_for_hidden_column(core_t *core, int col, int num, int *count)
{
    int last_row = -1;

    for (int row = 0; row < 9; row++) {
        if (has_possibility(&core->table[row][col], num)) {
            last_row = row;
            *count += 1;
        }
    }
    return last_row;
}

bool confirm_single_hidden_column(core_t *core, int col)
{
    int count = 0;
    int last_row = -1;

    for (int num = 1; num <= 9; num++) {
        if (number_exists_in_column(core, col, num))
            continue;
        count = 0;
        last_row = find_last_row_for_hidden_column(core, col, num, &count);
        if (count == 1) {
            printf("Confirmed number (hidden column) %d at position (%d, %d)\n",
                num, last_row, col);
            place_number(&core->table[last_row][col], num);
            return true;
        }
    }
    return false;
}

/*
** returns the index (0-8, row by row) of the last cell of core->block
** that can hold num, or -1. count is set to how many cells can hold it.
*/
static int find_last_in_block(core_t *core, int num, int *count)
{
    int last = -1;

    *count = 0;
    for (int i = 0; i < 9; i++) {
        if (has_possibility(&core->block[i / 3][i % 3], num)) {
            last = i;
            *count += 1;
        }
    }
    return last;
}

bool confirm_single_hidden_block(core_t *core, int row, int col)
{
    int count = 0;
    int last = -1;
    int last_row = -1;
    int last_col = -1;

    load_block(core, row, col);
    for (int num = 1; num <= 9; num++) {
        if (number_exists_in_block(core, row, col, num))
            continue;
        last = find_last_in_block(core, num, &count);
        if (count == 1) {
            last_row = row / 3 * 3 + last / 3;
            last_col = col / 3 * 3 + last % 3;
            printf("Confirmed number (hidden block) %d at position (%d, %d)\n",
                num, last_row, last_col);
            place_number(&core->table[last_row][last_col], num);
            return true;
        }
    }
    return false;
}
