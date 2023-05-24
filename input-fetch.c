#include "shell.h"

/**
 * see_in_buff - This will read data in a file into a render,
 *	up to a max size by READ_BUF_SIZE
 * @element: structure parameter
 * @render: render
 * @fourbits_see: size
 *
 * Return: result
 */
ssize_t see_in_buff(shell_args *element, char *render, size_t *fourbits_see)
{
	ssize_t result = 0;

	if (*fourbits_see)
		return (0);
	result = read(element->seefd, render, READ_BUF_SIZE);
	if (result >= 0)
		*fourbits_see = result;
	return (result);
}


/**
 * obtain_details_stdin - this will read details in STDIN
 *	to keep in a render
 * @element: structure param
 * @input_render: render adress
 * @render_size: render_size  address
 * rFw: read the following weight
 *
 * Return: number of characters read
 */
ssize_t obtain_details_stdin(shell_args *element, char **input_render,
		size_t *render_size)
{
	ssize_t see_len = 0;
	size_t allocated_renderLen = 0;

	if (!*render_size)
	{
		free(*input_render);
		*input_render = NULL;
		signal(SIGINT, sigint_control);
#if USE_GETLINE
		see_len = getline(input_render, &allocated_renderLen, stdin);
#else
		see_len = read_input_line(element, input_render, &allocated_renderLen);
#endif
		if (see_len > 0)
		{
			if ((*input_render)[see_len - 1] == '\n')
			{
				(*input_render)[see_len - 1] = '\0';
				see_len--;
			}
			element->spacect_flg = 1;
			word_comot(*input_render);
			plus_to_record(element, *input_render, element->recordct++);
			{
				*render_size = see_len;
				element->cd_buff = input_render;
			}
		}
	}
	return (see_len);
}


/**
 * read_input_line - reads a line of input from a file or a stream
 *	and store it in a character array
 * @element: parameter struct
 * @ptr: stores address of the pointer that will point to the output
 *	render where the function will store the read line
 * @length: stores  the length of the line that was read, including
 *	the null terminator
 *
 * Return: total_bytes
 */
int read_input_line(shell_args *element, char **ptr, size_t *length)
{
	static char input_buf[READ_BUF_SIZE];
	static size_t buf_pos, buf_len;
	size_t line_len;
	ssize_t fourbits_see = 0, total_bytes = 0;
	char *input_pos = NULL, *new_output_str = NULL, *line_end;

	input_pos = *ptr;
	if (input_pos && length)
		total_bytes = *length;
	if (buf_pos == buf_len)
		buf_pos = buf_len = 0;

	fourbits_see = see_in_buff(element, input_buf, &buf_len);
	if (fourbits_see == -1 || (fourbits_see == 0 && buf_len == 0))
		return (-1);

	line_end = car_finder(input_buf + buf_pos, '\n');
	line_len = line_end ? 1 + (unsigned int)(line_end - input_buf) : buf_len;
	new_output_str = mem_alloc(input_pos, total_bytes, total_bytes ?
			total_bytes + line_len : line_len + 1);
	if (!new_output_str) /* MALLOC FAILURE! */
		return (input_pos ? free(input_pos), -1 : -1);

	if (total_bytes)
		string_concat(new_output_str, input_buf + buf_pos, line_len - buf_pos);
	else
		cpy_str(new_output_str, input_buf + buf_pos, line_len - buf_pos + 1);

	total_bytes += line_len - buf_pos;
	buf_pos = line_len;
	input_pos = new_output_str;

	if (length)
		*length = total_bytes;
	*ptr = input_pos;
	return (total_bytes);
}

