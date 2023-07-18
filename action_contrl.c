#include "shell.h"


/**
 * locate_execute - in the list of dirctry_list this
 * command locates the path of the command with a
 * list of dirs
 *
 * @content: the content of struct
 * @dirctry_list: this reps the path to a string
 * @command: command
 *
 * Return: cmd full path or NULL
 */
char *locate_execute(sh_args *content, char *dirctry_list, char *command)
{
	int path_index = 0, prev_index = 0;
	char *full_path;

	if (!dirctry_list)
		return (NULL);
	if ((string_lent(command) > 2) && on_startFind_sub(command, "./"))
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
				extend_string(full_path, command);
			else
			{
				extend_string(full_path, "/");
				extend_string(full_path, command);
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
 * for_doc_exec - this function if a particular fine
 * contains an executable command
 *
 * @content: content of struct
 * @file_path: path to all files
 *
 * Return: 1 (true), else 0
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
 * clone_no_delim - this function adds another character
 * at the same time removing any delimiters
 *
 * @pathstr: path to string in a file
 * @start_index: index of the beginning
 * @stop_index: index signifying the ending
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
