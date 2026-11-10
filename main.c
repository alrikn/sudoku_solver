#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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

poss_t *add_possibility(spot_t *spot, int possibility)
{
    poss_t *new_poss = create_possibility(possibility);

    if (new_poss == NULL) {
        return NULL;
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
    return new_poss;
}

poss_t *remove_possibility(spot_t *spot, int possibility)
{
    poss_t *current = spot->possibilities;
    poss_t *to_remove = NULL;

    while (current != NULL) {
        if (current->possibility == possibility) {
            to_remove = current;
            break;
        }
        current = current->next;
    }
    if (to_remove != NULL) {
        if (to_remove->prev != NULL) {
            to_remove->prev->next = to_remove->next;
        } else {
            spot->possibilities = to_remove->next;
        }
        if (to_remove->next != NULL) {
            to_remove->next->prev = to_remove->prev;
        }
        current = to_remove->next;
        free(to_remove);
    }
    return current; //return the next possibility after the removed one, or NULL if it was the last one
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

int number_exists_in_column(core_t *core, int col, int num)
{
    for (int i = 0; i < 9; i++) {
        if (core->table[i][col].confirmed_num == num) {
            return true;
        }
    }
    return false;
}

int number_exists_in_row(core_t *core, int row, int num)
{
    for (int j = 0; j < 9; j++) {
        if (core->table[row][j].confirmed_num == num) {
            return true;
        }
    }
    return false;
}

int number_exists_in_block(core_t *core, int row, int col, int num)
{
    int block_row_start = (row / 3) * 3;
    int block_col_start = (col / 3) * 3;

    for (int i = block_row_start; i < block_row_start + 3; i++) {
        for (int j = block_col_start; j < block_col_start + 3; j++) {
            if (core->table[i][j].confirmed_num == num) {
                return true;
            }
        }
    }
    return false;
}

/*
this does the logic. every spot that could have a number gets added to possibilities list.
*/
int populate_possibilities(core_t *core)
{
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (core->table[row][col].confirmed_num == 0) {
                for (int num = 1; num <= 9; num++) {
                    add_possibility(&core->table[row][col], num);
                }
            }
        }
    }
    return 0;
}

int prune_possibilities(core_t *core)
{
    poss_t *current = NULL;

    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (core->table[row][col].confirmed_num == 0) {
                current = core->table[row][col].possibilities;
                while (current != NULL) {
                    int num = current->possibility;
                    if (number_exists_in_row(core, row, num) ||
                        number_exists_in_column(core, col, num) ||
                        number_exists_in_block(core, row, col, num)) {
                        current = remove_possibility(&core->table[row][col], num);
                    } else {
                        current = current->next;
                    }
                }
            }
        }
    }
    return 0;
}

int confirm_single_possibilities(core_t *core)
{
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (core->table[row][col].confirmed_num == 0 &&
                core->table[row][col].possibilities != NULL &&
                core->table[row][col].possibilities->next == NULL) {
                core->table[row][col].confirmed_num =
                    core->table[row][col].possibilities->possibility;
                free_possibilities(core->table[row][col].possibilities);
                core->table[row][col].possibilities = NULL;
                printf("Confirmed number %d at position (%d, %d)\n",
                       core->table[row][col].confirmed_num, row, col);
            }
        }
    }
    return 0;
}


int main_loop(core_t *core)
{
    // This is where the main logic of the Sudoku solver would go.
    // For now, we will just print the initial table.
    while (true) {
        populate_possibilities(core);
        prune_possibilities(core);
        confirm_single_possibilities(core);
        print_table(core);
        printf("Press Enter to continue or type 'exit' to quit: ");
        char input[10];
        fgets(input, sizeof(input), stdin);
        if (strncmp(input, "exit", 4) == 0) {
            break;
        }
    }
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
    main_loop(&core);
    return 0;
}
