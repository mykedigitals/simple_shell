#include "shell.h"


/**
 * check_surr_unsetsurr - validate the number of
 * arguments that's passed to surr_setter unsetsurr_cpy
 * @element: parameter
 *
 *  Return: 0
 */

int check_surr_unsetsurr(shell_args *element)
{
	int indices;

	if (element->argc == 1)
	{
		/* Prints errors */
		create_thread_in_render("Too few arguements.\n");
		return (1);
	}

	for (indices = 1; indices <= element->argc; indices++)
	{
		/* calls d unsetsurr_cpy function with d args in the struct shell_args */
		/* and the command-line argument at the current index */
		unsetsurr_cpy(element, element->argv[indices]);
	}
	return (0);
}



/**
 * surr_clone - print the current surrironment variables of the program
 * @element: struct parameter
 *
 * Return: 0
 */

int surr_clone(shell_args *element)
{
	int thaa = 0;
	/* Extract the surrironment variables from d shell_args struct and prints */
	screen_l_list_in_str(element->surr);

	return (thaa);
}


/**
 * getsurr_clone - search for an surrironment variable with
 * the given name in the linked list pointed to by element->surr
 * and return a pointer to its value if it is found
 * @element: struct parameter
 * @name: name of surr var
 *
 * Return: the value
 */

char *getsurr_clone(shell_args *element, const char *name)
{
	char *ptr;
	l_list *node;

	node = element->surr;

	while (node)
	{
		ptr = locate_word_begin(node->str, name);
		if (ptr && *ptr)
			return (ptr);
		node = node->link;
	}

	return (NULL);
}
