#include "commands.h"
#include "sudoku.h"
#include <stdio.h>

/*
** checks one unit (row, column or block) given as 9 cells:
** - a confirmed number appearing more than once
** - a number neither confirmed nor possible anywhere in the unit
** returns the number of problems found.
*/
static int check_unit(spot_t *cells[9], const char *kind, int index)
{
    int confirmed[10] = {0};
    int candidates[10] = {0};
    int errors = 0;

    for (int k = 0; k < 9; k++) {
        confirmed[cells[k]->confirmed_num]++;
        if (cells[k]->confirmed_num != 0)
            continue;
        for (int n = 1; n <= 9; n++)
            candidates[n] += has_possibility(cells[k], n);
    }
    for (int n = 1; n <= 9; n++) {
        if (confirmed[n] > 1) {
            printf("%s %d: %d appears %d times\n", kind, index, n,
                confirmed[n]);
            errors++;
        }
        if (confirmed[n] == 0 && candidates[n] == 0) {
            printf("%s %d: %d has nowhere to go\n", kind, index, n);
            errors++;
        }
    }
    return errors;
}

/* empty cells with no possibilities left */
static int check_dead_cells(core_t *core)
{
    int errors = 0;
    spot_t *spot = NULL;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            spot = &core->table[i][j];
            if (spot->confirmed_num == 0 && spot->possibilities == NULL) {
                printf("cell (%d,%d): no possibilities left\n", i + 1, j + 1);
                errors++;
            }
        }
    }
    return errors;
}

cmd_status_t cmd_sanity(core_t *core, char **args)
{
    spot_t *row[9];
    spot_t *col[9];
    spot_t *block[9];
    int errors = check_dead_cells(core);

    (void)args;
    for (int i = 0; i < 9; i++) {
        for (int k = 0; k < 9; k++) {
            row[k] = &core->table[i][k];
            col[k] = &core->table[k][i];
            block[k] = &core->table[(i / 3) * 3 + k / 3][(i % 3) * 3 + k % 3];
        }
        errors += check_unit(row, "row", i);
        errors += check_unit(col, "col", i);
        errors += check_unit(block, "box", i);
    }
    if (errors > 0) {
        printf("%d problem(s) found.\n", errors);
        return CMD_ERROR;
    }
    printf("Grid is valid.\n");
    return CMD_OK;
}
