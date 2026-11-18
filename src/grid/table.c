#include "sudoku.h"
#include <stdio.h>

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
** copies a 3x3 block from the main table into the block array in core_t.
** takes top left corner of the block as input (block_row, block_col)
** where each is 0, 1, or 2.
*/
void copy_block(core_t *core, int block_row, int block_col)
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            core->block[i][j] =
                core->table[block_row * 3 + i][block_col * 3 + j];
        }
    }
}

static void print_row(core_t *core, int i, FILE *out)
{
    for (int j = 0; j < 9; j++) {
        if (core->table[i][j].confirmed_num != 0)
            fprintf(out, "%d", core->table[i][j].confirmed_num);
        else
            fprintf(out, ".");
        if (j == 2 || j == 5)
            fprintf(out, "|");
    }
}

/*
** out is stdout for the screen, or a file for the write command.
** the format can be read back by load_file.
*/
void print_table(core_t *core, FILE *out)
{
    for (int i = 0; i < 9; i++) {
        print_row(core, i, out);
        if (i == 2 || i == 5)
            fprintf(out, "\n---+---+---");
        fprintf(out, "\n");
    }
}

/*
based on the row and the col, figures out which block and loads it inside
core block array. This is useful for checking possibilities in a block.
*/
void load_block(core_t * core, int row, int col)
{
    int block_row = row / 3;
    int block_col = col / 3;

    copy_block(core, block_row, block_col);
}
