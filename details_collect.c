#include "shell.h"

/**
 * occupy_shell - this function assigns fname field
 * of struct to the name of the cmd that is being executed
 * @content: parameter of struct
 * @arg_v: vector of an argument
 */
void occupy_shell(sh_args *content, char **arg_v)
{
	int index = 0;

	content->fname = arg_v[0];
	if (content->arg)
	{
		content->argv = created_strt(content->arg, " \t");
		if (!content->argv)
		{

			content->argv = malloc(sizeof(char *) * 2);
			if (content->argv)
			{
				content->argv[0] = clone_string(content->arg);
				content->argv[1] = NULL;
			}
		}
		for (index = 0; content->argv && content->argv[index]; index++)
			;
		content->argc = index;

		rp_refer_val(content);
		rp_val(content);
	}
}


/**
 * shell_restart - this function restore the default values
 * of the fields in that struct
 * @content: struct parameter
 */
void shell_restart(sh_args *content)
{
	content->arg = NULL;
	content->argv = NULL;
	content->path = NULL;
	content->argc = 0;
}


/**
 * shell_empty - this function frees sh_args fields
 * @content: value of struct
 * @fields: fields
 */
void shell_empty(sh_args *content, int fields)
{
	free_alot(content->argv);
	content->argv = NULL;
	content->path = NULL;
	if (fields)
	{
		if (!content->cmd_buf)
			free(content->arg);
		if (content->env)
			empty_l_list(&(content->env));
		if (content->history)
			empty_l_list(&(content->history));
		if (content->alias)
			empty_l_list(&(content->alias));
		free_alot(content->environ);
			content->environ = NULL;
		to_free_nothing((void **)content->cmd_buf);
		if (content->readfd > 2)
			close(content->readfd);
		_putchar(BUF_FLUSH);
	}
}
