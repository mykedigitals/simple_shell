#include "shell.h"


/**
 * collect_filepath - gets the path to the record file
 * @element: struct parameter
 *
 * Return: string construct to the path of the record file
 */

char *collect_filepath(shell_args *element)
{
	char *render, *abode;
	abode = getsurr_clone(element, "HOME=");

	if (!abode)
		return (NULL);

	render = malloc(sizeof(char) * (string_lent(abode)
				+ string_lent(RECO_DOCX) + 2));
	if (!render)
		return (NULL);
	render[0] = 0;
	clone_str(render, abode);
	string_add(render, "/");
	string_add(render, RECO_DOCX);
	return (render);
}

/**
 * create_shel_record - This create a file to keep record of shell program, 
 * or appends an existing file
 * @element: structure parameter
 *
 * Return: 1 (success), -1 (error)
 */

int create_shel_record(shell_args *element)
{
        ssize_t ent_int;
        char *record_file = collect_filepath(element);
        l_list *node = NULL;

        if (!record_file)
                return (-1);

        ent_int = open(record_file, O_CREAT | O_TRUNC | O_RDWR, 0644);
        free(record_file);
        if (ent_int == -1)
                return (-1);
        for (node = element->record; node; node = node->link)
        {
                create_strng_find(node->str, ent_int);
                write_chk_to_fd('\n', ent_int);
        }
        write_chk_to_fd(BUFF_FLUSHH, ent_int);
        close(ent_int);
        return (1);
}
