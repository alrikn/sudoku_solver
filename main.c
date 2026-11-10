#include "struct.h"
#include <stdio.h>
#include <stdlib.h>

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

void free_possibilities(poss_t *poss)
{
    poss_t *current = poss;
    while (current != NULL) {
        poss_t *next = current->next;
        free(current);
        current = next;
    }
}

poss_t *create_possibility(int possibility)
{
    poss_t *new_poss = malloc(sizeof(poss_t));
    if (new_poss == NULL) {
        fprintf(stderr, "Memory allocation failed for possibility\n");
        return NULL;
    }
    new_poss->possibility = possibility;
    new_poss->next = NULL;
    new_poss->prev = NULL;
    return new_poss;
}

void add_possibility(spot_t *spot, int possibility)
{
    poss_t *new_poss = create_possibility(possibility);

    if (new_poss == NULL) {
        return;
    }
    if (spot->possibilities == NULL) {
        spot->possibilities = new_poss;
    } else {
        poss_t *current = spot->possibilities;
        while (current->next != NULL)
            current = current->next;
        current->next = new_poss;
        new_poss->prev = current;
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


int main_loop(core_t *core)
{
    // This is where the main logic of the Sudoku solver would go.
    // For now, we will just print the initial table.
    print_table(core);
    return 0;
}


int main()
{
    core_t core = {0};
    char *test_table[9] = {
        "5..4673.9",
        "9.381.427",
        "1742.3...",
        "231976854",
        "857124.9.",
        "4963.8172",
        "....8926.",
        "782641..5",
        ".1....7.8"
    };

    parse_table(&core, test_table);
    print_table(&core);
    return 0;
}
