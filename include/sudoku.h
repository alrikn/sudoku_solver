#ifndef SUDOKU_H
    #define SUDOKU_H

    #include "struct.h"

// possibility.c
void free_possibilities(poss_t *poss);
poss_t *create_possibility(int possibility);
poss_t *add_possibility(spot_t *spot, int possibility);
poss_t *remove_possibility(spot_t *spot, int possibility);

// table.c
void initialise_table(core_t *core);
void parse_table(core_t *core, char **table);
void copy_block(core_t *core, int block_row, int block_col);
void print_table(core_t *core);

// checks.c
int number_exists_in_column(core_t *core, int col, int num);
int number_exists_in_row(core_t *core, int row, int num);
int number_exists_in_block(core_t *core, int row, int col, int num);

// solver.c
int populate_possibilities(core_t *core);
int row_possibility_taken(core_t *core, int row, int col, int num);
int prune_possibilities(core_t *core);
int confirm_single_possibilities(core_t *core);
int main_loop(core_t *core);

#endif
