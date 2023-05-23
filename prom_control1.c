#include "s_shell.h"

/**
 * reciprocate - this checks a shell is reciprocating
 * @element: struct parameter
 *
 * Return: 1 (is interactive mode)
 */

int reciprocate(shell_args *element)
{
	return (isatty(STDIN_FILENO) && element->readfd <= 2);
}



/**
 * separator - this checks if a given character can separate
 * @chk: character under check
 * @delim: delimeter string
 *
 * Return: 1 (true), 0 (false)
 */

int separator(char chk, char *delim)
{
	while (*delim)
		if (*delim++ == car)
			return (1);
	return (0);
}
