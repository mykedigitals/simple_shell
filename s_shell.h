#ifndef S_SHELL_H
#define S_SHELL_H

/* lists of all prototype variable names */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include < sys/wait.h>

#define END_OF_FILE -2
#define EXIT -3


/* hsh_control1 */

int created_shell(shell_args *, char **);
int find_root(shell_args *);
void created_fork(shell_args *);
void search_execcmd(shell_args *);

/* hsh_control */
int interactiv(shell_args *);
int delimiter(char, char *);

#endif /* S_SHELL_H */
