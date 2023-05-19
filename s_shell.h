#ifndef S_SHELL_H
#define S_SHELL_H

#include <limits.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>

#define END_OF_FILE -2
#define EXIT -3

#define BUF_FLUSH -1
#define WRITE_BUF_SIZE 1024
#define READ_BUF_SIZE 1024

#define CONVERT_UNSIGNED 	2
#define CONVERT_LOWERCASE	1


extern char **surround;

/* lists of all prototype variable names */

/**
 * struct the_shell_args - this is where the arguments and also
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
 * @a_v: an argument's array of pointer for cmd
 * @surround: env variables linked list
 * @buff_cmd: buffer pointer that stores cmd chain
 * @surr: this is the env array of pointers
 * @past: previous cmd linked list
 * @a_alias: the aliases linked list
 */


typedef struct the_shell_args
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
	char **a_v;
	char **surround;
	char **buff_cmd;
	l_list *surr;
	l_list *past;
	l_list *a_alias;	
} shell_args;

/**
 * struct l_list - reps singly linked list
 * @string: my string
 * @num: field num
 * @lnk: points to the next node
 */

typedef struct l_list
{
	int num;
	char *string;
	struct l_list *lnk;
} l_list;



/* hsh_control1 */

int find_root(shell_args *);
void created_fork(shell_args *);
void search_execcmd(shell_args *);

/* hsh_control */
int interactiv(shell_args *element);
int delimiter(char val, char *d_delim);
int created_shell(shell_args *element, char **a_v);


/*env_ctrls */
int *getenv_cpy(shell_args *, const char *);


/* parse_ctrls */
int file_exec(shell_args *, char *);
char *search_execpath(shell_args, char *, char *);


/* err_ctrl */
void error_msg_print(shell_args *, char *);


/* obtain_info */

void clear_shell_args(shell_args *);
void enter_shell_args(shell_args *, char **);
void empty_shell_args(shell_args *, int);


/* buff_ctrl */
void list_buffer(char);



/* obtain_line */
ssize_t pro_in(shell_args *);



/* obtain_hist */
int list_shell_hist(shell_args *element);



/* history_l */
int print_cmd_hist(shell_args *);



/* obtain_env */
char **obtain_env(shell_args *);



/* exit_fnct */
int s_shell_exit(shell_args *);
int cmd_help(shell_args *);
int cd_dir(shell_args *);


/* env_ctrl */
int env_cpy(shell_args *);
int env_apply(shell_args *);
int env_unapply(shell_args *);



/* ali_as */
int cpy_alias(shell_args *);



/* strings_ctrl1 */
int string_cmp(char *, char *);

#endif /* S_SHELL_H */
