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
	char *path = NULL;
	int index, un_delimiter_ct;

	element->path = element->a_v[0];
	if (element->linect_flg == 1)
	{
		element->line_ct++;
		element->linect_flg = 0;
	}
	for (index = 0, un_delimiter_ct = 0; element->arg[index]; index++)
		if (!delimiter(element->arg[index], "\t\n"))
			un_delimiter_ct++;
	if (!un_delimiter_ct)
		return;

	path = search_execpath(element, getenv_cpy(element, "PATH="), content-> a_v[0]);
	if (path)
	{
		element->path = path;
		created_fork(element);
	}
	else
	{
		if ((interactive(element) || getenv-clone(element, "PATH=") 
					|| element->a_v[0][0] =='/') && file_exec(element, element->a_v[0]))custom_fork(element);
		else if (*(element->arg) != '\n'
