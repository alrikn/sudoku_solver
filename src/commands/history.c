#include "sudoku.h"
#include <stdlib.h>
#include <string.h>

/*
** core->prev is the newest entry, each entry's prev is the one before it.
*/

static bool is_blank(const char *line)
{
    return line[strspn(line, " \t\r\n")] == '\0';
}

/*
** stores a copy of line (without its trailing newline) as the newest entry.
** blank lines are not stored, and repeating the last command reuses its
** entry. returns the entry so the caller can set its status, or NULL.
*/
command_history_t *history_add(core_t *core, const char *line)
{
    command_history_t *entry = NULL;
    size_t len = strcspn(line, "\r\n");

    if (is_blank(line))
        return NULL;
    if (core->prev != NULL && strlen(core->prev->line) == len
        && strncmp(core->prev->line, line, len) == 0)
        return core->prev;
    entry = calloc(1, sizeof(command_history_t));
    if (entry == NULL)
        return NULL;
    entry->line = strndup(line, len);
    if (entry->line == NULL) {
        free(entry);
        return NULL;
    }
    entry->prev = core->prev;
    if (core->prev != NULL)
        core->prev->next = entry;
    core->prev = entry;
    return entry;
}

void history_free(core_t *core)
{
    command_history_t *entry = core->prev;
    command_history_t *prev = NULL;

    while (entry != NULL) {
        prev = entry->prev;
        free(entry->line);
        free(entry);
        entry = prev;
    }
    core->prev = NULL;
}
