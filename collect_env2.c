#include "shell.h"

/**
 * unsetsurr_cpy - to remove a variable from the environment
 * @element: struct parameter
 * @var: name of the variable to remove from the environment
 * Desc: Each node in the list contains a string that
 * represents a single environment variable in the format
 * VARNAME=VALUE. "locate_word_begin" checks if
 * the node's string starts with var, is non-null, then the node
 * represents the environment variable to remove.
 * The function calls rem_node_sort to remove the node
 * from the linked list, sets element->env_changed to
 * true to indicate that the environment was modified,
 * resets the index to 0, and starts iterating the
 * linked list from the beginning again. But if it is null,
 * then the node does not represent the environment variable
 * to remove. The function increments the index and
 * continues iterating the linked list
 * 
 * Return: 1 (delete), 0 (if node or var is null,
 * indicating that no changes were made to the environment)
 */

int unsetsurr_cpy(shell_args *element, char *var)
{
	/* represents the current environment variables */
	l_list *node = element->surr;
	size_t index, whaa;
	char *ptr;

	index = 0;
	whaa = 0;
	if (var == NULL || !node)
	{
		return (whaa);
	}
	/* Loop thu l list of env vars until d end of d list is reached */
	for ( ; node; index++)
	{
		/* Find the first occurrence of the input string at */
		/* the start of the current string in the linked list */
		ptr = locate_word_begin(node->str, var);
		if (*ptr == '=' && ptr != NULL)
		{
			/* Delete the current node from the linked list, */
			/* set env_vars_changed to 1 */
			/* and reset the index and node variables */
			element->env_changed = rem_node_sort(&(element->surr), index);
			index = whaa;
			node = element->surr;
			continue;
		}
		node = node->link;
	}
	return (element->env_changed);
}
