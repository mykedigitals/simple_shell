#include "shell.h"

/**
 * hist_cmd_print -  print out the command history,
 * consecutively, leading with line numbers, from 0
 * @content: struct parameter
 *  Return: Always 0
 */
int hist_cmd_print(sh_args *content)
{
	idx_of_printedList(content->history);
	return (0);
}
