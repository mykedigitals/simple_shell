#include "shell.h"

/**
 * load_record - reads command history
 * from a file and add it to a record render
 * @element: struct parameter
 *
 * Return: recordct (success), 0 (error)
 */

int load_record(shell_args *element)
{
	int work_idx, end_lne = 0, linecount = 0;
	ssize_t hom_doc, rd_lent, fil_size = 0;
	struct stat file_stats;
	char *render = NULL, *record_file = collect_filepath(element);

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
	render = malloc(sizeof(char) * (fil_size + 1));
	if (!render)
		return (0);
	rd_lent = read(hom_doc, render, fil_size);
	render[fil_size] = 0;
	if (rd_lent <= 0)
		return (free(render), 0);
	close(hom_doc);
	for (work_idx = 0; work_idx < fil_size; work_idx++)
		if (render[work_idx] == '\n')
		{
			render[work_idx] = 0;
			plus_to_record(element, render + end_lne, linecount++);
			end_lne = work_idx + 1;
		}
	if (end_lne != work_idx)
		plus_to_record(element, render + end_lne, linecount++);
	free(render);
	element->recordct = linecount;
	while (element->recordct-- >= HIST_MAX)
		rem_node_sort(&(element->record), 0);
	edit_nodenumber(element);
	return (element->recordct);
}


/**
 * plus_to_record - builds a history list by adding
 * a new node at the end of the linked list pointed to by
 *	element->record
 * @element: struct parameter
 * @render: render
 * @linecount: record linecount, recordct
 *
 * Return: 0
 */
int plus_to_record(shell_args *element, char *render, int linecount)
{
	l_list *node = NULL;

	if (element->record)
		node = element->record;
	updated_tail_node(&node, render, linecount);

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
