#include "shell.h"

/**
 * print_command_record -  print out the command history,
 * consecutively, leading with line numbers, from 0
 * @element: struct parameter
 *  Return: Always 0
 */
int print_command_record(shell_args *element)
{
	prt_l_list_in_sort(element->record);
	return (0);
}
