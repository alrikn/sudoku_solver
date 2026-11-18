#include "sudoku.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

/* replaces what is on the prompt line with text */
void show_input(input_t *in, const char *text)
{
    snprintf(in->buf, INPUT_MAX, "%s", text);
    in->len = strlen(in->buf);
    printf("\r\033[K> %s", in->buf);
    fflush(stdout);
}

static void erase_char(input_t *in)
{
    in->len--;
    in->buf[in->len] = '\0';
    printf("\b \b");
}

static void insert_char(input_t *in, char c)
{
    in->buf[in->len] = c;
    in->len++;
    in->buf[in->len] = '\0';
    putchar(c);
}

/* returns 1 when the line is done, -1 on Ctrl+D on an empty line */
static int handle_key(core_t *core, input_t *in, char c)
{
    char seq[2] = {0};

    if (c == '\n' || c == '\r')
        return 1;
    if (c == 4 && in->len == 0)
        return -1;
    if ((c == 127 || c == '\b') && in->len > 0)
        erase_char(in);
    if (c == 27 && read(STDIN_FILENO, seq, 2) == 2 && seq[0] == '[') {
        if (seq[1] == 'A')
            history_up(core, in);
        if (seq[1] == 'B')
            history_down(in);
    }
    if (c >= ' ' && c < 127 && in->len < INPUT_MAX - 1)
        insert_char(in, c);
    fflush(stdout);
    return 0;
}

static char *read_raw(core_t *core)
{
    struct termios old;
    struct termios raw;
    input_t in = {0};
    char c = 0;
    int done = 0;

    tcgetattr(STDIN_FILENO, &old);
    raw = old;
    raw.c_lflag &= ~(ICANON | ECHO);
    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    while (done == 0)
        done = read(STDIN_FILENO, &c, 1) == 1 ? handle_key(core, &in, c) : -1;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &old);
    printf("\n");
    return done == 1 ? strdup(in.buf) : NULL;
}

/*
** prints the prompt and returns the typed line (to free), NULL at the end
** of input. on a terminal, up / down go through the history; otherwise
** (input piped from a file) lines are read as they are.
*/
char *read_input(core_t *core)
{
    char *line = NULL;
    size_t size = 0;

    printf("> ");
    fflush(stdout);
    if (isatty(STDIN_FILENO))
        return read_raw(core);
    if (getline(&line, &size, stdin) == -1) {
        free(line);
        printf("\n");
        return NULL;
    }
    return line;
}
