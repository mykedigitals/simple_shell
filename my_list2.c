#include "shell.h"

/**
 * list_len - finds length of linked list
 * @head: head node
 *
 * Return: list size
 */
size_t list_len(const l_list *head)
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
 * prnt_l_list_with_index - prints all elements of a l_list linked list
 * @head: head node
 *
 * Return: list size
 */
size_t prnt_l_list_with_index(const l_list *head)
{
	size_t index = 0;

	while (head)
	{
		_puts(custom_itoa(head->num, 10, 0));
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
 * conv_list_to_strings - create an array of strings from list->str
 * @head: head node
 *
 * Return: array of strings
 */
char **conv_list_to_strings(l_list *head)
{
	l_list *node = head;
	size_t index = list_len(head), x;
	char **str_array;
	char *str;

	if (!head || !index)
		return (NULL);
	str_array = malloc(sizeof(char *) * (index + 1));
	if (!str_array)
		return (NULL);
	for (index = 0; node; node = node->link, index++)
	{
		str = malloc(len_of_str(node->str) + 1);
		if (!str)
		{
			for (x = 0; x < index; x++)
				free(str_array[x]);
			free(str_array);
			return (NULL);
		}

		str = str_cpy(str, node->str);
		str_array[index] = str;
	}
	str_array[index] = NULL;
	return (str_array);
}
