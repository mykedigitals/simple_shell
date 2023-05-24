#include "shell.h"

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
                {"out", shell_out},
                {"surr", surr_clone},
                {"help", help_command},
                {"record", print_command_record},
                {"setsurr", check_surr_setter},
                {"unsetsurr", check_surr_unsetsurr},
                {"chd", ch_directory},
                {"alias", alias_clone},
                {NULL, NULL}
        };
        for (i = 0; root_table_list[i].type; i++)
                if (weigh_strs(element->argv[0], root_table_list[i].type) == 0)
                {
                        element->space_ct++;
                        root_back = root_table_list[i].func(element);
                        break;
                }
        return (root_back);
}

/**
 * search_execcmd - function finds the path to an executable
 * file based on the command-line arguments
 * and then calls invent_cmd to execute the file
 * @element: struct parameter
 *
 * Return: nil
 */
void search_execcmd(shell_args *element)
{
	char *path = NULL;
	int index, non_separate_ct;

	element->path = element->argv[0];
	if (element->spacect_flg == 1)
	{
		element->space_ct++;
		element->spacect_flg = 0;
	}
	for (index = 0, non_separate_ct = 0; element->arg[index]; index++)
		if (!separator(element->arg[index], " \t\n"))
			non_separate_ct++;
	if (!non_separate_ct)
		return;

	path = search_path(element, getsurr_clone(
		element, "PATH="), element->argv[0]);
	if (path)
	{
		element->path = path;
		createdfork(element);
	}
	else
	{
		if ((reciprocate(element) || getsurr_clone(element, "PATH=")
			|| element->argv[0][0] == '/') && is_exec(element, element->argv[0]))
			createdfork(element);
		else if (*(element->arg) != '\n')
		{
			element->status = 127;
			prt_mes_eror(element, "not known\n");
		}
	}
}
