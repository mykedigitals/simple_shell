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
			_puts("# ");
		
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
			_putchar('\n');
		empty_shell_args(element, 0);
	}
	
	list_shell_hist(element);
	empty_shell_args(element, 1);
	if (!interactiv(element) && element->level)
		exit(element->level);
	if (root_result == -2)
	{
		if (element ->error_num == -1)
			exit(element->level);
		exit(element->error_num);
	}
	return (root_result);
}
