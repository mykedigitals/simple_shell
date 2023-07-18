#include "shell.h"


/**
 * main - encapsulates the running a custom shell program
 * @arg_c: argument count
 * @arg_v: argument vector
 *
 * Return: 0 (success), 1 (error)
 */
int main(int arg_c, char **arg_v)
{
	sh_args content[] = { INFO_INIT };
	int fil_des = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fil_des)
		: "r" (fil_des));

	if (arg_c == 2)
	{
		fil_des = open(arg_v[1], O_RDONLY);
		if (fil_des == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				using_buffer_to_write_str(arg_v[0]);
				using_buffer_to_write_str(": 0: Can't open ");
				using_buffer_to_write_str(arg_v[1]);
				using_buffer_to_write('\n');
				using_buffer_to_write(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		content->readfd = fil_des;
	}
	listing_surr_amt(content);
	hist_process(content);
	self_created_sh(content, arg_v);
	return (EXIT_SUCCESS);
}
