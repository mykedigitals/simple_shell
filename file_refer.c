#include "shell.h"


/**
 * comot_refer - removes an alias command in the form
 * "alias name=value" from "shell_args" struct
 * @element: struct parameter
 * @str: the alias string
 * Desc: It copies alias name from @str_p to @clone, then
 * set @str_p to null (\0) to terminate the string at that point.
 * The search_node_sort function is then called to find the index
 * of the node in the alias linked list that starts with the string
 * before the equal sign. The obtain_beginingnode function is
 * used to perform the comparison. If a matching node is found, the
 * search_node_sort function is called
 * to remove the node from the linked list.
 *
 * Return: 0 (success), 1 (error)7
 */

int comot_refer(shell_args *element, char *str)
{
	int comoter;
	char clone;
	char *str_p = locate_char(str, '=');

	if (!str_p)
	{
		return (1);
	}
	/* Temporarily replace the '=' character with a null terminator */
	clone = *str_p;
	*str_p = 0;
	/* Get d index of d first node in d alias list that matches the prefix */
	/* Delete the node at the given index from the alias list */

	comoter = rem_node_sort(&(element->alias),
			search_node_sort(element->alias,
			obtain_beginingnode(element->alias, str, -1)));
	/* Restore the '=' character to the input string */
	*str_p = clone;
	return (comoter);
}



/**
 * cpy_refer - prints out the name and value of each alias
 * @element: struct parameter
 *
 * Return: 0
 */

int cpy_refer(shell_args *element)
{
	int indices = 0;
	char *chk = NULL;
	l_list *node = NULL;

	if (element->argc == 1)
	{
		/* prints the node while iterating through the linked list */
		node = element->alias;
		for ( ; node != NULL; node = node->link)
			print_refer(node);
		return (0);
	}
	indices = 1;
	while (element->argv[indices])
	{
		chk = locate_char(element->argv[indices], '=');
		if (chk != NULL)
			refer_to_word(element, element->argv[indices]);
		else
			print_refer(obtain_beginingnode(
						element->alias, element->argv[indices], '='));
		indices++;
	}
	return (0);
}
