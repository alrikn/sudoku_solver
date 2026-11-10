
#ifndef STRUCT_H
#define STRUCT_H

typedef struct poss_s {
    int possibility;
    struct poss_s *next;
    struct poss_s *prev;
} poss_t; //the possibility of a number, with linked list

typedef struct spot_s {
    int confirmed_num; //if we are sure its this num that where we store its
    poss_t *possibilities;
} spot_t; //if confirmed_num is not 0, then possibities should be empty

typedef struct core_s {
    spot_t table[9][9];
    spot_t block[3][3]; //for loading a piece of the table, to be used if necessary (unsure for now)
} core_t;

#endif
