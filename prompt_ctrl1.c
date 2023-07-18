#include "shell.h"

/**
 * to_commune - checks if shell is in interactive mode
 * @content: struct parameter
 *
 * Return: 1 (is interactive mode)
 */
int to_commune(sh_args *content)
{
	return (isatty(STDIN_FILENO) && content->readfd <= 2);
}


/**
 * no_limitation - checks if a given
 * character is a delimeter character
 * @car: character being check
 * @delim: delimeter string
 *
 * Return: 1 (true), 0 (false)
 */
int no_limitation(char car, char *delim)
{
	while (*delim)
		if (*delim++ == car)
			return (1);
	return (0);
}
