#include "shell.h"

/**
 * correct_shell_args - default reset of the values of the
 * areas in that struct to their default values
 * @element: struct parameter
 */
void correct_shell_args(shell_args *element)
{
	element->arg = NULL;
	element->argv = NULL;
	element->path = NULL;
	element->argc = 0;
}


/**
 * empty_shell_args - frees shell_args areas
 * @element: struct parameter
 * @areas: areas
 */
void empty_shell_args(shell_args *element, int areas)
{
	double_empty(element->argv);
	element->argv = NULL;
	element->path = NULL;
	if (areas)
	{
		if (!element->cd_buff)
			free(element->arg);
		if (element->surr)
			empty_l_list(&(element->surr));
		if (element->record)
			empty_l_list(&(element->record));
		if (element->alias)
			empty_l_list(&(element->alias));
		double_empty(element->environ);
		element->environ = NULL;
		empty_n_NULL((void **)element->cd_buff);
		if (element->seefd > 2)
			close(element->seefd);
		_putchar(BUF_FLUSH);
	}
}

