#include "shell.h"


/**
 * set_surr_confirm - verifies the number of
 * arguments being passed to surr_set
 * @content: struct parameter
 *
 *  Return: 0 (success), 1 (error)
 */
int set_surr_confirm(sh_args *content)
{
	if (content->argc != 3)
	{
		using_buffer_to_write_str("Incorrect number of arguements\n");
		return (1);
	}
	if (surr_set(content, content->argv[1], content->argv[2]))
		return (0);
	return (1);
}

/**
 * unsetting_surr_confirm - verifies the number of
 * arguments being passed to surr_set unsetduplicate_surr
 * @content: struct parameter
 *
 *  Return: 0
 */
int unsetting_surr_confirm(sh_args *content)
{
	int index;

	if (content->argc == 1)
	{
		using_buffer_to_write_str("Too few arguements.\n");
		return (1);
	}
	for (index = 1; index <= content->argc; index++)
		unsetduplicate_surr(content, content->argv[index]);

	return (0);
}

/**
 * listing_surr_amt -  populating a linked list with environment variables
 * @content: struct parameter
 * Desc: it adds each element of the environ array to the end
 * of the linked list using the endOf_node function. The third
 * argument to endOf_node takes 0 (an integer value) as arguments
 *
 * Return: 0
 */
int listing_surr_amt(sh_args *content)
{
	l_list *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		endOf_node(&node, environ[i], 0);
	content->env = node;
	return (0);
}


/**
 * duplicate_surr - print the current environment variables of the program
 * @content: struct parameter
 *
 * Return: 0
 */
int duplicate_surr(sh_args *content)
{
	list_of_stringPrint(content->env);
	return (0);
}


/**
 * getduplicate_surr - search for an environment variable with
 * the given name in the linked list pointed to by content->env
 * and return a pointer to its value if it is found
 * @content: struct parameter
 * @name: name of env var
 *
 * Return: the value
 */
char *getduplicate_surr(sh_args *content, const char *name)
{
	l_list *node = content->env;
	char *p;

	while (node)
	{
		p = on_startFind_sub(node->str, name);
		if (p && *p)
			return (p);
		node = node->link;
	}
	return (NULL);
}
