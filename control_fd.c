#include "shell.h"


/**
 * stringwrite_toFd - This function write the str
 * to a stream
 * @str: str that is printed
 * @fil_des: filedes written to
 *
 * Return: chars written
 */
int stringwrite_toFd(char *str, int fil_des)
{
	int count = 0;

	if (!str)
		return (0);
	while (*str)
	{
		count += charWrite_toFd(*str++, fil_des);
	}
	return (count);
}

/**
 * charWrite_toFd - This function writes chars
 * to a file des fil_des in a buffd manner
 * @car: charr that is to be printed
 * @fil_des: filedes written to
 *
 * Return: 1 (success), -1 (error)
 */
int charWrite_toFd(int fil_des, char car)
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


/**
 * decimal_intPrint - print the value of the
 * "feed" argument as a decimal number i.e base 10
 * @feed: the input
 * @fil_des: the filedescriptor to write to
 * Desc: In case the "nourish" contention is negative,
 * the work calculates the supreme esteem of "feed3"
 * and sets avariable named "absol_val" to that esteem.
 * It at that point prints a short sign to demonstrate
 * that the number is negative,and increases the "number"
 * variable to reflect the reality that an extra character
 * was printed, at that point on the off chance that
 * non-negative, the work essentially sets "absol_val" rise
 * to to "nourish". To print it initializes "remaining" to
 * "absol_val", and after that employing a circle to emphasize
 * through the powers of 10, beginning with 1000000000 and
 * partitioning by 10 each time. For each control of 10, the
 * work checks on the off chance that "absol_val" is detachable
 * by that control of 10 In the event that it is, it prints the
 * comparing digit of "remaining" partitioned by that control of 10
 * (utilizing the ASCII code for the digit), and increases the "tally"
 * variable. It at that point overhauls "remaining" to be rise to to
 * the leftover portion of "absol_val" separated by that control of 10.
 * At that point work prints the final digit of "remaining" moreover
 * utilizing the ASCII code and increases "number" one last time.
 * It at that point returns the esteem of "number", showing how numerous
 * characters were printed
 * Return: printed characters
 */

int decimal_intPrint(int feed, int fil_des)
{
	int (*_puchar)(char) = _putchar;
	int index, count = 0;
	unsigned int absol_val, remaining;

	/* _puchar writes to stderr*/
	if (fil_des == STDERR_FILENO)
		_puchar = using_buffer_to_write;

	if (feed < 0)
	{
		absol_val = -feed;
		_puchar('-');
		count++;
	}
	else
		absol_val = feed;
	remaining = absol_val;
	for (index = 1000000000; index > 1; index /= 10)
	{
		if (absol_val / index)
		{
			_puchar('0' + remaining / index);
			count++;
		}
		remaining %= index;
	}
	_puchar('0' + remaining);
	count++;

	return (count);
}
