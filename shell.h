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
#define CMD_WIT		2
#define CMD_EI		1
#define CMD_ORDI	0
#define CMD_ORDER	3


/* File History Specifiers */
#define HIST_MAX	4096
#define HIST_FILE	".simple_shell_record"


/* Number Converters */
#define CONVERT_UNSIGNED	2
#define CONVERT_LOWERCASE	1


/* Buffer sizes for Read-Write */
#define WRITE_BUF_SIZE 1024
#define SEEN_BUF_SIZE 1024
#define BUFF_FLUSHH -1


extern char **surriron;


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
 *struct shell_args - stores arguments and surrironment variables for a shell
 * @arg: command to be executed
 * @argv: array of pointers to the arguments for the command
 * @path: path to the command
 * @argc: number of arguments for the command
 * @space_ct: number of lines in the command
 * @err_num: error number if the command fails
 * @spacect_flg: flag indicating if the command is a line count command
 * @fname: name of the file for the command
 * @surr: array of pointers to the environment variables
 * @surriron: linked list of environment variables
 * @record: linked list of previous commands
 * @alias: linked list of aliases
 * @surr_changed: flag show if the environment variables have been changed
 * @status: exit status of the command
 * @cd_buff: pointer to a buffer that stores the command chain
 * @cd_buff_type: type of the command chain
 * @seefd: file descriptor for the command
 * @histcount: number of commands in the record
 */
typedef struct shell_args
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int space_ct;
	int err_num;
	int spacect_flg;
	char *fname;
	l_list *surr;
	l_list *record;
	l_list *alias;
	char **surriron;
	int surr_changed;
	int status;

	char **cd_buff;
	int cd_buff_category;
	int seefd;
	int recordct;
} shell_args;

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
	int (*func)(shell_args *);
} root_table;


/* PROTOTYPE DEFINATIONS */

/* file_refer */
int comot_refer(shell_args *element, char *str);
int cpy_refer(shell_args *);


/* filer_refer2 */
int refer_to_word(shell_args *element, char *str);
int print_refer(l_list *node);


/* buffer_handlers */
int create_in_space(char);
void create_thread_in_render(char *);


/* dym_mem_allocator */
void *mem_alloc(void *, unsigned int, unsigned int);
char *memset_clone(char *, char, unsigned int);
void double_empty(char **);
int empty_n_NULL(void **);


/* collect_env */
int make_env(shell_args *, char *, char *);
int unsetsurr_cpy(shell_args *, char *);
char **surr_seeker(shell_args *);


/* control_environ */
int check_surr_setter(shell_args *);
int check_surr_unsetsurr(shell_args *);
int fillup_ct_surr(shell_args *);
int surr_clone(shell_args *);
char *getsurr_clone(shell_args *, const char *);


/* error_handlers1 */
void prt_mes_eror(shell_args *, char *);
int end_from_str(char *);


/* exit_checker */
int ch_directory(shell_args *);
int help_command(shell_args *);
int shell_out(shell_args *);


/* file-descriptor_handlers */
int write_string_to_fd(char *str, int fd);
int write_chk_to_fd(int fil_des, char chk);
int prt_dcm_int(int, int);


/* record_getter */
int load_record(shell_args *element);
int create_shel_record(shell_args *element);
int plus_to_record(shell_args *element, char *buf, int linecount);
char *get_hist_file_path(shell_args *element);
int update_hist_node_numbrs(shell_args *inelementfo);


/* record_list */
int print_command_record(shell_args *);


/* hsh_handlers */
int created_sh(shell_args *, char **);
void search_execcmd(shell_args *);
void createdfork(shell_args *);
int find_root(shell_args *);


/* hsh_handlers1 */
int reciprocate(shell_args *);
int separator(char, char *);


/* info_getter */
void enter_shell_args(shell_args *, char **);
void correct_sh_args(shell_args *);
void empty_shell_args(shell_args *, int);


/* l_list_handler */
size_t screen_l_list_in_str(const l_list *);
l_list *updated_tail_node(l_list **, const char *, int);
int rem_node_sort(l_list **, unsigned int);
void empty_l_list(l_list **);


/* l_list_handler1 */
ssize_t search_node_sort(l_list *, l_list *);
l_list *obtain_beginingnode(l_list *, char *, char);
size_t list_span(const l_list *);
size_t prt_l_list_in_sort(const l_list *);
char **chng_list_to_strng(l_list *);


/* line_getter */
ssize_t pro_details(shell_args *);
ssize_t read_into_buffer(shell_args *element, char *buf, size_t *i);
ssize_t obtain_details_stdin(shell_args *element, char **buf, size_t *len);
int see_line_details(shell_args *, char **, size_t *);
void signit_control(int);


/* examiner */
char *search_path(shell_args *, char *, char *);
int is_exec(shell_args *, char *);
char *char_clone_nolimiter(char *, int, int);


/* thread_control */
char *locate_char(char *, char);
char *thread_rearr(char *, char *, int);
char *string_clone(char *, char *, int);
void word_comot(char *);
char *created_iota(long int, int, int);


/* thread_control1 */
char *locate_word_begin(const char *, const char *);
int string_lent(char *);
char *string_add(char *, char *);
int weigh_strs(char *, char *);


/* thread_control2 */
int _putchar(char);
void _puts(char *);
char *clone_str(char *, char *);
char *double_str(const char *);


/* token_handlers */
char **created_tokener(char *, char *);


/* token_handlers */
void access_cmd_order(shell_args *, char *, size_t *, size_t, size_t);
int order_cmd_discover(shell_args *, char *, size_t *);
int change_element(char **, char *);
int sub_alias_val(shell_args *);
int sub_var_val(shell_args *);


#endif /* MAIN_H */
