#include "shell.h"

/**
 * double_empty - empty memory given to a string of string
 * @ptr_strng: pointer to a string of strings
 */
void double_empty(char **ptr_strng)
{
	char **our_stng;

	our_stng = ptr_strng;

	if (ptr_strng == NULL)
	{
		return;
	}

	while (*ptr_strng != NULL)
	{
		free(*ptr_strng++);
	}

	free(our_stng);
}


/**
 * empty_n_NULL - This is empty the memory pointed
 * @ptr: This is the pointer address being emptied
 *
 * Return: 1 (emptied), 0 (if not)
 */
int empty_n_NULL(void **ptr)
{
	int is_emptied = 1;

	/* See if pointer isn't NULL and point to a true memory place */
	if (*ptr != NULL && ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;

		/* put flag to show that memory is empty */
		return (is_emptied);
	}
	return (0);
}
