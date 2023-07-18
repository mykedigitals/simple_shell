#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>


/* when using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0


/* Command Chaining sequence */
#define CMD_AND		2
#define CMD_OR		1
#define CMD_NORM	0
#define CMD_CHAIN	3


/* File History Specifiers */
#define HIST_MAX	4096
#define HIST_FILE	".simple_shell_history"


/* Number Converters */
#define CONVERT_UNSIGNED	2
#define CONVERT_LOWERCASE	1


/* Buffer sizes for Read-Write */
#define WRITE_BUF_SIZE 1024
#define READ_BUF_SIZE 1024
#define BUF_FLUSH -1


extern char **environ;


/**
 * struct l_list - singly linked list
 * @str: string
 * @num: number field
 * @link: points to the next node
 */
typedef struct l_list
{
	int num;
	char *str;
	struct l_list *link;
} l_list;

/**
 *struct shell_args - stores arguments and environment variables for a shell
 * @arg: command to be executed
 * @argv: array of pointers to the arguments for the command
 * @path: path to the command
 * @argc: number of arguments for the command
 * @line_count: number of lines in the command
 * @err_num: error number if the command fails
 * @linecount_flag: flag indicating if the command is a line count command
 * @fname: name of the file for the command
 * @env: array of pointers to the environment variables
 * @environ: linked list of environment variables
 * @history: linked list of previous commands
 * @alias: linked list of aliases
 * @env_changed: flag show if the environment variables have been changed
 * @status: exit status of the command
 * @cmd_buf: pointer to a buffer that stores the command chain
 * @cmd_buf_type: type of the command chain
 * @readfd: file descriptor for the command
 * @histcount: number of commands in the history
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
	l_list *env;
	l_list *history;
	l_list *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} sh_args;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(sh_args *);
} builtin_table;


/* PROTOTYPE DEFINATIONS */

/* file_refer.c */
int convert_aliasToStr(sh_args *content, char *str);
int alias_rm(sh_args *content, char *str);
int getting_alias(l_list *node);
int duplicate_alias(sh_args *);


/* control_buff.c */
int using_buffer_to_write(char);
void using_buffer_to_write_str(char *);


/* assign_dym_mem */
void *to_allocate_mem(void *, unsigned int, unsigned int);
char *cpy_setof_mem(char *, char, unsigned int);
void free_alot(char **);
int to_free_nothing(void **);


/* obtain_surr.c */
int surr_set(sh_args *, char *, char *);
int unsetduplicate_surr(sh_args *, char *);
char **get_surround(sh_args *);


/* environment_handlers */
int set_surr_confirm(sh_args *);
int unsetting_surr_confirm(sh_args *);
int listing_surr_amt(sh_args *);
int duplicate_surr(sh_args *);
char *getduplicate_surr(sh_args *, const char *);


/* errs_control.c */
void error_msg_print(sh_args *, char *);
int close_str_intt(char *);


/* exit_checker */
int c_dir_shell(sh_args *);
int assist_cmd(sh_args *);
int close_sh(sh_args *);


/* control_fd */
int stringwrite_toFd(char *str, int fd);
int charWrite_toFd(int fil_des, char car);
int decimal_intPrint(int, int);


/* hist_obtain */
int hist_process(sh_args *content);
int put_sh_record(sh_args *content);
int append_inRecord(sh_args *content, char *buf, int linecount);
char *obtain_histFile_path(sh_args *content);
int refresh_history_nodeNumber(sh_args *incontentfo);


/* ls_hist.c */
int hist_cmd_print(sh_args *);


/* prompt_ctrl.c */
int self_created_sh(sh_args *, char **);
void locate_exeCmd(sh_args *);
void self_created_fork(sh_args *);
int find_andExe_follow(sh_args *);


/* prompt_ctrl1.c */
int to_commune(sh_args *);
int no_limitation(char, char *);


/* obtain_collect.c */
void occupy_shell(sh_args *, char **);
void shell_restart(sh_args *);
void shell_empty(sh_args *, int);


/* my_list.c */
size_t list_of_stringPrint(const l_list *);
l_list *endOf_node(l_list **, const char *, int);
int rm_node_idx(l_list **, unsigned int);
void empty_l_list(l_list **);


/* my_list1.c */
ssize_t locate_idx_node(l_list *, l_list *);
l_list *prefix_of_firstNode(l_list *, char *, char);
size_t length_ofList(const l_list *);
size_t idx_of_printedList(const l_list *);
char **list_toStrings_list(l_list *);


/* collect_line.c */
ssize_t put_prosez(sh_args *);
ssize_t  buffer_insert(sh_args *content, char *buf, size_t *i);
ssize_t stdin_obtained(sh_args *content, char **buf, size_t *len);
int insert_line_search(sh_args *, char **, size_t *);
void input_Ctrl(int);


/* parse_handlers */
char *locate_execute(sh_args *, char *, char *);
int for_doc_exec(sh_args *, char *);
char *clone_no_delim(char *, int, int);


/* str_ctrl.c */
char *to_find_char(char *, char);
char *addMore_str(char *, char *, int);
char *string_to_copy(char *, char *, int);
void thisRm_comments(char *);
char *selfCreated_get(long int, int, int);


/* str_ctrl1.c */
char *on_startFind_sub(const char *, const char *);
int string_lent(char *);
char *extend_string(char *, char *);
int strings_weigh(char *, char *);


/* str_ctrl2.c */
char *copy_string(char *, char *);
char *clone_string(const char *);
int _putchar(char);
void _puts(char *);


/* bit_contrl */
char **created_strt(char *, char *);


/* token_handlers */
void analyse_cmd_chain(sh_args *, char *, size_t *, size_t, size_t);
int observe_cmd_chain(sh_args *, char *, size_t *);
int rm_content(char **, char *);
int rp_refer_val(sh_args *);
int rp_val(sh_args *);


#endif /* MAIN_H */
