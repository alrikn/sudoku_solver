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

static void parse_row(core_t *core, char *line, int i)
{
    for (int j = 0; j < 9; j++) {
        core->table[i][j].possibilities = NULL;
        if (line[j] == '.')
            core->table[i][j].confirmed_num = 0;
        else
            core->table[i][j].confirmed_num = line[j] - '0';
    }
}

/*
in the future this will actually parse stuff,
for now its hard coded to test the rest of the program
*/
void parse_table(core_t *core, char **table)
{
    for (int i = 0; i < 9; i++)
        parse_row(core, table[i], i);
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

static void print_row(core_t *core, int i)
{
    for (int j = 0; j < 9; j++) {
        if (core->table[i][j].confirmed_num != 0)
            printf("%d", core->table[i][j].confirmed_num);
        else
            printf(".");
        if (j == 2 || j == 5)
            printf("|");
    }
}

void print_table(core_t *core)
{
    for (int i = 0; i < 9; i++) {
        print_row(core, i);
        if (i == 2 || i == 5)
            printf("\n---+---+---");
        printf("\n");
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
