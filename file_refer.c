#include "shell.h"


/**
 * remv_alias - removes an alias command in the form
 * "alias name=value" from "sh_args" struct
 * @content: struct parameter
 * @str: the alias string
 * Desc: It copies alias name from @str_p to @copy, then
 * set @str_p to null (\0) to terminate the string at that point.
 * The find_node_index function is then called to find the index
 * of the node in the alias linked list that starts with the string
 * before the equal sign. The get_first_node_with_prefix function is
 * used to perform the comparison. If a matching node is found, the
 * delete_node_index function is called
 * to remove the node from the linked list.
 *
 * Return: 0 (success), 1 (error)7
 */

int remv_alias(sh_args *content, char *str)
{
	/* Find the position of the '=' character in the input string */
	int remover;
	char copy;
	char *str_p = car_finder(str, '=');

	if (!str_p)
	{
		return (1);
	}
	/* Temporarily replace the '=' character with a null terminator */
	copy = *str_p;
	*str_p = 0;
	/* Get d index of d first node in d alias list that matches the prefix */
	/* Delete the node at the given index from the alias list */

	remover = delete_node_index(&(content->alias),
			find_node_index(content->alias,
				get_first_node_with_prefix(content->alias, str, -1)));
	/* Restore the '=' character to the input string */								*str_p = copy;
	return (remover);
}



/**
 * alias_clone - prints out the name and value of each alias
 * @content: struct parameter
 *
 * Return: 0
 */

int alias_clone(sh_args *content)
{
	int idx = 0;
	char *car = NULL;
	l_list *node = NULL;

	if (content->argc == 1)
	{
		/* prints the node while iterating through the linked list */
		node = content->alias;
		for ( ; node != NULL; node = node->link)
			alias_printer(node);
		return (0);
	}
	idx = 1;
	while (content->argv[idx])
	{
		car = car_finder(content->argv[idx], '=');
		if (car != NULL)
			alias_to_str(content, content->argv[idx]);
		else
			alias_printer(get_first_node_with_prefix(
						content->alias, content->argv[idx], '='));
		idx++;
	}
	return (0);
}
