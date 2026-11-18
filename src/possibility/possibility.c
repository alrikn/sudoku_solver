#include "sudoku.h"
#include <stdio.h>
#include <stdlib.h>

void free_possibilities(poss_t *poss)
{
    poss_t *current = poss;
    poss_t *next = NULL;

    while (current != NULL) {
        next = current->next;
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
    poss_t *current = NULL;

    if (new_poss == NULL)
        return NULL;
    if (spot->possibilities == NULL) {
        spot->possibilities = new_poss;
        return new_poss;
    }
    current = spot->possibilities;
    while (current->next != NULL)
        current = current->next;
    current->next = new_poss;
    new_poss->prev = current;
    return new_poss;
}

static poss_t *find_possibility(poss_t *current, int possibility)
{
    while (current != NULL && current->possibility != possibility)
        current = current->next;
    return current;
}

/**
** Checks if a spot has a specific possibility.
** @param spot The spot to check.
** @param num The number to look for.
** @return true if the spot has the possibility, false otherwise.
*/
bool has_possibility(spot_t *spot, int num)
{
    return find_possibility(spot->possibilities, num) != NULL;
}

/*
** returns the next possibility after the removed one,
** or NULL if it was the last one (or was not found).
*/
poss_t *remove_possibility(spot_t *spot, int possibility)
{
    poss_t *to_remove = find_possibility(spot->possibilities, possibility);
    poss_t *next = NULL;

    if (to_remove == NULL)
        return NULL;
    next = to_remove->next;
    if (to_remove->prev != NULL)
        to_remove->prev->next = next;
    else
        spot->possibilities = next;
    if (next != NULL)
        next->prev = to_remove->prev;
    free(to_remove);
    return next;
}
