#include "sudoku.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
** File format: 9 rows of 9 cells. A cell is 1-9, or '.' / '0' when empty.
** '|', spaces and lines made only of '-' and '+' (or empty lines) are
** ignored, so the output of print_table can be read back.
*/

static bool is_separator(const char *line)
{
    for (int i = 0; line[i] != '\0'; i++) {
        if (strchr("-+ \t\r\n", line[i]) == NULL)
            return false;
    }
    return true;
}

static bool parse_cell(char c, int *value)
{
    if (c == '.' || c == '0') {
        *value = 0;
        return true;
    }
    if (c >= '1' && c <= '9') {
        *value = c - '0';
        return true;
    }
    return false;
}

static bool parse_line(spot_t table[9][9], int row, const char *line,
    int line_num)
{
    int col = 0;
    int value = 0;
    bool valid = row < 9;

    for (int i = 0; valid && line[i] != '\0' && line[i] != '\n'; i++) {
        if (strchr("| \t\r", line[i]) != NULL)
            continue;
        valid = col < 9 && parse_cell(line[i], &value);
        if (valid) {
            table[row][col].confirmed_num = value;
            col++;
        }
    }
    if (row >= 9)
        fprintf(stderr, "Line %d: more than 9 rows\n", line_num);
    else if (!valid || col != 9)
        fprintf(stderr, "Line %d: expected 9 cells (1-9, '.' or '0')\n",
            line_num);
    return valid && col == 9;
}

static bool parse_stream(spot_t table[9][9], FILE *file)
{
    char *line = NULL;
    size_t size = 0;
    int row = 0;
    int line_num = 0;
    bool ok = true;

    while (ok && getline(&line, &size, file) != -1) {
        line_num++;
        if (is_separator(line))
            continue;
        ok = parse_line(table, row, line, line_num);
        row++;
    }
    free(line);
    if (ok && row != 9)
        fprintf(stderr, "Expected 9 rows, found %d\n", row);
    return ok && row == 9;
}

/*
** parses into a temporary table first, so a bad file leaves
** the current sudoku untouched.
*/
bool load_file(core_t *core, const char *path)
{
    FILE *file = fopen(path, "r");
    spot_t table[9][9] = {0};
    bool ok = false;

    if (file == NULL) {
        perror(path);
        return false;
    }
    ok = parse_stream(table, file);
    fclose(file);
    if (!ok)
        return false;
    free_all_possibilities(core);
    memcpy(core->table, table, sizeof(table));
    populate_possibilities(core);
    return true;
}
