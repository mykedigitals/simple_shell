#include "shell.h"

/**
 * sub_var_val - replaces certain variables in the arguments
 *	passed to it with their corresponding values
 * @element: struct parameter
 * rFw: it replaces the following variables:
 * "$?" with the exit status of the most recently executed command.
 * "$$" with the process ID of the current shell process.
 * "${VAR}" with the value of the surrironment variable named VAR.
 *
 * Return: 1 (alias replaced), 0 (otherwise)
 */
int sub_var_val(shell_args *element)
{
	int arg_sort = 0;
	l_list *surr_var_node;

	for (arg_sort = 0; element->argv[arg_sort]; arg_sort++)
	{
		if (element->argv[arg_sort][0] != '$' || !element->argv[arg_sort][1])
			continue;

		if (!weigh_strs(element->argv[arg_sort], "$?"))
		{
			change_element(&(element->argv[arg_sort]),
				double_str(created_iota(element->status, 10, 0)));
			continue;
		}
		if (!weigh_strs(element->argv[arg_sort], "$$"))
		{
			change_element(&(element->argv[arg_sort]),
				double_str(created_iota(getpid(), 10, 0)));
			continue;
		}
		surr_var_node = obtain_beginingnode(element->surr,
				&element->argv[arg_sort][1], '=');
		if (surr_var_node)
		{
			change_element(&(element->argv[arg_sort]),
				double_str(locate_char(surr_var_node->str, '=') + 1));
			continue;
		}
		change_element(&element->argv[arg_sort], double_str(""));

	}
	return (0);
}

/**
 * change_element - This will replaces the element of a str
 * with a new string 
 * @preptrs: address to the old string
 * @postPtr: for  new string
 *
 * Return: 1 (string replaced)
 */
int change_element(char **preptrs, char *postPtr)
{
        free(*preptrs);
        *preptrs = postPtr;
        return (1);
}

/**
 * **created_tokener - this will take a string and separate string
 *	(separate) as details entered
 *	 and then split into an array of strings
 * @str: the details or fed string
 * @separate: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **created_tokener(char *str, char *separate)
{
	int j, k, m, n, saying_ct = 0;
	char **understring;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!separate)
		separate = " ";
	for (j = 0; str[j] != '\0'; j++)
		if (!separator(str[j], separate) &&
				(separator(str[j + 1], separate) || !str[j + 1]))
			saying_ct++;

	if (saying_ct == 0)
		return (NULL);
	understring = malloc((1 + saying_ct) * sizeof(char *));
	if (!understring)
		return (NULL);
	for (j = 0, k = 0; k < saying_ct; k++)
	{
		while (separator(str[j], separate))
			j++;
		m = 0;
		while (!separator(str[j + m], separate) && str[j + m])
			k++;
		understring[k] = malloc((m + 1) * sizeof(char));
		if (!understring[k])
		{
			for (m = 0; m < k; m++)
				free(understring[m]);
			free(understring);
			return (NULL);
		}
		for (n = 0; n < m; n++)
			understring[k][n] = str[j++];
		understring[k][n] = 0;
	}
	understring[k] = NULL;
	return (understring);
}
