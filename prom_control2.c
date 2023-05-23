#include "s_shell.h"

/**
 * find_root - searches for a root or
 * built-in command in our shell program
 * @element: struct parameter
 * Return: -1 (if builtin is not found), 0(when executed),
 * 1 (if found but not executed),
 * -2 (if it (builtin) signals exit())
 */

int find_root(shell_args *element)
{
        int i, root_back = -1;

        root_table root_table_list[] = {
                {"exit", shell_exit},
                {"env", env_clone},
                {"help", help_command},
                {"history", print_command_hist},
                {"setenv", check_env_setter},
                {"unsetenv", check_env_unsetenv},
                {"cd", change_directory},
                {"alias", alias_clone},
                {NULL, NULL}
        };
        for (i = 0; root_table_list[i].type; i++)
                if (cmpare_strs(element->argv[0], root_table_list[i].type) == 0)
                {
                        element->line_count++;
                        root_back = root_table_list[i].func(element);
                        break;
                }
        return (root_back);
}

/**
 * findAndExecCommand - function finds the path to an executable
 * file based on the command-line arguments
 * and then calls fork_cmd to execute the file
 * @element: struct parameter
 *
 * Return: nil
 */
void findAndExecCommand(shell_args *element)
{
	char *path = NULL;
	int index, non_delim_count;

	element->path = element->argv[0];
	if (element->linecount_flag == 1)
	{
		element->line_count++;
		element->linecount_flag = 0;
	}
	for (index = 0, non_delim_count = 0; element->arg[index]; index++)
		if (!is_delimiter(element->arg[index], " \t\n"))
			non_delim_count++;
	if (!non_delim_count)
		return;

	path = find_exec_path(element, getenv_clone(
		element, "PATH="), element->argv[0]);
	if (path)
	{
		element->path = path;
		custom_fork(element);
	}
	else
	{
		if ((is_interactive(element) || getenv_clone(element, "PATH=")
			|| element->argv[0][0] == '/') && is_file_exec(element, element->argv[0]))
			custom_fork(element);
		else if (*(element->arg) != '\n')
		{
			element->status = 127;
			print_err_mesg(element, "not found\n");
		}
	}
}
