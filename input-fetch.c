#include "shell.h"

/**
 * see_in_buff - This will read data in a file into a render,
 *	up to a max size by SEEN_BUF_SIZE
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
	result = read(element->seefd, render, SEEN_BUF_SIZE);
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
		signal(SIGINT, signit_control);
#if USE_GETLINE
		see_len = receiveline(input_render, &allocated_renderLen, stdin);
#else
		see_len = see_line_details(element, input_render, &allocated_renderLen);
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
 * see_line_details - This will read line of input in a file and 
 * store it in array
 * @element: parameter struct
 * @ptr: This will store address of pointer that point to result
 *	render where the function will store the seen line
 * @lent: stores  the lent of the line that was read, including
 *	the null terminator
 *
 * Return: all_fourbitss
 */
int see_line_details(shell_args *element, char **ptr, size_t *lent)
{
	static char input_buf[SEEN_BUF_SIZE];
	static size_t buf_area, buf_len;
	size_t line_len;
	ssize_t fourbits_see = 0, all_fourbitss = 0;
	char *details_pos = NULL, *result_str = NULL, *line_end;

	details_pos = *ptr;
	if (details_pos && lent)
		all_fourbitss = *lent;
	if (buf_area == buf_len)
		buf_area = buf_len = 0;

	fourbits_see = see_in_buff(element, input_buf, &buf_len);
	if (fourbits_see == -1 || (fourbits_see == 0 && buf_len == 0))
		return (-1);

	line_end = locate_char(input_buf + buf_area, '\n');
	line_len = line_end ? 1 + (unsigned int)(line_end - input_buf) : buf_len;
	result_str = alloc_mem(details_pos, all_fourbitss, all_fourbitss ?
			all_fourbitss + line_len : line_len + 1);
	if (!result_str) /* MALLOC FAIL! */
		return (details_pos ? free(details_pos), -1 : -1);

	if (all_fourbitss)
		thread_rearr(result_str, input_buf + buf_area, line_len - buf_area);
	else
		string_clone(result_str, input_buf + buf_area, line_len - buf_area + 1);

	all_fourbitss += line_len - buf_area;
	buf_area = line_len;
	details_pos = result_str;

	if (lent)
		*lent = all_fourbitss;
	*ptr = details_pos;
	return (all_fourbitss);
}

