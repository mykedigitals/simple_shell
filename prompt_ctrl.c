#include "shell.h"

/**
 * self_created_sh - this is custom shell implementation
 * which will read user input, interpret then execute commands
 * @content: the struct parameter
 * @arg_v: this reps argument vector
 *
 * Return: 0 (success), 1 (error)
 */
int self_created_sh(sh_args *content, char **arg_v)
{
	ssize_t input_result = 0;
	int builtin_result = 0;

	while (input_result != -1 && builtin_result != -2)
	{
		shell_restart(content);
		if (to_commune(content))
			_puts("$ ");
		using_buffer_to_write(BUF_FLUSH);
		input_result = put_prosez(content);
		if (input_result != -1)
		{
			occupy_shell(content, arg_v);
			builtin_result = find_andExe_follow(content);
			if (builtin_result == -1)
				locate_exeCmd(content);
		}
		else if (to_commune(content))
			_putchar('\n');
		shell_empty(content, 0);
	}
	put_sh_record(content);
	shell_empty(content, 1);
	if (!to_commune(content) && content->status)
		exit(content->status);
	if (builtin_result == -2)
	{
		if (content->err_num == -1)
			exit(content->status);
		exit(content->err_num);
	}
	return (builtin_result);
}


/**
 * locate_exeCmd - this function will find the path to executable
 * file depending on command-line arguments then it calls 
 * fork_cmd to execute the file
 * @content: this is struct parameter
 *
 * Return: nil(no return)
 */
void locate_exeCmd(sh_args *content)
{
	char *path = NULL;
	int index, non_delim_count;

	content->path = content->argv[0];
	if (content->linecount_flag == 1)
	{
		content->line_count++;
		content->linecount_flag = 0;
	}
	for (index = 0, non_delim_count = 0; content->arg[index]; index++)
		if (!no_limitation(content->arg[index], " \t\n"))
			non_delim_count++;
	if (!non_delim_count)
		return;

	path = locate_execute(content, getduplicate_surr(
		content, "PATH="), content->argv[0]);
	if (path)
	{
		content->path = path;
		self_created_fork(content);
	}
	else
	{
		if ((to_commune(content) || getduplicate_surr(content, "PATH=")
			|| content->argv[0][0] == '/') && for_doc_exec(content, content->argv[0]))
			self_created_fork(content);
		else if (*(content->arg) != '\n')
		{
			content->status = 127;
			error_msg_print(content, "not found\n");
		}
	}
}


/**
 * self_created_fork - this will iterate a system call and create a new process
 * @content: this is struct parameter
 *
 * Return: nil(no return)
 */
void self_created_fork(sh_args *content)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO:this is to add our error function */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(content->path, content->argv, get_surround(content)) == -1)
		{
			shell_empty(content, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: this is to add our error function */
	}
	else
	{
		wait(&(content->status));
		if (WIFEXITED(content->status))
		{
			content->status = WEXITSTATUS(content->status);
			if (content->status == 126)
				error_msg_print(content, "Permission denied\n");
		}
	}
}


/**
 * find_andExe_follow - this will search for a built-in 
 * command in our shell program
 * @content: this is struct parameter
 *
 * Return: -1 ( if our builtin is not found), 0 (if our builtin is executed),
 * 1 (if our builtin can be  found but not executed),
 *	   -2 (when our builtin signals exit())
 */
int find_andExe_follow(sh_args *content)
{
	int i, builtin_return = -1;
	builtin_table builtin_table_list[] = {
		{"exit", close_sh},
		{"env", duplicate_surr},
		{"help", assist_cmd},
		{"history", hist_cmd_print},
		{"setenv", set_surr_confirm},
		{"unsetenv", unsetting_surr_confirm},
		{"cd", c_dir_shell},
		{"alias", duplicate_alias},
		{NULL, NULL}
	};

	for (i = 0; builtin_table_list[i].type; i++)
		if (strings_weigh(content->argv[0], builtin_table_list[i].type) == 0)
		{
			content->line_count++;
			builtin_return = builtin_table_list[i].func(content);
			break;
		}
	return (builtin_return);
}

