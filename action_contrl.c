#include "shell.h"


/**
 * locate_execute - finds the full path of a command within a
 *	list of directories provided in the dirctry_list
 * @content: struct content
 * @dirctry_list: string path
 * @command: command
 *
 * Return: command's full path | NULL
 */
char *locate_execute(sh_args *content, char *dirctry_list, char *command)
{
	int path_index = 0, prev_index = 0;
	char *full_path;

	if (!dirctry_list)
		return (NULL);
	if ((len_of_str(command) > 2) && find_substr_at_start(command, "./"))
	{
		if (for_doc_exec(content, command))
			return (command);
	}
	while (1)
	{
		if (!dirctry_list[path_index] || dirctry_list[path_index] == ':')
		{
			full_path = clone_no_delim(dirctry_list,
					prev_index, path_index);
			if (!*full_path)
				concat_str(full_path, command);
			else
			{
				concat_str(full_path, "/");
				concat_str(full_path, command);
			}
			if (for_doc_exec(content, full_path))
				return (full_path);
			if (!dirctry_list[path_index])
				break;
			prev_index = path_index;
		}
		path_index++;
	}
	return (NULL);
}


/**
 * for_doc_exec - checks if a file is an executable command or not
 * @content: struct content
 * @file_path: file path
 *
 * Return: 1 (true), 0 (otherwise)
 */
int for_doc_exec(sh_args *content, char *file_path)
{
	struct stat file_info;

	(void)content;
	if (!file_path || stat(file_path, &file_info))
		return (0);

	if (file_info.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}


/**
 * clone_no_delim - duplicates chars while removing any
 *	delimiters
 * @pathstr: string path
 * @start_index: start index
 * @stop_index: stop index
 *
 * Return: pointer to new buffer
 */
char *clone_no_delim(char *pathstr, int start_index,
		int stop_index)
{
	static char buffer[1024];
	int source_index = 0, dest_index = 0;

	for (dest_index = 0, source_index = start_index;
			source_index < stop_index; source_index++)
		if (pathstr[source_index] != ':')
			buffer[dest_index++] = pathstr[source_index];
	buffer[dest_index] = 0;
	return (buffer);
}
