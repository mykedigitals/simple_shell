#include "shell.h"


/**
 *  * multi_free - frees memory allocated to a string of strings
 *   * @str_ptr: pointer to a string of strings
 *    */
void multi_free(char **str_ptr)
{
	char **my_strings;

	my_strings = str_ptr;
	if (str_ptr == NULL)
	{
		return;
	}
	while (*str_ptr != NULL)
	{
		free(*str_ptr++);
	}
	free(my_strings);
}


/**
 *  memset_clone - emulates "memset()"
 *  function as it fills memory with a constant byte
 *  @ptr: pointer to the memory area to be filled
 *  @value: the value to be filled in the memory block
 *  @num: the number of bytes to be set in the memory block
 *  
 *  Return: pointer to the memory area
 */

char *memset_clone(char *ptr, char value, unsigned int num)
{
	unsigned int x;

	x = 0;
	/* Set each byte of the memory block to the given value */
	while  (num > x)
	{
		ptr[x] = value;
		x++;
	}
	return (ptr);
}
