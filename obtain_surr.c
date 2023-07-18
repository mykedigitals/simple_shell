#include "shell.h"


/**
 * surr_set - sets or updates an environment
 * variable with a given name and value
 * @content: struct parameter
 * @name: the name of the environment variable to be set
 * @value: the value of the environment variable to be set
 * Desc: It concatenates the name and value of the environment
 *	variable, along with the equal sign, into the buffer
 *	then looks for an existing variable with the same name as
 *	the one being set. If it finds a matching variable, it frees the
 *	existing string for that variable and replaces it with the
 *	new string in the buffer, then it sets a flag
 *	indicating that the environment has been changed
 *	"content->env_changed". If it does not find a matching
 *	variable, it adds a new node to the end of the linked
 *	list of environment variables, with the new string in
 *	the buffer as its value.
 *
 * Return: Always 0
 */
int surr_set(sh_args *content, char *name, char *value)
{
	char *buffer = NULL;
	l_list *node;
	char *str;

	if (!name || !value)
		return (0);

	/* allocates memory for a buffer that is large*/
	/*enough to hold the name and value of the */
	/* environment variable, plus an equal sign and a null terminator. */
	buffer = malloc(string_lent(name) + string_lent(value) + 2);
	if (!buffer)
		return (1);
	copy_string(buffer, name);
	extend_string(buffer, "=");
	extend_string(buffer, value);
	node = content->env;
	while (node)
	{
		str = on_startFind_sub(node->str, name);
		if (str && *str == '=')
		{
			free(node->str);
			node->str = buffer;
			content->env_changed = 1;
			return (0);
		}
		node = node->link;
	}
	endOf_node(&(content->env), buffer, 0);
	free(buffer);
	content->env_changed = 1;
	return (0);
}


/**
 * unsetduplicate_surr - to remove a variable from the environment
 * @content: struct parameter
 * @var: name of the variable to remove from the environment
 * Desc: Each node in the list contains a string that
 * represents a single environment variable in the format
 * VARNAME=VALUE. "on_startFind_sub" checks if
 * the node's string starts with var, is non-null, then the node
 * represents the environment variable to remove.
 * The function calls rm_node_idx to remove the node
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
int unsetduplicate_surr(sh_args *content, char *var)
{
	/* represents the current environment variables */
	l_list *node = content->env;
	size_t index = 0;
	char *ptr;

	if (!node || !var)
		return (0);

	while (node)
	{
		ptr = on_startFind_sub(node->str, var);
		if (ptr && *ptr == '=')
		{
			content->env_changed = rm_node_idx(&(content->env), index);
			index = 0;
			node = content->env;
			continue;
		}
		node = node->link;
		index++;
	}
	return (content->env_changed);
}


/**
 * get_surround - retrieve the current environment
 * variables as an array of strings and it caches it
 * @content: struct parameter
 * Desc: If the environ field of the sh_args struct is empty
 * or has been changed since the last time get_surround was
 * called, the function will convert the linked list of
 * environment variables in the env field of the sh_args
 * struct to an array of strings using the list_toStrings_list
 * function and store the resulting array in the environ field.
 * The env_changed field is then set to 0 to indicate
 * that the environment variables have not
 * changed since the last call to get_surround
 *
 * Return: 0
 */
char **get_surround(sh_args *content)
{
	if (!content->environ || content->env_changed)
	{
		content->environ = list_toStrings_list(content->env);
		content->env_changed = 0;
	}

	return (content->environ);
}
