#include "sudoku.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

static void populate_spot(spot_t *spot)
{
    if (spot->confirmed_num != 0)
        return;
    for (int num = 1; num <= 9; num++)
        add_possibility(spot, num);
}

/*
** this does the logic. every spot that could have a number
** gets added to possibilities list.
*/
int populate_possibilities(core_t *core)
{
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++)
            populate_spot(&core->table[row][col]);
    }
    return 0;
}

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
            number_exists_in_block(core, row, col, num))
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

static void confirm_spot(spot_t *spot, int row, int col)
{
    if (spot->confirmed_num == 0 && spot->possibilities != NULL &&
        spot->possibilities->next == NULL) {
        spot->confirmed_num = spot->possibilities->possibility;
        printf("Confirmed number %d at position (%d, %d)\n",
            spot->confirmed_num, row, col);
    }
    free_possibilities(spot->possibilities);
    spot->possibilities = NULL;
}

int confirm_single_possibilities(core_t *core)
{
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++)
            confirm_spot(&core->table[row][col], row, col);
    }
    return 0;
}

/*
** This is where the main logic of the Sudoku solver goes.
*/
int main_loop(core_t *core)
{
    char input[10];

    while (true) {
        populate_possibilities(core);
        prune_possibilities(core);
        confirm_single_possibilities(core);
        print_table(core);
        printf("Press Enter to continue or type 'exit' to quit: ");
        fgets(input, sizeof(input), stdin);
        if (strncmp(input, "exit", 4) == 0)
            break;
    }
    print_table(core);
    return 0;
}
