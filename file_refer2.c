#include "shell.h"


/**
 * print_refer - prints the alias and
 * its value stored in the input node's "str"
 * @node: node of the alias
 *
 * Return: 0 (success), 1 (error)
 */

int print_refer(l_list *node)
{
	char *ptr_equality = NULL;
	char *top_tier = NULL;

	if (node != NULL)
	{
		ptr_equality = locate_char(node->str, '=');
		/* printing chars before "=" */
		top_tier = node->str;
		while (top_tier <= ptr_equality)
		{
			_putchar(*top_tier);
			top_tier++;
		}
		_putchar('\'');
		/* printing the remaining chars after "=" */
		_puts(ptr_equality + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}


/**
 *  refer_to_word - convert an alias command in the
 *  form "alias name=value"into a string and
 *  store it in the "shell_args" struct
 *  @element: struct parameter
 *  @str: the alias string
 *  Desc: It facilitates the creation of a new alias and
 *  stores it in @element, but if the value of the alias is
 *  not empty, the function calls @comot_refer with the to remove
 *  any existing alias with the same name as the one being created
 *  and then adds it as new node at the end of a linked list
 *  Return: 0 (success), 1 (error)
 */

int refer_to_word(shell_args *element, char *str)
{
	/* Find the equals sign in the string */
	char *str_p = locate_char(str, '=');

	if (str_p == NULL)
	{
		return (1);
	}
	/* If the value part of the alias is not empty, add or */
	/* update the alias in the structure */
	if (!*++str_p)
	{
		return (comot_refer(element, str));
	}
	comot_refer(element, str);
	/* Add the new alias to the end of the list */
	return (updated_tail_node(&(element->alias), str, 0) == NULL);
}
