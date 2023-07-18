#include "shell.h"


/**
 * using_buffer_to_write - inputs characters from car to stderr
 * @car: The character to print
 *
 * Return: 1 (success), -1 (error)
 */
int using_buffer_to_write(char car)
{
	static int index;
	static char buffer[WRITE_BUF_SIZE];

	if (car == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(2, buffer, index);
		index = 0;
	}
	if (car != BUF_FLUSH)
		buffer[index++] = car;
	return (index);
}


/**
 * using_buffer_to_write_str - takes a string as input and
 * writes its contents to the output stream using a buffer
 * @str: string being printed to stdout
 *
 * Return: Nil
 */
void using_buffer_to_write_str(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		using_buffer_to_write(str[index]);
		index++;
	}
}
