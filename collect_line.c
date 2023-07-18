#include "shell.h"


/**
 * put_prosez - reads user input from the command line
 *	(apart from the newline)
 * @content: struct parameter
 *
 * Return: length of the current command
 */
ssize_t put_prosez(sh_args *content)
{
	static char *command_chain_buffer;
	static size_t current_position, next_position, buffer_length;
	ssize_t input_length = 0;
	char **current_command_pointer = &(content->arg), *current_command;

	_putchar(BUF_FLUSH);
	input_length = stdin_obtained(content,
			&command_chain_buffer, &buffer_length);
	if (input_length == -1)
		return (-1);
	if (buffer_length)
	{
		next_position = current_position;
		current_command = command_chain_buffer + current_position;

		analyse_cmd_chain(content, command_chain_buffer,
				&next_position, current_position, buffer_length);
		while (next_position < buffer_length)
		{
			if (observe_cmd_chain(content, command_chain_buffer, &next_position))
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
		return (string_lent(current_command));
	}

	*current_command_pointer = command_chain_buffer;
	return (input_length);
}


/**
 *  buffer_insert - reads data from a file descriptor into a buffer,
 *	up to a maximum size specified by READ_BUF_SIZE
 * @content: struct parameter
 * @buffer: buffer
 * @bytes_read: size
 *
 * Return: result
 */
ssize_t  buffer_insert(sh_args *content, char *buffer, size_t *bytes_read)
{
	ssize_t result = 0;

	if (*bytes_read)
		return (0);
	result = read(content->readfd, buffer, READ_BUF_SIZE);
	if (result >= 0)
		*bytes_read = result;
	return (result);
}


/**
 * stdin_obtained - reads input from standard input (stdin)
 *	and store it in a buffer
 * @content: parameter struct
 * @input_buffer: buffer's address
 * @buffer_size: buffer_size  address
 * Desc: If there is no input left in the buffer, the function will
 *	fill the buffer by calling getline or insert_line_search function
 *	to read input from stdin. The input is then processed by
 *	removing any trailing newline, removing comments, adding it to
 *	the command history, and determining if it is a command chain
 *	by checking for the presence of a semicolon
 *
 * Return: number of characters read
 */
ssize_t stdin_obtained(sh_args *content, char **input_buffer,
		size_t *buffer_size)
{
	ssize_t read_len = 0;
	size_t allocated_bufferLen = 0;

	if (!*buffer_size)
	{
		free(*input_buffer);
		*input_buffer = NULL;
		signal(SIGINT, input_Ctrl);
#if USE_GETLINE
		read_len = getline(input_buffer, &allocated_bufferLen, stdin);
#else
		read_len = insert_line_search(content, input_buffer, &allocated_bufferLen);
#endif
		if (read_len > 0)
		{
			if ((*input_buffer)[read_len - 1] == '\n')
			{
				(*input_buffer)[read_len - 1] = '\0';
				read_len--;
			}
			content->linecount_flag = 1;
			thisRm_comments(*input_buffer);
			append_inRecord(content, *input_buffer, content->histcount++);
			{
				*buffer_size = read_len;
				content->cmd_buf = input_buffer;
			}
		}
	}
	return (read_len);
}


/**
 * insert_line_search - reads a line of input from a file or a stream
 *	and store it in a character array
 * @content: parameter struct
 * @ptr: stores address of the pointer that will point to the output
 *	buffer where the function will store the read line
 * @length: stores  the length of the line that was read, including
 *	the null terminator
 *
 * Return: total_bytes
 */
int insert_line_search(sh_args *content, char **ptr, size_t *length)
{
	static char input_buf[READ_BUF_SIZE];
	static size_t buf_pos, buf_len;
	size_t line_len;
	ssize_t bytes_read = 0, total_bytes = 0;
	char *input_pos = NULL, *new_output_str = NULL, *line_end;

	input_pos = *ptr;
	if (input_pos && length)
		total_bytes = *length;
	if (buf_pos == buf_len)
		buf_pos = buf_len = 0;

	bytes_read =  buffer_insert(content, input_buf, &buf_len);
	if (bytes_read == -1 || (bytes_read == 0 && buf_len == 0))
		return (-1);

	line_end = to_find_char(input_buf + buf_pos, '\n');
	line_len = line_end ? 1 + (unsigned int)(line_end - input_buf) : buf_len;
	new_output_str = to_allocate_mem(input_pos, total_bytes, total_bytes ?
			total_bytes + line_len : line_len + 1);
	if (!new_output_str) /* MALLOC FAILURE! */
		return (input_pos ? free(input_pos), -1 : -1);

	if (total_bytes)
		addMore_str(new_output_str, input_buf + buf_pos, line_len - buf_pos);
	else
		string_to_copy(new_output_str, input_buf + buf_pos, line_len - buf_pos + 1);

	total_bytes += line_len - buf_pos;
	buf_pos = line_len;
	input_pos = new_output_str;

	if (length)
		*length = total_bytes;
	*ptr = input_pos;
	return (total_bytes);
}


/**
 * input_Ctrl - handle signal calls when user presses Ctrl+C
 * @unused_signal_num:  indicates the signal number that triggered
 *	the signal handler
 *
 * Return: nil
 */
void input_Ctrl(__attribute__((unused))int unused_signal_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
