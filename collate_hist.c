#include "shell.h"

/**
 * order_print_rec -  print out the command history,
 * consecutively, leading with line numbers, from 0
 * @element: struct parameter
 *  Return: Always 0
 */
int order_print_rec(shell_args *element)
{
	prt_l_list_in_sort(element->record);
	return (0);
}
