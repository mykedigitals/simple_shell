#include "shell.h"


/**
 * check_env_unsetenv - verifies the number of
 * arguments being passed to env_setter unsetenv_clone
 * @content: struct parameter
 *
 *  Return: 0
 */

int check_env_unsetenv(sh_args *content)
{
	int idx;

	if (content->argc == 1)
	{
		/* Prints errors */
		write_string_with_buffer("Too few arguements.\n");
		return (1);
	}

	for (idx = 1; idx <= content->argc; idx++)
	{
		/* calls d unsetenv_clone function with d args in the struct sh_args */
		/* and the command-line argument at the current index */
		unsetenv_clone(content, content->argv[idx]);
	}
	return (0);
}



/**
 * env_clone - print the current environment variables of the program
 * @content: struct parameter
 *
 * Return: 0
 */
int env_clone(sh_args *content)
{
	int xx = 0;
	/* Extract the environment variables from d sh_args struct and prints */
	prnt_l_list_str(content->env);

	return (xx);
}


/**
 * getenv_clone - search for an environment variable with
 * the given name in the linked list pointed to by content->env
 * and return a pointer to its value if it is found
 * @content: struct parameter
 * @name: name of env var
 *
 * Return: the value
 */
char *getenv_clone(sh_args *content, const char *name)
{
	char *ptr;
	l_list *node;

	node = content->env;

	while (node)
	{
		ptr = find_substr_at_start(node->str, name);
		if (ptr && *ptr)
			return (ptr);
		node = node->link;
	}

	return (NULL);
}
