#include "shell.h"

/**
 * pro_details - this  will read user input from the command line
 *	other than a newline
 * @element: structure parameter
 *
 * Return: length of present command
 */
ssize_t pro_details(shell_args *element)
{
	static char *cmd_order_render;
	static size_t pre_post, post_next, lenght_buff;
	ssize_t details_lenght = 0;
	char **pre_cmd_pointer = &(element->arg), *pre_cmd;

	_putchar(BUF_FLUSH);
	details_lenght = obtain_details_stdin(element,
			&cmd_order_render, &lenght_buff);
	if (details_lenght == -1)
		return (-1);
	if (lenght_buff)
	{
		post_next = pre_post;
		pre_cmd = cmd_order_render + pre_post;

		access_cmd_order(element, cmd_order_render,
				&post_next, pre_post, lenght_buff);
		while (post_next < lenght_buff)
		{
			if (order_cmd_discover(element, cmd_order_render, &post_next))
				break;
			post_next++;
		}

		pre_post = post_next + 1;
		if (pre_post >= lenght_buff)
		{
			pre_post = lenght_buff = 0;
			element->cd_buff_category = CMD_NORM;
		}

		*pre_cmd_pointer = pre_cmd;
		return (string_lent(pre_cmd));
	}

	*pre_cmd_pointer = cmd_order_render;
	return (details_lenght);
}

/**
 * sigint_control - handle signal calls when user presses Ctrl+C
 * @unused_signal_num:  indicates the signal number that triggered
 *	the signal handler
 *
 * Return: nil
 */
void sigint_control(__attribute__((unused))int unused_signal_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
