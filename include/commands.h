#ifndef COMMANDS_H
    #define COMMANDS_H

    //#include "sudoku.h"
    #include <stdbool.h>
    #include <stddef.h>

    /* max number of words on a command line, command name included */
    #define MAX_ARGS 4
    /* max length of a line typed at the prompt */
    #define INPUT_MAX 256

typedef struct core_s core_t;

typedef enum cmd_status_e {
    CMD_OK,
    CMD_ERROR,
    CMD_EXIT
} cmd_status_t;

/*
** One entry of the command table (see src/commands/dispatch.c).
** args[0] is the command name, args[1..] its arguments, NULL terminated.
** min_args / max_args do not count the command name, and are checked
** before run is called, so handlers can use args[1..min_args] directly.
*/
typedef struct command_s {
    const char *name;
    int min_args;
    int max_args;
    const char *usage;
    const char *help;
    cmd_status_t (*run)(core_t *core, char **args);
} command_t;

typedef struct command_history_s {
    char *line;
    cmd_status_t status;
    //cus we want to be able to go back in history
    struct command_history_s *prev;
    struct command_history_s *next; // newer entry, for the down arrow
} command_history_t;

/*
** the line being typed (see src/commands/input.c).
** pos: the history entry shown, NULL while on the line being typed.
** draft: what was typed before going up, given back when coming down.
*/
typedef struct input_s {
    char buf[INPUT_MAX];
    size_t len;
    char draft[INPUT_MAX];
    command_history_t *pos;
} input_t;

// src/commands/history.c
command_history_t *history_add(core_t *core, const char *line);
void history_free(core_t *core);
void history_up(core_t *core, input_t *in);
void history_down(input_t *in);

// src/commands/input.c
void show_input(input_t *in, const char *text);
char *read_input(core_t *core);

// src/commands/dispatch.c
cmd_status_t execute_command(core_t *core, char *line);
cmd_status_t cmd_help(core_t *core, char **args);

// src/commands/args.c
bool parse_int(const char *arg, int min, int max, int *out);
bool parse_coords(const char *arg, int *row, int *col);

// src/commands/cmd_solver.c
cmd_status_t cmd_step(core_t *core, char **args);
cmd_status_t cmd_solve(core_t *core, char **args);
cmd_status_t cmd_exit(core_t *core, char **args);

// src/commands/cmd_io.c
cmd_status_t cmd_read(core_t *core, char **args);
cmd_status_t cmd_write(core_t *core, char **args);
cmd_status_t cmd_print(core_t *core, char **args);

// src/commands/cmd_inspect.c
cmd_status_t cmd_print_pos(core_t *core, char **args);

// src/commands/cmd_edit.c
cmd_status_t cmd_set(core_t *core, char **args);
cmd_status_t cmd_clear(core_t *core, char **args);

// src/commands/cmd_sanity.c
cmd_status_t cmd_sanity(core_t *core, char **args);

#endif
