#include "shell.h"


/**
 * convert_aliasToStr - convert an alias command in the
 * form "alias name=value"into a string and
 * store it in the "sh_args" struct
 * @content: struct parameter
 * @str: the alias string
 * Desc: It facilitates the creation of a new alias and
 * stores it in @content, but if the value of the alias is
 * not empty, the function calls @alias_rm with the to remove
 * any existing alias with the same name as the one being created
 * and then adds it as new node at the end of a linked list
 *
 * Return: 0 (success), 1 (error)
 */
int convert_aliasToStr(sh_args *content, char *str)
{
	/* Find the equals sign in the string */
	char *str_p = to_find_char(str, '=');

	if (str_p == NULL)
	{
		return (1);
	}
	/* If the value part of the alias is not empty, add or */
	/* update the alias in the structure */
	if (!*++str_p)
	{
		return (alias_rm(content, str));
	}

	alias_rm(content, str);
	/* Add the new alias to the end of the list */
	return (endOf_node(&(content->alias), str, 0) == NULL);
}


/**
 * alias_rm - removes an alias command in the form
 * "alias name=value" from "sh_args" struct
 * @content: struct parameter
 * @str: the alias string
 * Desc: It copies alias name from @str_p to @copy, then
 * set @str_p to null (\0) to terminate the string at that point.
 * The locate_idx_node function is then called to find the index
 * of the node in the alias linked list that starts with the string
 * before the equal sign. The prefix_of_firstNode function is
 * used to perform the comparison. If a matching node is found, the
 * rm_node_idx function is called
 * to remove the node from the linked list.
 *
 * Return: 0 (success), 1 (error)7
 */
int alias_rm(sh_args *content, char *str)
{
	/* Find the position of the '=' character in the input string */
	int remover;
	char copy;
	char *str_p = to_find_char(str, '=');

	if (!str_p)
	{
		return (1);
	}
	/* Temporarily replace the '=' character with a null terminator */
	copy = *str_p;
	*str_p = 0;

	 /* Get d index of d first node in d alias list that matches the prefix */
	/* Delete the node at the given index from the alias list */
	remover = rm_node_idx(&(content->alias),
		locate_idx_node(content->alias,
		prefix_of_firstNode(content->alias, str, -1)));
	/* Restore the '=' character to the input string */
	*str_p = copy;
	return (remover);
}


/**
 * getting_alias - prints the alias and
 * its value stored in the input node's "str"
 * @node: node of the alias
 *
 * Return: 0 (success), 1 (error)
 */
int getting_alias(l_list *node)
{
	char *equal_sign_ptr = NULL;
	char *c_ptr = NULL;

	if (node != NULL)
	{
		equal_sign_ptr = to_find_char(node->str, '=');

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
 * duplicate_alias - prints out the name and value of each alias
 * @content: struct parameter
 *
 *  Return: 0
 */
int duplicate_alias(sh_args *content)
{
	int idx = 0;
	char *car = NULL;
	l_list *node = NULL;

	if (content->argc == 1)
	{
		/* prints the node while iterating through the linked list */
		node = content->alias;
		for ( ; node != NULL; node = node->link)
			getting_alias(node);
		return (0);
	}
	idx = 1;
	while (content->argv[idx])
	{
		car = to_find_char(content->argv[idx], '=');
		if (car != NULL)
			convert_aliasToStr(content, content->argv[idx]);
		else
			getting_alias(prefix_of_firstNode(
				content->alias, content->argv[idx], '='));
		idx++;
	}

	return (0);
}
