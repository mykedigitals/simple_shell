#ifndef S_SHELL_H
#define S_SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>


/* if I use system getline() */
#define DO_GETLINE 0
#define DO_STRTOK 0

/* buffer sizes for rd_wr */
#define BUF_FLUSH -1
#define WRITE_BUF_SIZE 1024
#define READ_BUF_SIZE 1024


#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}


/* No Converters */
#define CONVERT_UNSIGNED 	2
#define CONVERT_LOWERCASE	1

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */

typedef struct builtin
{
	char *type;
	int (*func)(sh_args *);
} builtin_table;



extern char **environ;



/* lists of all prototype variable names */

/**
 * struct l_list - reps singly linked list
 * @string: my string
 * @num: field num
 * @lnk: points to the next node
 */



typedef struct l_list
{
	int num;
	char *str;
	struct l_list *link;
} l_list;



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


typedef struct shell_args
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
<<<<<<< HEAD
	char **a_v;
	char **surround;
	char **buff_cmd;
	l_list *surr;
	l_list *past;
	l_list *a_alias;	
} shell_args;

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
ssize_t read_into_buffer(shell_args *content, char *buf, size_t *i);
ssize_t get_input_from_stdin(shell_args *content, char **buf, size_t *len);
int read_input_line(shell_args *, char **, size_t *);
void handle_sigInt(int);


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

=======
	l_list *env;
	l_list *history;
	l__list *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} sh_args;
>>>>>>> 5a1c8792ebacd1eec566aa59313dcb02c5edad8e




/* hsh_handlers */
int custom_shell(sh_args *, char **);
void findAndExecCommand(sh_args *);
void custom_fork(sh_args *);
int search_and_exec_builtin(sh_args *);


/* hsh_handlers1 */
int is_interactive(sh_args *);
int is_delimiter(char, char *);



#endif /* S_SHELL_H */
