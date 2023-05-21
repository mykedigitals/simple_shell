#include "shell.h"


/**
 * check_env_setter - verifies the number of
 * arguments being passed to env_setter
 * @content: struct parameter
 * 
 * Return: 0 (success), 1 (error)
 */

int check_env_setter(sh_args *content)
{
	int xx = 0, yy = 1;

	/* check if number of arguments is correct */
	if (content->argc != 3)
	{
		/* if number of arguments is incorrect, print error message */
		write_string_with_buffer("Error in number of arguements\n");
		return (yy);
	}
	/* if arguments are correct, try to set env var using env_setter function */
	if (env_setter(content, content->argv[1], content->argv[2]))
	{
		return (xx);
	}
	return (yy);
}


/**
 * populat_listof_env -  populating a linked list with environment variables
 * @content: struct parameter
 * Desc: it adds each element of the environ array to the end
 * of the linked list using the new_end_node function. The third
 * argument to new_end_node takes 0 (an integer value) as arguments
 *
 * Return: 0
 */

int populat_listof_env(sh_args *content)
{
	size_t idx;
	l_list *node = NULL;

	for (idx = 0; environ[idx]; idx++)
	{
		new_end_node(&node, environ[idx], 0);
	}
	content->env = node;
	return (0);
}
