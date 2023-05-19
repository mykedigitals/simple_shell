#include "s_shell.h"

/**
 * created_shell - to implement shell created that reads user input, interprets and executes commands.
 * @element: parameter struct
 * @a_v: argument vector
 * Return: 0 on success, 1 on error
 */

int created_shell(shell_args *element, char **a_v)
{
	ssize_t in_result = 0;
	int root_result = 0;

	while (in_result != -1 && root_result != -2)
	{
		clear_shell_args(element);
		if (interactiv(element))
		{
			puts("# ");
		}

		list_buffer(BUF_FLUSH);
		in_result = pro_in(element);
		if (in_result != -1)
		{
			enter_shell_args(element, a_v);
			root_result = find_root(element);
			if (root_result == -1)
				search_execcmd(element);
		}
		else if (interactiv(element))
		{
			putchar('\n');
		}
		empty_shell_args(element, 0);
	}

	list_shell_hist(element);
	empty_shell_args(element, 1);
	if (!interactiv(element) && element->for_status)
		exit(element->for_status);
	if (root_result == -2)
	{
		if (element->num_error == -1)
			exit(element->for_status);
		exit(element->num_error);
	}
	return (root_result);
}
