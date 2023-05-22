#include "shell.h"

/**
 * delete_node_index - delete a node in a linked list at a specific index
 * @list_head: head node
 * @index: index node being deleted
 *
 * Return: 1 (success), 0 (failure)
 */
int delete_node_index(l_list **list_head, unsigned int index)
{
	l_list *current_node, *preceding_node;
	unsigned int x = 0;

	if (!list_head || !*list_head)
		return (0);

	if (!index)
	{
		current_node = *list_head;
		*list_head = (*list_head)->link;
		free(current_node->str);
		free(current_node);
		return (1);
	}
	current_node = *list_head;
	while (current_node)
	{
		if (x == index)
		{
			preceding_node->link = current_node->link;
			free(current_node->str);
			free(current_node);
			return (1);
		}
		x++;
		preceding_node = current_node;
		current_node = current_node->link;
	}
	return (0);
}


/**
 * free_l_list - frees all list
 * @list_head: head node
 *
 * Return: void
 */
void free_l_list(l_list **list_head)
{
	l_list *current_node, *next_node, *head;

	if (!list_head || !*list_head)
		return;
	head = *list_head;
	current_node = head;
	while (current_node)
	{
		next_node = current_node->link;
		free(current_node->str);
		free(current_node);
		current_node = next_node;
	}
	*list_head = NULL;
}
