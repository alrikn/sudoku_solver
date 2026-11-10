#include "sudoku.h"
#include <stdio.h>
#include <stdbool.h>

//
void initialise_table(core_t *core)
{
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            core->table[i][j].confirmed_num = 0;
            core->table[i][j].possibilities = NULL;
        }
    }
}

/*
in the future this will actually parse stuff,
for now its hard coded to test the rest of the program
*/
void parse_table(core_t *core, char **table)
{
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (table[i][j] == '.') {
                core->table[i][j].confirmed_num = 0;
                core->table[i][j].possibilities = NULL;
                continue;
            }
            core->table[i][j].confirmed_num = table[i][j] - '0';
            core->table[i][j].possibilities = NULL;
        }
    }

}

/*
** copies a 3x3 block from the main table into the block array in core_t.
** takes top left corner of the block as input (block_row, block_col) where each is 0, 1, or 2.
*/
void copy_block(core_t *core, int block_row, int block_col)
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            core->block[i][j] = core->table[block_row * 3 + i][block_col * 3 + j];
        }
    }
}

void print_table(core_t *core)
{
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (core->table[i][j].confirmed_num != 0) {
                printf("%d", core->table[i][j].confirmed_num);
            } else
                printf(".");
            if (j == 2 || j == 5)
                printf("|");
        }
        if (i == 2 || i == 5)
            printf("\n---+---+---");
        printf("\n");
    }
}

int number_exists_in_column(core_t *core, int col, int num)
{
    for (int i = 0; i < 9; i++) {
        if (core->table[i][col].confirmed_num == num) {
            return true;
        }
    }
    return false;
}

int number_exists_in_row(core_t *core, int row, int num)
{
    for (int j = 0; j < 9; j++) {
        if (core->table[row][j].confirmed_num == num) {
            return true;
        }
    }
    return false;
}

int number_exists_in_block(core_t *core, int row, int col, int num)
{
    int block_row_start = (row / 3) * 3;
    int block_col_start = (col / 3) * 3;

    for (int i = block_row_start; i < block_row_start + 3; i++) {
        for (int j = block_col_start; j < block_col_start + 3; j++) {
            if (core->table[i][j].confirmed_num == num) {
                return true;
            }
        }
    }
    return false;
}
