#include "shell.h"


/**
 * alias_printer - prints the alias and
 * its value stored in the input node's "str"
 * @node: node of the alias
 *
 * Return: 0 (success), 1 (error)
 */

int alias_printer(l_list *node)
{
	char *equal_sign_ptr = NULL;
	char *c_ptr = NULL;

	if (node != NULL)
	{
		equal_sign_ptr = car_finder(node->str, '=');
		/* printing chars before "=" */
		c_ptr = node->str;
		while (c_ptr <= equal_sign_ptr)
		{
			_putchar(*c_ptr);
			c_ptr++;
		}
		_putchar('\'');
		/* printing the remaining chars after "=" */
		_puts(equal_sign_ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}


/**
 *  alias_to_str - convert an alias command in the
 *  form "alias name=value"into a string and
 *  store it in the "sh_args" struct
 *  @content: struct parameter
 *  @str: the alias string
 *  Desc: It facilitates the creation of a new alias and
 *  stores it in @content, but if the value of the alias is
 *  not empty, the function calls @remv_alias with the to remove
 *  any existing alias with the same name as the one being created
 *  and then adds it as new node at the end of a linked list
 *  Return: 0 (success), 1 (error)
 */

int alias_to_str(sh_args *content, char *str)
{
	/* Find the equals sign in the string */
	char *str_p = car_finder(str, '=');

	if (str_p == NULL)
	{
		return (1);
	}
	/* If the value part of the alias is not empty, add or */
	/* update the alias in the structure */
	if (!*++str_p)
	{
		return (remv_alias(content, str));
	}
	remv_alias(content, str);
	/* Add the new alias to the end of the list */
	return (new_end_node(&(content->alias), str, 0) == NULL);
}
