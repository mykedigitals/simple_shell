#include "shell.h"

/**
 * unsetenv_clone - to remove a variable from the environment
 * @content: struct parameter
 * @var: name of the variable to remove from the environment
 * Desc: Each node in the list contains a string that
 * represents a single environment variable in the format
 * VARNAME=VALUE. "find_substr_at_start" checks if
 * the node's string starts with var, is non-null, then the node
 * represents the environment variable to remove.
 * The function calls delete_node_index to remove the node
 * from the linked list, sets content->env_changed to
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

int unsetenv_clone(sh_args *content, char *var)
{
	/* represents the current environment variables */
	l_list *node = content->env;
	size_t index, yy;
	char *ptr;

	index = 0;
	yy = 0;
	if (var == NULL || !node)
	{
		return (yy);
	}
	/* Loop thu l list of env vars until d end of d list is reached */
	for ( ; node; index++)
	{
		/* Find the first occurrence of the input string at */
		/* the start of the current string in the linked list */
		ptr = find_substr_at_start(node->str, var);
		if (*ptr == '=' && ptr != NULL)
		{
			/* Delete the current node from the linked list, */
			/* set env_vars_changed to 1 */
			/* and reset the index and node variables */
			content->env_changed = delete_node_index(&(content->env), index);
			index = yy;
			node = content->env;
			continue;
		}
		node = node->link;
	}
	return (content->env_changed);
}
