#include "shell.h"

/**
 * multi_free - frees memory allocated to a string of strings
 * @str_ptr: pointer to a string of strings
 */
void multi_free(char **str_ptr)
{
	char **my_strings;

	my_strings = str_ptr;

	if (str_ptr == NULL)
	{
		return;
	}

	while (*str_ptr != NULL)
	{
		free(*str_ptr++);
	}

	free(my_strings);
}


/**
 * free_n_NULL - free the memory pointed to by
 * @ptr: pointer address being freed
 *
 * Return: 1 (freed), 0 (otherwise)
 */
int free_n_NULL(void **ptr)
{
	int is_freed = 1;

	/* Check if pointer is not NULL and points to a valid memory location */
	if (*ptr != NULL && ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;

		/* Set flag to indicate that memory has been freed */
		return (is_freed);
	}
	return (0);
}
