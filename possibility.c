#include "sudoku.h"
#include <stdio.h>
#include <stdlib.h>

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
