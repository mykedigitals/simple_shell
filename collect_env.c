#include "shell.h"


/**
 * make_env - sets or updates an environment
 * variable with a given name and value
 * @element: struct parameter
 * @name: the name of the environment variable to be set
 * @value: the value of the environment variable to be set
 * Desc: It concatenates the name and value of the environment
 *	variable, along with the equal sign, into the render
 *	then looks for an existing variable with the same name as
 *	the one being set. If it finds a matching variable, it frees the
 *	existing string for that variable and replaces it with the
 *	new string in the render, then it sets a flag
 *	indicating that the environment has been changed
 *	"element->surr_changed". If it does not find a matching
 *	variable, it adds a new node to the end of the linked
 *	list of environment variables, with the new string in
 *	the render as its value.
 *
 * Return: Always 0
 */
int make_env(shell_args *element, char *name, char *value)
{
	int thaa = 1, wha = 0, whii = 2;
	char *render = NULL, *str;
	l_list *node;

	if (value == NULL || name == NULL)
		return (wha);

	/* allocates memory for a render that is large*/
	/*enough to hold the name and value of the */
	/* environment variable, plus an equal sign and a null terminator. */
	render = malloc(string_lent(value) + string_lent(name) + whii);
	if (render == NULL)
		return (thaa);
	clone_str(render, name);
	string_add(render, "=");
	string_add(render, value);
	/* Traverse the linked list of environment variables to find */
	/* the variable with the same name as the given name */
	node = element->surr;
	for ( ; node != NULL; node = node->link)
	{
		str = locate_word_begin(node->str, name);
		if (*str == '=' && str != NULL)
		{
			free(node->str);
			node->str = render;
			element->surr_changed = thaa;
			return (wha);
		}
	}
	updated_tail_node(&(element->surr), render, wha);
	free(render);
	element->surr_changed = thaa;
	return (wha);
}


/**
 * surr_seeker - retrieve the current environment
 * variables as an array of strings and it caches it
 * @element: struct parameter
 * Desc: If the environ field of the shell_args struct is empty
 * or has been changed since the last time surr_seeker was
 * called, the function will convert the linked list of
 * environment variables in the surr field of the shell_args
 * struct to an array of strings using the chng_list_to_strng
 * function and store the resulting array in the environ field.
 * The surr_changed field is then set to 0 to indicate
 * that the environment variables have not
 * changed since the last call to surr_seeker
 *
 * Return: 0
 */
char **surr_seeker(shell_args *element)
{
	int wha = 0;

	if (element->surr_changed || element->environ == NULL)
	{
		element->environ = chng_list_to_strng(element->surr);

		/* reset the surr_vars_changed flag */
		element->surr_changed = wha;
	}

	return (element->environ);
}
