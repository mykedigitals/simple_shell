#include "shell.h"

/**
 * created_sh - implementation of created_sh to read
 * a user's input, interpret and execute it
 * @element: structure parameter
 * @a_v: argument vector
 * Return: 0 (success), 1 (error)
 */

int created_sh(shell_args *element, char **a_v)
{
	ssize_t details_rslt = 0;
	int root_rslt = 0;

	while (details_rslt != -1 && root_rslt != -2)
	{
		correct_sh_args(element);
		if (reciprocal(element))
			_puts("$ ");
		create_in_space(BUFF_FLUSH);
		details_rslt = pro_details(element);
		if (details_rslt != -1)
		{
			enter_shell_args(element, a_v);
			root_rslt = find_root(element);
			if (root_rslt == -1)
				search_execcmd(element);
		}
		else if (reciprocal(element))
			_putchar('\n');
		empty_shell_args(element, 0);
	}
	create_shel_record(element);
	empty_shell_args(element, 1);
	if (!reciprocal(element) && element->status)
		exit(element->status);
	if (root_rslt == -2)
	{
		if (element->err_num == -1)
			exit(element->status);
		exit(element->err_num);
	}
	return (root_rslt);
}

/**
 * createdfork - forks a system call to create a new process
 * @element: struct parameter
 *
 * Return: nil
 */

void createdfork(shell_args *element)
{
	pid_t child_pid;
	
	child_pid = fork();
	if (child_pid == -1)
	{
		/* ACTION: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(element->path, element->argv, env_seeker(element)) == -1)
		{
			empty_shell_args(element, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* ACTION: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(element->status));
		if (WIFEXITED(element->status))
		{
			element->status = WEXITSTATUS(element->status);
			if (element->status == 126)
				print_err_mesg(element, "Permission notgiv\n");
		}
	}
}

