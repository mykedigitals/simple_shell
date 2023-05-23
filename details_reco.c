#include "shell.h"

/**
 * enter_shell_args - sets the fname field of the struct to the name
 *	of the command being executed
 * @element: struct parameter
 * @a_v: argument vector
 */
void enter_shell_args(shell_args *element, char **a_v)
{
	int index = 0;

	element->fname = a_v[0];
	if (element->arg)
	{
		element->argv = created_strtow(element->arg, " \t");
		if (!element->argv)
		{

			element->argv = malloc(sizeof(char *) * 2);
			if (element->argv)
			{
				element->argv[0] = str_dup(element->arg);
				element->argv[1] = NULL;
			}
		}
		for (index = 0; element->argv && element->argv[index]; index++)
			;
		element->argc = index;

		sub_alias_val(element);
		sub_var_val(element);
	}
}

