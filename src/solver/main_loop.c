#include "sudoku.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/*
** This is where the main logic of the Sudoku solver goes.
*/
int main_loop(core_t *core)
{
    char input[10];

    populate_possibilities(core);
    while (true) {
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
