#include "shell.h"

/**
 * process_input - reads user input from the command line
 *	(apart from the newline)
 * @content: struct parameter
 *
 * Return: length of the current command
 */
ssize_t process_input(sh_args *content)
{
	static char *command_chain_buffer;
	static size_t current_position, next_position, buffer_length;
	ssize_t input_length = 0;
	char **current_command_pointer = &(content->arg), *current_command;

	_putchar(BUF_FLUSH);
	input_length = get_input_from_stdin(content,
			&command_chain_buffer, &buffer_length);
	if (input_length == -1)
		return (-1);
	if (buffer_length)
	{
		next_position = current_position;
		current_command = command_chain_buffer + current_position;

		evaluate_command_chain(content, command_chain_buffer,
				&next_position, current_position, buffer_length);
		while (next_position < buffer_length)
		{
			if (detect_command_chaining(content, command_chain_buffer, &next_position))
				break;
			next_position++;
		}

		current_position = next_position + 1;
		if (current_position >= buffer_length)
		{
			current_position = buffer_length = 0;
			content->cmd_buf_type = CMD_NORM;
		}

		*current_command_pointer = current_command;
		return (len_of_str(current_command));
	}

	*current_command_pointer = command_chain_buffer;
	return (input_length);
}

/**
 * handle_sigInt - handle signal calls when user presses Ctrl+C
 * @unused_signal_num:  indicates the signal number that triggered
 *	the signal handler
 *
 * Return: nil
 */
void handle_sigInt(__attribute__((unused))int unused_signal_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
