#include "shell.h"


/**
 * main - the running a custom shell program
 * @arg_c: argument count
 * @arg_v: argument vector
 *
 * Return: 0 (success), 1 (error)
 */
int main(int arg_c, char **arg_v)
{
	shell_args element[] = { INFO_INIT };
	int ent_int = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (ent_int)
		: "r" (ent_int));

	if (arg_c == 2)
	{
		ent_int = open(arg_v[1], O_RDONLY);
		if (ent_int == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				write_string_with_buffer(arg_v[0]);
				write_string_with_buffer(": 0: Can't open ");
				write_string_with_buffer(arg_v[1]);
				write_with_buffer('\n');
				write_with_buffer(BUFF_FLUSHH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		element->seefd = ent_int;
	}

	fillup_ct_surr(element);
	load_record(element);
	created_sh(element, arg_v);
	return (EXIT_SUCCESS);
}
