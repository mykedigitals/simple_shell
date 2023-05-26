#include "shell.h"



/**
 * end_from_str - converts string inputs to integer
 * @str: string being converted
 * Desc: It then checks whether the first character
 * of the input string is a + sign. If it is, it increments
 * the pointer (str++) to move past the + sign. whether each
 * character is a digit between 0 and 9. If it is, it
 * multiplies the changed_return by 10 and adds the
 * value of the current digit to it. If the changed_return
 * exceeds the maximum value of an integer (INT_MAX),
 * the function returns -1 indicating an error
 *
 * Return: 0 , -1 (error, if the input string contains non-numeric characters)
 */

int end_from_str(char *str)
{
	unsigned long int changed_return = 0;
	int review = 0;

	/* checks for number polarity */
	if (*str == '+')
	{
		str++;
	}
	/* Iterates through the string and convert each digit to integer */
	for (review = 0;  str[review] != '\0'; review++)
	{
		if (str[review] <= '9' && str[review] >= '0')
		{
			changed_return *= 10;
			changed_return += (str[review] - '0');
			if (changed_return > INT_MAX)
				return (-1);
		}
		else
		{
			return (-1);
		}
	}
	return (changed_return);
}


/**
 * help_command -  to provide a placeholder
 * for the "help" command in a shell program
 * @element: struct parameter
 *
 * Return: 0
 */

int help_command(shell_args *element)
{
	char **a_v = element->argv;
	/* If no argument is provided, show general help message */
	_puts("Welcome to the Shell Help Menu:\n   help: Show this help menu\n");
	_puts("   cd: Change directory\n   exit: Exit the shell\n");
	if (0)
	{
		_puts(*a_v);
	}
	return (0);
}
