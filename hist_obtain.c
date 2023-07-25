#include "shell.h"

/**
 * hist_process - this function scan through cmd history
 * from a file and add it to a history buffer
 * @content: struct parameter
 *
 * Return: histcount (success), else 0
 */
int hist_process(sh_args *content)
{
	int index, last_newline = 0, linecount = 0;
	ssize_t fil_des, read_len, fil_size = 0;
	struct stat file_stats;
	char *buffer = NULL, *history_file = obtain_histFile_path(content);

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
			append_inRecord(content, buffer + last_newline, linecount++);
			last_newline = index + 1;
		}
	if (last_newline != index)
		append_inRecord(content, buffer + last_newline, linecount++);
	free(buffer);
	content->histcount = linecount;
	while (content->histcount-- >= HIST_MAX)
		rm_node_idx(&(content->history), 0);
	refresh_history_nodeNumber(content);
	return (content->histcount);
}


/**
 * put_sh_record - generates a file to save
 * history of shell program, or attach presently
 * available file
 * @content: value of struct
 *
 * Return: 1 (success), else -1
 */
int put_sh_record(sh_args *content)
{
	ssize_t fil_des;
	char *history_file = obtain_histFile_path(content);
	l_list *node = NULL;

	if (!history_file)
		return (-1);

	fil_des = open(history_file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(history_file);
	if (fil_des == -1)
		return (-1);
	for (node = content->history; node; node = node->link)
	{
		stringwrite_toFd(node->str, fil_des);
		charWrite_toFd('\n', fil_des);
	}
	charWrite_toFd(BUF_FLUSH, fil_des);
	close(fil_des);
	return (1);
}


/**
 * append_inRecord - builds a history list by adding
 * a new node at the end of the linked list pointed to by
 *	content->history
 * @content: struct parameter
 * @buffer: buffer
 * @linecount: history linecount, histcount
 *
 * Return: 0
 */
int append_inRecord(sh_args *content, char *buffer, int linecount)
{
	l_list *node = NULL;

	if (content->history)
		node = content->history;
	endOf_node(&node, buffer, linecount);

	if (!content->history)
		content->history = node;
	return (0);
}


/**
 * obtain_histFile_path - This sentence means finding the
 * location of the file where the history is stored.
 * @content: value of struct
 *
 * Return: string struct to the location where the history file
 * is located
 */
char *obtain_histFile_path(sh_args *content)
{
	char *buffer, *home;

	home = getduplicate_surr(content, "HOME=");
	if (!home)
		return (NULL);
	buffer = malloc(sizeof(char) * (string_lent(home)
		+ string_lent(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	copy_string(buffer, home);
	extend_string(buffer, "/");
	extend_string(buffer, HIST_FILE);
	return (buffer);
}


/**
 * refresh_history_nodeNumber - This function numbers
 * the nodes in a linked-list of hist items again
 * @content: value of struct
 *
 * Return: all nodes completely in the linked list
 * this means the new highest no assigned to a node, plus one
 */
int refresh_history_nodeNumber(sh_args *content)
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
