#include "shell.h"


/**
 * prt_mes_eror - This function will write our error
 * msg to the stderr output
 * @element: structure parameter
 * @strng_of_err: write info on source of the error
 *
 * Return: 0
 */
void prt_mes_eror(shell_args *element, char *strng_of_err)
{
	/* This will write the filename to buffer */
	create_thread_in_render(element->fname);
	/* This will write colon and space to buffer */
	create_thread_in_render(": ");
	/* This will write line num to buffer */
	prt_dcm_int(element->space_ct, STDERR_FILENO);
	create_thread_in_render(": ");
	/* This will write cmd name buffer */
	create_thread_in_render(element->argv[0]);
	create_thread_in_render(": ");
	/* This write error msg to buffer */
	create_thread_in_render(strng_of_err);
}
