#include "shell.h"

/**
 * custom_shell - custom shell implementation
 * that reads user input, interprets and executes commands
 * @content: struct parameter
 * @arg_v: argument vector
 * Return: 0 (success), 1 (error)
 */

int custom_shell(sh_args *content, char **arg_v)
{
	ssize_t input_result = 0;
	int builtin_result = 0;

	while (input_result != -1 && builtin_result != -2)
	{
		reset_sh_args(content);
		if (is_interactive(content))
			_puts("$ ");
		write_with_buffer(BUF_FLUSH);
		input_result = process_input(content);
		if (input_result != -1)
		{
			fill_sh_args(content, arg_v);
			builtin_result = search_and_exec_builtin(content);
			if (builtin_result == -1)
				findAndExecCommand(content);
		}
		else if (is_interactive(content))
			_putchar('\n');
		free_sh_args(content, 0);
	}
	write_shel_histry(content);
	free_sh_args(content, 1);
	if (!is_interactive(content) && content->status)
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
 * custom_fork - forks a system call to create a new process
 * @content: struct parameter
 *
 * Return: nil
 */

void custom_fork(sh_args *content)
{
	pid_t child_pid;
	
	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(content->path, content->argv, environ_getter(content)) == -1)
		{
			free_sh_args(content, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(content->status));
		if (WIFEXITED(content->status))
		{
			content->status = WEXITSTATUS(content->status);
			if (content->status == 126)
				print_err_mesg(content, "Permission denied\n");
		}
	}
}

