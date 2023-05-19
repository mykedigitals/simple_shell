#include "s_shell.h"

/**
 * search-execcmd - searches path to executable file based onthe command line args
 * then cals fork_cmd to execute the file
 *
 * @element: parameter struct
 * return: nil
 */

void search_execcmd(shell_args *element)
{
	char *way_path = NULL;
	int index, un_delimiter_ct;

	element->way_path = element->argv[0];
	if (element->flag_count_ln == 1)
	{
		element->count_ln++;
		element->flag_count_ln = 0;
	}
	for (index = 0, un_delimiter_ct = 0; element->arg[index]; index++)
		if (!delimiter(element->arg[index], "\t\n"))
			un_delimiter_ct++;
	if (!un_delimiter_ct)
		return;

	way_path = search_execpath(element, getenv_cpy(element, "PATH="), content-> argv[0]);
	if (way_path)
	{
		element->way_path = way_path;
		created_fork(element);
	}
	else
	{
		if ((interactiv(element) || getenv_cpy(element, "PATH=")
					|| element->argv[0][0] == '/') && file_exec(element, element->argv[0]))created_fork(element);
		else if (*(element->arg) != '\n')
		{
			element->for_status = 127;
			error_msg_print(element, "not found\n");
		}
	}
}


/**
 * created_fork - to create a new process a system call is forked
 * @element: parameter for the struct
 * Return: nothing to return
 */

void created_fork(shell_args *element)
{
	pid_t pid_pikin;

	pid_pikin = fork();
	if (pid_pikin == -1)
	{
		perror("Error");
		return;
	}
	if (pid_pikin == 0)
	{
		if (execve(content->way_path, element->argv, obtain_env(element)) == -1)
		{
			empty_shell_args(element, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(element->for_status));
		if (WIFEXITED(element->for_status))
		{
			element->for_status = WEXITSTATUS(element->for_status);
			if(element->for_status == 126)
				error_msg_print(element, "Permission denied\n");
		}
	}

}
