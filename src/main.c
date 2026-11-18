#include "sudoku.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    core_t core = {0};

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <sudoku_file>\n", argv[0]);
        return 84;
    }
    if (!load_file(&core, argv[1]))
        return 84;
    main_loop(&core);
    free_all_possibilities(&core);
    return 0;
}
