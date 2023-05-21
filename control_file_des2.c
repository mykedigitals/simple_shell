#include "shell.h"


/**
 * write_car_to_fd - writes characters
 * to a file descriptor fil_des in a buffered manner
 * @car: character being printed
 * @fil_des: filedescriptor written to
 *
 * Return: 1 (success), -1 (error)
 */

int write_car_to_fd(int fil_des, char car)
{
	static int index;
	static char buffer[WRITE_BUF_SIZE];

	if (car == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(fil_des, buffer, index);
		index = 0;
	}
	if (car != BUF_FLUSH)
		buffer[index++] = car;
	return (1);
}
