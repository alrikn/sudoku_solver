#ifndef STRUCT_H
    #define STRUCT_H

/* the possibility of a number, with linked list */
typedef struct poss_s {
    int possibility;
    struct poss_s *next;
    struct poss_s *prev;
} poss_t;

/*
** confirmed_num: if we are sure it's this num, that's where we store it.
** if confirmed_num is not 0, then possibilities should be empty.
*/
typedef struct spot_s {
    int confirmed_num;
    poss_t *possibilities;
} spot_t;

/*
** block: for loading a piece of the table,
** to be used if necessary (unsure for now)
*/
typedef struct core_s {
    spot_t table[9][9];
    spot_t block[3][3];
} core_t;

#endif
