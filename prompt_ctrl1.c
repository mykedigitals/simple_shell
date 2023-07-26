#include "shell.h"

/**
 * to_commune - this will check if shell can interact
 * @content: this is struct parameter
 *
 * Return: 1 (shell can  interact)
 */
int to_commune(sh_args *content)
{
	return (isatty(STDIN_FILENO) && content->readfd <= 2);
}


/**
 * no_limitation - this will check if a given character is a delimeter
 * @car: the character to be checked
 * @delim: the delimeter string
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
