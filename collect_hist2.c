#include "shell.h"


/**
 * get_hist_file_path - gets the path to the history file
 * @content: struct parameter
 *
 * Return: string construct to the path of the history file
 */

char *get_hist_file_path(sh_args *content)
{
	char *buffer, *home;
	home = getenv_clone(content, "HOME=");

	if (!home)
		return (NULL);

	buffer = malloc(sizeof(char) * (len_of_str(home)
				+ len_of_str(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	str_cpy(buffer, home);
	concat_str(buffer, "/");
	concat_str(buffer, HIST_FILE);
	return (buffer);
}

/**
 * write_shel_histry - creates a file to store
 * history of shell program, or appends an existing file
 * @content: struct parameter
 *
 * Return: 1 (success), -1 (error)
 */

int write_shel_histry(sh_args *content)
{
        ssize_t fil_des;
        char *history_file = get_hist_file_path(content);
        l_list *node = NULL;

        if (!history_file)
                return (-1);

        fil_des = open(history_file, O_CREAT | O_TRUNC | O_RDWR, 0644);
        free(history_file);
        if (fil_des == -1)
                return (-1);
        for (node = content->history; node; node = node->link)
        {
                write_string_to_fd(node->str, fil_des);
                write_car_to_fd('\n', fil_des);
        }
        write_car_to_fd(BUF_FLUSH, fil_des);
        close(fil_des);
        return (1);
}
