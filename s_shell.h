#ifndef S_SHELL_H
#define S_SHELL_H

/* lists of all prototype variable names */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>


#define END_OF_FILE -2
#define EXIT -3

/**
 * struct the_sh_args - this is where the arguments and also
 * the variables for the shell are stored
 * @rd_fd: this is the descriptor of file to be read
 * @history_c: total number of command in history of the shell
 * @way_path: the PATH of through the command goes
 * @num_error: the error number designated to failed commands
 * @for_status: this states the status of the command on exit
 * @argc: counted number of arg in a command
 * @type_buff_cmd: this states the type of command china
 * @flag_count_ln: this flag show if a command is for a line count
 * @change_surr: this flag indicates if an env variable has changed
 * @arg: cmd that we want to execute
 * @fname: this is the file name for a particular cmd
 * @argv: an argument's array of pointer for cmd
 * @surround: env variables linked list
 * @buff_cmd: buffer pointer that stores cmd chain
 * @surr: this is the env array of pointers
 * @past: previous cmd linked list
 * @a_alias: the aliases linked list
 */

typedef struct the_sh_args
{
	unsigned int count_ln;
	int rd_fd;
	int history_c;
	char *way_path;
	int num_error;
	int for_status;
	int argc;
	int type_buff_cmd;
	int flag_count_ln;
	int change_surr;
	char *arg;
	char *fname;
	char **argv;
	char **surround;
	char **buff_cmd;
	l_list *surr;
	l_list *past;
	l_list *a_alias;	
} shell_args;


/* hsh_control1 */

int created_shell(shell_args *, char **);
int find_root(shell_args *);
void created_fork(shell_args *);
void search_execcmd(shell_args *);

/* hsh_control */
int interactiv(shell_args *);
int delimiter(char, char *);

#endif /* S_SHELL_H */
