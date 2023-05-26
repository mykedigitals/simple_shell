#include "shell.h"


/**
 * create_strng_find - to write a string to other streams of strings
 * @str: string to be printed back 
 * @go_to_file: the descriptor of file to be written into
 *
 * Return: this returns the value string written
 */

int create_strng_find(char *str, int go_to_file)
{
	int val_num = 0;

	if (!str)
		return (0);
	while (*str)
	{
		val_num += write_chk_to_fd(*str++, go_to_file);
	}
	return (val_num);
}


/**
 * prt_dcm_int - print the value of the
 * "platform_f" argument as a decimal number i.e base 10
 * @platform_f: the value we will be inputting
 * @go_to_file: this describe the file we will be writing into
 *
 * Return: printed characters
 */

int prt_dcm_int(int platform_f, int go_to_file)
{
	int (*print_putc)(char) = _putchar;
	int index, val_num = 0;
	unsigned int no_minus_val, remaining;

	/* print_putc writes to stderr*/
	if (go_to_file == STDERR_FILENO)
		print_putc = write_with_buffer;

	if (platform_f < 0)
	{
		no_minus_val = -platform_f;
		print_putc('-');
		val_num++;
	}
	else
		no_minus_val = platform_f;
	remaining = no_minus_val;
	for (index = 1000000000; index > 1; index /= 10)
	{
		if (no_minus_val / index)
		{
			print_putc('0' + remaining / index);
			val_num++;
		}
		remaining %= index;
	}
	print_putc('0' + remaining);
	val_num++;

	return (val_num);
}
