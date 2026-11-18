#include "commands.h"
#include <stdio.h>

cmd_status_t cmd_print_pos(core_t *core, char **args)
{
    int row = 0;
    int col = 0;
    spot_t *spot = NULL;

    if (!parse_coords(args[1], &row, &col))
        return CMD_ERROR;
    spot = &core->table[row][col];
    if (spot->confirmed_num != 0) {
        printf("(%d,%d) is confirmed: %d\n", col, row, spot->confirmed_num);
        return CMD_OK;
    }
    printf("(%d,%d) possibilities:", col, row);
    if (spot->possibilities == NULL)
        printf(" none");
    for (poss_t *p = spot->possibilities; p != NULL; p = p->next)
        printf(" %d", p->possibility);
    printf("\n");
    return CMD_OK;
}
