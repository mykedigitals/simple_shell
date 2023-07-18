#include "shell.h"


/**
 * locate_idx_node - finds the index of a given node in a linked list
 * @head: head node
 * @target_node: target_node
 *
 * Return: node index starting from 0, -1 (otherwise)
 */
ssize_t locate_idx_node(l_list *head, l_list *target_node)
{
	size_t index = 0;

	while (head)
	{
		if (head == target_node)
			return (index);
		head = head->link;
		index++;
	}
	return (-1);
}


/**
 * prefix_of_firstNode -  searches a linked list of strings for
 *	the first node whose string starts with a given prefix
 * @node: pointer to list head
 * @search_str: string to match
 * @search_char: the next character after search_str to match
 *
 * Return: matching node, null
 */
l_list *prefix_of_firstNode(l_list *node, char *search_str,
		char search_char)
{
	char *match_ptr = NULL;

	while (node)
	{
		match_ptr = on_startFind_sub(node->str, search_str);
		if (match_ptr && ((search_char == -1) || (*match_ptr == search_char)))
			return (node);
		node = node->link;
	}
	return (NULL);
}


/**
 * length_ofList - finds length of linked list
 * @head: head node
 *
 * Return: list size
 */
size_t length_ofList(const l_list *head)
{
	size_t index = 0;

	while (head)
	{
		head = head->link;
		index++;
	}
	return (index);
}


/**
 * idx_of_printedList - prints all elements of a l_list linked list
 * @head: head node
 *
 * Return: list size
 */
size_t idx_of_printedList(const l_list *head)
{
	size_t index = 0;

	while (head)
	{
		_puts(selfCreated_get(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->link;
		index++;
	}
	return (index);
}


/**
 * list_toStrings_list - create an array of strings from list->str
 * @head: head node
 *
 * Return: array of strings
 */
char **list_toStrings_list(l_list *head)
{
	l_list *node = head;
	size_t index = length_ofList(head), x;
	char **str_array;
	char *str;

	if (!head || !index)
		return (NULL);
	str_array = malloc(sizeof(char *) * (index + 1));
	if (!str_array)
		return (NULL);
	for (index = 0; node; node = node->link, index++)
	{
		str = malloc(string_lent(node->str) + 1);
		if (!str)
		{
			for (x = 0; x < index; x++)
				free(str_array[x]);
			free(str_array);
			return (NULL);
		}

		str = copy_string(str, node->str);
		str_array[index] = str;
	}
	str_array[index] = NULL;
	return (str_array);
}
