#include "shell.h"


/**
 * env_setter - sets or updates an environment
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
int env_setter(sh_args *content, char *name, char *value)
{
	int xx = 1, yy = 0, zz = 2;
	char *buffer = NULL, *str;
	l_list *node;

	if (value == NULL || name == NULL)
		return (yy);

	/* allocates memory for a buffer that is large*/
	/*enough to hold the name and value of the */
	/* environment variable, plus an equal sign and a null terminator. */
	buffer = malloc(len_of_str(value) + len_of_str(name) + zz);
	if (buffer == NULL)
		return (xx);
	str_cpy(buffer, name);
	concat_str(buffer, "=");
	concat_str(buffer, value);
	/* Traverse the linked list of environment variables to find */
	/* the variable with the same name as the given name */
	node = content->env;
	for ( ; node != NULL; node = node->link)
	{
		str = find_substr_at_start(node->str, name);
		if (*str == '=' && str != NULL)
		{
			free(node->str);
			node->str = buffer;
			content->env_changed = xx;
			return (yy);
		}
	}
	new_end_node(&(content->env), buffer, yy);
	free(buffer);
	content->env_changed = xx;
	return (yy);
}


/**
 * environ_getter - retrieve the current environment
 * variables as an array of strings and it caches it
 * @content: struct parameter
 * Desc: If the environ field of the sh_args struct is empty
 * or has been changed since the last time environ_getter was
 * called, the function will convert the linked list of
 * environment variables in the env field of the sh_args
 * struct to an array of strings using the conv_list_to_strings
 * function and store the resulting array in the environ field.
 * The env_changed field is then set to 0 to indicate
 * that the environment variables have not
 * changed since the last call to environ_getter
 *
 * Return: 0
 */
char **environ_getter(sh_args *content)
{
	int yy = 0;

	if (content->env_changed || content->environ == NULL)
	{
		content->environ = conv_list_to_strings(content->env);

		/* reset the env_vars_changed flag */
		content->env_changed = yy;
	}

	return (content->environ);
}
