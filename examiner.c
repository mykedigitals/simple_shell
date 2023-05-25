#include "shell.h"


/**
 * search_path - finds the full path of a command within a
 *	list of directories provided in the dirctry_list
 * @element: struct element
 * @dirctry_list: string path
 * @command: command
 *
 * Return: command's full path | NULL
 */
char *search_path(shell_args *element, char *dirctry_list, char *command)
{
	int path_index = 0, prev_index = 0;
	char *full_path;

	if (!dirctry_list)
		return (NULL);
	if ((span_of_str(command) > 2) && locate_word_begin(command, "./"))
	{
		if (is_exec(element, command))
			return (command);
	}
	while (1)
	{
		if (!dirctry_list[path_index] || dirctry_list[path_index] == ':')
		{
			full_path = char_clone_nolimiter(dirctry_list,
					prev_index, path_index);
			if (!*full_path)
				string_add(full_path, command);
			else
			{
				string_add(full_path, "/");
				string_add(full_path, command);
			}
			if (is_exec(element, full_path))
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
 * is_exec - checks if a file is an executable command or not
 * @element: struct element
 * @doc_nav: file path
 *
 * Return: 1 (true), 0 (otherwise)
 */
int is_exec(shell_args *element, char *doc_nav)
{
	struct stat file_info;

	(void)element;
	if (!doc_nav || stat(doc_nav, &file_info))
		return (0);

	if (file_info.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}


/**
 * char_clone_nolimiter - duplicates chars while removing any
 *	delimiters
 * @pathstr: string path
 * @found_idx: start index
 * @stop_index: stop index
 *
 * Return: pointer to new render
 */
char *char_clone_nolimiter(char *pathstr, int found_idx,
		int stop_index)
{
	static char render[1024];
	int origin_idx = 0, end_idx = 0;

	for (end_idx = 0, origin_idx = found_idx;
			origin_idx < stop_index; origin_idx++)
		if (pathstr[origin_idx] != ':')
			render[end_idx++] = pathstr[origin_idx];
	render[end_idx] = 0;
	return (render);
}
