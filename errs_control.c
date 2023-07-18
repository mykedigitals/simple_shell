#include "shell.h"


/**
 * error_msg_print - The function writes an
 * error message to the standard error output
 * @content: struct parameter
 * @err_str: information about the source of the error
 *
 * Return: 0
 */
void error_msg_print(sh_args *content, char *err_str)
{
	using_buffer_to_write_str(content->fname);
	using_buffer_to_write_str(": ");
	decimal_intPrint(content->line_count, STDERR_FILENO);
	using_buffer_to_write_str(": ");
	using_buffer_to_write_str(content->argv[0]);
	using_buffer_to_write_str(": ");
	using_buffer_to_write_str(err_str);
}
