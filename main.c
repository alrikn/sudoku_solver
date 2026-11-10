#include "sudoku.h"

int main()
{
    core_t core = {0};
    char *test_table[9] = {
        ".5..3..7.",
        "7......2.",
        "1.3.....6",
        "..965.2..",
        "36.2....7",
        ".....1..8",
        "....6.5..",
        "89..4....",
        ".......4."
    };

    parse_table(&core, test_table);
    print_table(&core);
    main_loop(&core);
    return 0;
}
