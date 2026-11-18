#ifndef SUDOKU_H
    #define SUDOKU_H

    #include "struct.h"
    #include <stdbool.h>
    #include <stdio.h>
    #include <stdbool.h>

// src/possibility/possibility.c
void free_possibilities(poss_t *poss);
poss_t *create_possibility(int possibility);
poss_t *add_possibility(spot_t *spot, int possibility);
poss_t *remove_possibility(spot_t *spot, int possibility);

// src/grid/table.c
void initialise_table(core_t *core);
void copy_block(core_t *core, int block_row, int block_col);
void print_table(core_t *core, FILE *out);
void load_block(core_t *core, int row, int col);

// src/grid/parse.c
bool load_file(core_t *core, const char *path);

// src/grid/checks.c
int number_exists_in_column(core_t *core, int col, int num);
int number_exists_in_row(core_t *core, int row, int num);
int number_exists_in_block(core_t *core, int row, int col, int num);
bool is_solved(core_t *core);

// src/solver/populate.c
int populate_possibilities(core_t *core);
void free_all_possibilities(core_t *core);
void refresh_possibilities(core_t *core);

// src/solver/prune.c
int prune_possibilities(core_t *core);

// src/solver/pointing.c
bool pointing_row(core_t *core, int row, int col, int num);

// src/solver/hidden.c
int find_last_col_for_hidden_row(core_t *core, int row, int num, int *count);
bool confirm_single_hidden_row(core_t *core, int row);
int find_last_row_for_hidden_column(core_t *core, int col, int num, int *count);
bool confirm_single_hidden_column(core_t *core, int col);
bool confirm_single_hidden_block(core_t *core, int row, int col);

// src/solver/confirm.c
int confirm_single_possibilities(core_t *core);

// src/solver/main_loop.c
int main_loop(core_t *core);

#endif
