#include "shell.h"

/**
 * rem_node_sort - delete a node in a linked list at a specific index
 * @list_top: top node
 * @index: sort node being deleted
 *
 * Return: 1 (success), 0 (failure)
 */
int rem_node_sort(l_list **list_top, unsigned int index)
{
	l_list *present_node, *prev_node;
	unsigned int x = 0;

	if (!list_top || !*list_top)
		return (0);

	if (!index)
	{
		present_node = *list_top;
		*list_top = (*list_top)->link;
		free(present_node->str);
		free(present_node);
		return (1);
	}
	present_node = *list_top;
	while (present_node)
	{
		if (x == index)
		{
			prev_node->link = present_node->link;
			free(present_node->str);
			free(present_node);
			return (1);
		}
		x++;
		prev_node = present_node;
		present_node = present_node->link;
	}
	return (0);
}


/**
 * empty_l_list - frees all list
 * @list_top: top node
 *
 * Return: void
 */
void empty_l_list(l_list **list_top)
{
	l_list *present_node, *following_node, *top;

	if (!list_top || !*list_top)
		return;
	top = *list_top;
	present_node = top;
	while (present_node)
	{
		following_node = present_node->link;
		free(present_node->str);
		free(present_node);
		present_node = following_node;
	}
	*list_top = NULL;
}
