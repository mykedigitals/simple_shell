#include "shell.h"


/**
 * using_buffer_to_write - This function converts inputs
 * characters from char to stderr
 * @car: The char to be printed
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
 * composes its substance to the yield stream employing
 * a buffer
 * @str: string being printed in to stdout
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
