#include "shell.h"



/**
 * exit_str_to_int - converts string inputs to integer
 * @str: string being converted
 * Desc: It then checks whether the first character
 * of the input string is a + sign. If it is, it increments
 * the pointer (str++) to move past the + sign. whether each
 * character is a digit between 0 and 9. If it is, it
 * multiplies the converted_output by 10 and adds the
 * value of the current digit to it. If the converted_output
 * exceeds the maximum value of an integer (INT_MAX),
 * the function returns -1 indicating an error
 * 
 *
 * Return: 0 , -1 (error, if the input string contains non-numeric characters)
 */

int exit_str_to_int(char *str)
{
	unsigned long int converted_output = 0;
	int count = 0;

	/* checks for number polarity */
	if (*str == '+')
	{
		str++;
	}
	/* Iterates through the string and convert each digit to integer */
	for (count = 0;  str[count] != '\0'; count++)
	{
		if (str[count] <= '9' && str[count] >= '0')
		{
			converted_output *= 10;
			converted_output += (str[count] - '0');
			if (converted_output > INT_MAX)
				return (-1);
		}
		else
		{
			return (-1);
		}
	}
	return (converted_output);
}


/**
 * help_command -  to provide a placeholder
 * for the "help" command in a shell program
 * @content: struct parameter
 *
 * Return: 0
 */

int help_command(sh_args *content)
{
	char **arg_v = content->argv;
	/* If no argument is provided, show general help message */
	_puts("Welcome to the Shell Help Menu:\n   help: Show this help menu\n");
	_puts("   cd: Change directory\n   exit: Exit the shell\n");
	if (0)
	{
		_puts(*arg_v);
	}
	return (0);
}
