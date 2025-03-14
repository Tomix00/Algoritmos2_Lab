#ifndef _HELPERS_H
#define _HELPERS_H

#include <stdio.h>


char *readline(FILE *file);

char *readline_from_stdin(void);
/*
 * Read the user input from standard input until a newline is detected,
 * and return the corresponding (dinamically allocated) string.
 *
 * The caller to this function is responsible for the allocated memory.
 *
 * POST: A new null-terminated string is returned with the content read from
 * standard input, or NULL if there was an error.
 */

#endif
