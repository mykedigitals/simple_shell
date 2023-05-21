#include "shell.h"

/**
 * load_history - reads command history
 * from a file and add it to a history buffer
 * @content: struct parameter
 *
 * Return: histcount (success), 0 (error)
 */
int load_history(sh_args *content)
{
	int index, last_newline = 0, linecount = 0;
	ssize_t fil_des, read_len, fil_size = 0;
	struct stat file_stats;
	char *buffer = NULL, *history_file = get_hist_file_path(content);

	if (!history_file)
		return (0);

	fil_des = open(history_file, O_RDONLY);
	free(history_file);
	if (fil_des == -1)
		return (0);
	if (!fstat(fil_des, &file_stats))
		fil_size = file_stats.st_size;
	if (fil_size < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fil_size + 1));
	if (!buffer)
		return (0);
	read_len = read(fil_des, buffer, fil_size);
	buffer[fil_size] = 0;
	if (read_len <= 0)
		return (free(buffer), 0);
	close(fil_des);
	for (index = 0; index < fil_size; index++)
		if (buffer[index] == '\n')
		{
			buffer[index] = 0;
			add_to_history(content, buffer + last_newline, linecount++);
			last_newline = index + 1;
		}
	if (last_newline != index)
		add_to_history(content, buffer + last_newline, linecount++);
	free(buffer);
	content->histcount = linecount;
	while (content->histcount-- >= HIST_MAX)
		delete_node_index(&(content->history), 0);
	update_hist_node_numbrs(content);
	return (content->histcount);
}


/**
 * add_to_history - builds a history list by adding
 * a new node at the end of the linked list pointed to by
 *	content->history
 * @content: struct parameter
 * @buffer: buffer
 * @linecount: history linecount, histcount
 *
 * Return: 0
 */
int add_to_history(sh_args *content, char *buffer, int linecount)
{
	l_list *node = NULL;

	if (content->history)
		node = content->history;
	new_end_node(&node, buffer, linecount);

	if (!content->history)
		content->history = node;
	return (0);
}



/**
 * update_hist_node_numbrs - renumbers
 * the nodes in a linked list of history items
 * @content: struct parameter
 *
 * Return: total number of nodes in the linked list
 * (i.e. the new highest number assigned to a node, plus one)
 */
int update_hist_node_numbrs(sh_args *content)
{
	l_list *node = content->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->link;
	}
	return (content->histcount = i);
}
