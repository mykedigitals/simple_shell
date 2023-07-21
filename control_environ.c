#include "shell.h"


/**
 * set_surr_confirm - validates the amounts of
 * args being moved to surr_set
 * @content: credentials of struct
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
 * unsetting_surr_confirm - validates the amounts of
 * args being moved to surr_set unsetduplicate_surr
 * @content: credentials of struct
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
 * listing_surr_amt -  propagating a linked-list with environ
 * variables
 * @content: credentials of struct
 * Desc: it includes each component of the environ cluster to the
 * conclusion of the connected list utilizing the endOf_node work.
 * The third contention to endOf_node takes (an numbers esteem)
 * as contentions
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
 * duplicate_surr - This function prints the present env variables
 * of the program
 * @content: credentials of the struct
 *
 * Return: 0
 */
int duplicate_surr(sh_args *content)
{
	list_of_stringPrint(content->env);
	return (0);
}


/**
 * getduplicate_surr - look for an environment variable with the
 * given title within the connected list pointed to by content->env
 * and return a pointer to its esteem on the off chance that
 * it is found
 * @content: credential of the struct
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
