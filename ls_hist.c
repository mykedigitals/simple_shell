#include "shell.h"

/**
 * hist_cmd_print -  this function make it simple, you can say: "Get a list of all the commands you have used, starting from line 0, with line numbers included."
 * @content: value of struct
 *  Return: Always 0
 */
int hist_cmd_print(sh_args *content)
{
	idx_of_printedList(content->history);
	return (0);
}
