#include "shell.h"

/**
 * search_and_exec_builtin - searches for a built-in command in a shell program
 * @content: struct parameter
 * Return: -1 (builtin is not found), 0 (builtin is executed),
 * 1 (builtin found but not executed),
 * -2 (builtin signals exit())
 */

int search_and_exec_builtin(sh_args *content)
{
        int i, builtin_return = -1;

        builtin_table builtin_table_list[] = {
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
        for (i = 0; builtin_table_list[i].type; i++)
                if (cmpare_strs(content->argv[0], builtin_table_list[i].type) == 0)
                {
                        content->line_count++;
                        builtin_return = builtin_table_list[i].func(content);
                        break;
                }
        return (builtin_return);
}

/**
 * findAndExecCommand - function finds the path to an executable
 * file based on the command-line arguments
 * and then calls fork_cmd to execute the file
 * @content: struct parameter
 *
 * Return: nil
 */
void findAndExecCommand(sh_args *content)
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
		if (!is_delimiter(content->arg[index], " \t\n"))
			non_delim_count++;
	if (!non_delim_count)
		return;

	path = find_exec_path(content, getenv_clone(
		content, "PATH="), content->argv[0]);
	if (path)
	{
		content->path = path;
		custom_fork(content);
	}
	else
	{
		if ((is_interactive(content) || getenv_clone(content, "PATH=")
			|| content->argv[0][0] == '/') && is_file_exec(content, content->argv[0]))
			custom_fork(content);
		else if (*(content->arg) != '\n')
		{
			content->status = 127;
			print_err_mesg(content, "not found\n");
		}
	}
}
