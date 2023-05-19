#include "s_shell.h"


/**
 * delimiter - it is a checker if a particular content is
 * a delimiter character
 * @val: this is the content to be checked
 * @d_delim: the content of the delimiter
 *
 * Return: this returns 1 if true and 0 if it is false
 */

int delimiter(char val, char *d_delim)
{
	while (*d_delim)
		if (*d_delim++ == val)
			return (1);
	return (0);
}

/**
 * interactiv - the shell is checked if it is in interactive mode
 * @element: this is the parameter for struct
 *
 * Return: it returns one(1) if element is in interactive mode
 */

int interactiv(shell_args *element)
{
	return (isatty(STDIN_FILENO) && element->rd_fd <= 2);
}



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
