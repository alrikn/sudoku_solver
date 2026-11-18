#include "commands.h"
#include <stdio.h>
#include <stdlib.h>

/* reads a whole-string integer in [min, max] */
bool parse_int(const char *arg, int min, int max, int *out)
{
    char *end = NULL;
    long value = strtol(arg, &end, 10);

    if (end == arg || *end != '\0' || value < min || value > max)
        return false;
    *out = (int)value;
    return true;
}

/*
** reads "x,y" (0-based, x = column, y = row).
** prints the error itself so every command reports it the same way.
*/
bool parse_coords(const char *arg, int *row, int *col)
{
    int x = 0;
    int y = 0;
    char extra = '\0';

    if (sscanf(arg, "%d,%d%c", &x, &y, &extra) != 2 ||
        x < 0 || x > 8 || y < 0 || y > 8) {
        fprintf(stderr, "Invalid position '%s': expected x,y in 0-8\n", arg);
        return false;
    }
    *col = x;
    *row = y;
    return true;
}
