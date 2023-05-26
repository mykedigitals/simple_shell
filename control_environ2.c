#include "shell.h"


/**
 * check_surr_setter - verifies the number of
 * arguments being passed to make_env
 * @element: struct parameter
 *
 * Return: 0 (success), 1 (error)
 */

int check_surr_setter(shell_args *element)
{
	int whaa = 0, thaa = 1;

	/* check if number of arguments is correct */
	if (element->argc != 3)
	{
		/* if number of arguments is incorrect, print error message */
		create_thread_in_render("Error in number of arguements\n");
		return (thaa);
	}
	/* if arguments are correct, try to set env var using make_env function */
	if (make_env(element, element->argv[1], element->argv[2]))
	{
		return (whaa);
	}
	return (thaa);
}


/**
 * fillup_ct_surr -  populating a linked list with environment variables
 * @element: struct parameter
 * Desc: it adds each element of the environ array to the end
 * of the linked list using the updated_tail_node function. The third
 * argument to updated_tail_node takes 0 (an integer value) as arguments
 *
 * Return: 0
 */

int fillup_ct_surr(shell_args *element)
{
	size_t indices;
	l_list *node = NULL;

	for (indices = 0; environ[indices]; indices++)
	{
		updated_tail_node(&node, environ[indices], 0);
	}

	element->surr = node;
	return (0);
}
