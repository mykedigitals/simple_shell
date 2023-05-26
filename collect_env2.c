#include "shell.h" 

/**..
 * unsetsurr_cpy - This will evacuate a parameter in the surrouding
 * @element: structure parameter
 * @var: parameter name thst be remove from environment
 * rFw: For nodes in the list contain a string that represent 
 * single environment parameter in the format
 * PARNAME=vALUE. "locate_word_begin" checks if
 * the node's string starts with var, is non-null, then the node is removed
 * This function beckon rem_node_sort removed and sets element->surr_changed to
 * true to indicate that the environment was modified,
 * resets the sort to 0
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
			/* rem current node in linked list */
			/* set surr_vars_changed to 1 */
			/* then reset the sort and node pars */
			element->surr_changed = rem_node_sort(&(element->surr), sort);
			sort = dhaa;
			node = element->surr;
			continue;
		}
		node = node->link;
	}
	return (element->surr_changed);
}
