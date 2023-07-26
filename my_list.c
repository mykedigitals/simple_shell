#include "shell.h"


/**
 * list_of_stringPrint - print all the strings put away
 * in a independently connected list of strings, with
 * each string taken after by a newline character
 * @head: pointer to the beginning of the node
 *
 * Return: amounts of hubs navigated within the connected list
 */
size_t list_of_stringPrint(const l_list *head)
{
	size_t index = 0;

	while (head)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->link;
		index++;
	}
	return (index);
}


/**
 * endOf_node - includes an update node to the
 * conclusion of a connected list
 * @list_head: the top of the node
 * @str: strs
 * @num: index
 *
 * Return: size of the connected list
 */
l_list *endOf_node(l_list **list_head, const char *str, int num)
{
	l_list *new_node, *current_node;

	if (!list_head)
		return (NULL);

	current_node = *list_head;
	new_node = malloc(sizeof(l_list));
	if (!new_node)
		return (NULL);
	cpy_setof_mem((void *)new_node, 0, sizeof(l_list));
	new_node->num = num;
	if (str)
	{
		new_node->str = clone_string(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (current_node)
	{
		while (current_node->link)
			current_node = current_node->link;
		current_node->link = new_node;
	}
	else
		*list_head = new_node;
	return (new_node);
}


/**
 * rm_node_idx - remove a hub in a connected list at a particular index
 * @list_head: head node
 * @index: index node being deleted
 *
 * Return: 1 if success, else 0
 */
int rm_node_idx(l_list **list_head, unsigned int index)
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
 * empty_l_list - this function liberates all list
 * @list_head: the tip of the node
 *
 * Return: null
 */
void empty_l_list(l_list **list_head)
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
