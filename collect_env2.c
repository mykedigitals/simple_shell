#include "shell.h"

/**
 * unsetsurr_cpy - This will evacuate a parameter in the surrouding
 * @element: structure parameter
 * @var: parameter name thst be remove from environment
 *
 * Return: 1 (delete), 0 (if node or var is null,
 * indicating that no changes were made to the environment)
 */

int unsetsurr_cpy(shell_args *element, char *var)
{
	/* represents the current environment parameters */
	l_list *node = element->surr;
	size_t sort, dhaa;
	char *ptr;

	sort = 0;
	dhaa = 0;
	if (var == NULL || !node)
	{
		return (dhaa);
	}
	/* for loop until d end of d list is reached */
	for ( ; node; sort++)
	{
		ptr = locate_word_begin(node->str, var);
		if (*ptr == '=' && ptr != NULL)
		{
			element->surr_changed = rem_node_sort(&(element->surr), sort);
			sort = dhaa;
			node = element->surr;
			continue;
		}
		node = node->link;
	}
	return (element->surr_changed);
}
