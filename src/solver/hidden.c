#include "sudoku.h"
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>

int find_last_col_for_hidden_row(core_t *core, int row, int num, int *count)
{
    int last_col = -1;

    for (int col = 0; col < 9; col++) {
        spot_t *spot = &core->table[row][col];
        poss_t *current = spot->possibilities;
        while (current != NULL) {
            if (current->possibility == num) {
                last_col = col;
                break;
            }
            current = current->next;
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
            spot_t *spot = &core->table[row][last_col];
            spot->confirmed_num = num;
            printf("Confirmed number (hidden row) %d at position (%d, %d)\n",
                num, row, last_col);
            free_possibilities(spot->possibilities);
            spot->possibilities = NULL;
            return true;
        }
    }
    return false;
}

int find_last_row_for_hidden_column(core_t *core, int col, int num, int *count)
{
    int last_row = -1;
    spot_t *spot;
    poss_t *current;

    for (int row = 0; row < 9; row++) {
        spot = &core->table[row][col];
        current = spot->possibilities;
        while (current != NULL) {
            if (current->possibility == num) {
                last_row = row;
                *count += 1;
                break;
            }
            current = current->next;
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
            spot_t *spot = &core->table[last_row][col];
            spot->confirmed_num = num;
            printf("Confirmed number (hidden column) %d at position (%d, %d)\n",
                num, last_row, col);
            free_possibilities(spot->possibilities);
            spot->possibilities = NULL;
            return true;
        }
    }
    return false;
}
