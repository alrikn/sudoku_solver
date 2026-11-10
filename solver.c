#include "sudoku.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/*
this does the logic. every spot that could have a number gets added to possibilities list.
*/
int populate_possibilities(core_t *core)
{
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (core->table[row][col].confirmed_num == 0) {
                for (int num = 1; num <= 9; num++) {
                    add_possibility(&core->table[row][col], num);
                }
            }
        }
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
*/
int row_possibility_taken(core_t *core, int row, int col, int num) //TODO: figure out a better name for this function
{
    //first, we figure out which block we are in
    int block_row_start = (row / 3) * 3;
    int block_col_start = (col / 3) * 3;
    poss_t *current = NULL;
    bool row_is_taken = false; //might need to start as true

    //first we copy the other blocks into the block array in core_t, so we can work with it more easily

    return 0;
}


int prune_possibilities(core_t *core)
{
    poss_t *current = NULL;

    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (core->table[row][col].confirmed_num == 0) {
                current = core->table[row][col].possibilities;
                while (current != NULL) {
                    int num = current->possibility;
                    if (number_exists_in_row(core, row, num) ||
                        number_exists_in_column(core, col, num) ||
                        number_exists_in_block(core, row, col, num)) {
                        current = remove_possibility(&core->table[row][col], num);
                    } else {
                        current = current->next;
                    }
                }
            }
        }
    }
    return 0;
}

int confirm_single_possibilities(core_t *core)
{
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (core->table[row][col].confirmed_num == 0 &&
                core->table[row][col].possibilities != NULL &&
                core->table[row][col].possibilities->next == NULL) {
                core->table[row][col].confirmed_num =
                    core->table[row][col].possibilities->possibility;
                printf("Confirmed number %d at position (%d, %d)\n",
                       core->table[row][col].confirmed_num, row, col);
            }
            free_possibilities(core->table[row][col].possibilities);
            core->table[row][col].possibilities = NULL;
        }
    }
    return 0;
}


int main_loop(core_t *core)
{
    // This is where the main logic of the Sudoku solver would go.
    // For now, we will just print the initial table.
    while (true) {
        populate_possibilities(core);
        prune_possibilities(core);
        confirm_single_possibilities(core);
        print_table(core);
        printf("Press Enter to continue or type 'exit' to quit: ");
        char input[10];
        fgets(input, sizeof(input), stdin);
        if (strncmp(input, "exit", 4) == 0) {
            break;
        }
    }
    print_table(core);
    return 0;
}
