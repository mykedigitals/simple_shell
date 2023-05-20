#include "s_shell.h"

/**
 * delimiter - it is a checker if a particular content is
 * a delimiter character
 * @val: this is the content to be checked
 * @d_delim: the content of the delimiter
 *
 * Return: this returns 1 if true and 0 if it is false
 */

int delimiter(char val, char *d_delim)
{
        while (*d_delim)
                if (*d_delim++ == val)
                        return (1);
        return (0);
}

/**
 * interactiv - the shell is checked if it is in interactive mode
 * @element: this is the parameter for struct
 *
 * Return: it returns one(1) if element is in interactive mode
 */

int interactiv(shell_args *element)
{
        return (isatty(STDIN_FILENO) && element->rd_fd <= 2);
}

