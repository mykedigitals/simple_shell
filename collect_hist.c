#include "shell.h"

/**
 * load_record - reads command history
 * from a file and add it to a record buffer
 * @element: struct parameter
 *
 * Return: recordct (success), 0 (error)
 */

int load_record(shell_args *element)
{
	int work_idx, end_lne = 0, linecount = 0;
	ssize_t hom_doc, rd_lent, fil_size = 0;
	struct stat file_stats;
	char *buffer = NULL, *record_file = collect_filepath(element);

	if (!record_file)
		return (0);

	hom_doc = open(record_file, O_RDONLY);
	free(record_file);
	if (hom_doc == -1)
		return (0);
	if (!fstat(hom_doc, &file_stats))
		fil_size = file_stats.st_size;
	if (fil_size < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fil_size + 1));
	if (!buffer)
		return (0);
	rd_lent = read(hom_doc, buffer, fil_size);
	buffer[fil_size] = 0;
	if (rd_lent <= 0)
		return (free(buffer), 0);
	close(hom_doc);
	for (work_idx = 0; work_idx < fil_size; work_idx++)
		if (buffer[work_idx] == '\n')
		{
			buffer[work_idx] = 0;
			plus_to_record(element, buffer + end_lne, linecount++);
			end_lne = work_idx + 1;
		}
	if (end_lne != work_idx)
		plus_to_record(element, buffer + end_lne, linecount++);
	free(buffer);
	element->recordct = linecount;
	while (element->recordct-- >= RECO_MAX)
		rem_node_sort(&(element->record), 0);
	edit_nodenumber(element);
	return (element->recordct);
}


/**
 * plus_to_record - builds a history list by adding
 * a new node at the end of the linked list pointed to by
 *	element->record
 * @element: struct parameter
 * @buffer: buffer
 * @linecount: record linecount, recordct
 *
 * Return: 0
 */
int plus_to_record(shell_args *element, char *buffer, int linecount)
{
	l_list *node = NULL;

	if (element->record)
		node = element->record;
	updated_tail_node(&node, buffer, linecount);

	if (!element->record)
		element->record = node;
	return (0);
}



/**
 * edit_nodenumber - renumbers
 * the nodes in a linked list of record items
 * @element: struct parameter
 *
 * Return: total number of nodes in the linked list
 * (i.e. the new highest number assigned to a node, plus one)
 */
int edit_nodenumber(shell_args *element)
{
	l_list *node = element->record;
	int yep = 0;

	while (node)
	{
		node->num = yep++;
		node = node->link;
	}
	return (element->recordct = yep);
}
