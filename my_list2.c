#include "shell.h"

/**
 * list_span - finds length of linked list
 * @top: top node
 *
 * Return: list size
 */
size_t list_span(const l_list *top)
{
	size_t index = 0;

	while (top)
	{
		top = top->link;
		index++;
	}
	return (index);
}


/**
 * prt_l_list_in_sort - prints all elements of a l_list linked list
 * @top: top node
 *
 * Return: list size
 */
size_t prt_l_list_in_sort(const l_list *top)
{
	size_t index = 0;

	while (top)
	{
		_puts(created_iota(top->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(top->str ? top->str : "(nil)");
		_puts("\n");
		top = top->link;
		index++;
	}
	return (index);
}


/**
 * chng_list_to_strng - create an array of strings from list->str
 * @top: top node
 *
 * Return: array of strings
 */
char **chng_list_to_strng(l_list *top)
{
	l_list *node = top;
	size_t index = list_span(top), x;
	char **str_array;
	char *str;

	if (!top || !index)
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

		str = clone_str(str, node->str);
		str_array[index] = str;
	}
	str_array[index] = NULL;
	return (str_array);
}
