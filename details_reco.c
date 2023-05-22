#include "s_shell.h"

/**
 * fill_sh_args - sets the fname field of the struct to the name
 *	of the command being executed
 * @content: struct parameter
 * @arg_v: argument vector
 */
void fill_sh_args(sh_args *content, char **arg_v)
{
	int index = 0;

	content->fname = arg_v[0];
	if (content->arg)
	{
		content->argv = custom_strtow(content->arg, " \t");
		if (!content->argv)
		{

			content->argv = malloc(sizeof(char *) * 2);
			if (content->argv)
			{
				content->argv[0] = str_dup(content->arg);
				content->argv[1] = NULL;
			}
		}
		for (index = 0; content->argv && content->argv[index]; index++)
			;
		content->argc = index;

		replace_alias_with_value(content);
		replace_var_values(content);
	}
}

