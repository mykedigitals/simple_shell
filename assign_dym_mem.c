#include "shell.h"


/**
 * to_allocate_mem - this function resizes the former alloc memory block
 * @prev_mem_size: size of former block in byte
 * @new_mem_size: new block size in byte
 * @first_ptr: this points to the former malloc block
 * Desc: First of, it calc the minimum size between
 * the former and new block size then store them in the former size
 * This is cause we only copy the min num of bytes required to
 * contain the data in the mem block.
 * Here after it cpy over the data from the formerly alloc
 * mem block to the new mem block. This loops keeps reiterating
 *
 * Return: this returns the pointer pointing to the newly alloc mem block(p)
 */
void *to_allocate_mem(void *first_ptr, unsigned int
prev_mem_size, unsigned int new_mem_size)
{
	char *new_ptr;

	if (!first_ptr)
		return (malloc(new_mem_size));

	/* deallocates "new size" if memory block is zero */
	if (!new_mem_size)
		return (free(first_ptr), NULL);

	/* if the new size of the memory block is equal to the old size. */
	/* If it is, then there's no need to resize the memory block */
	if (new_mem_size == prev_mem_size)
		return (first_ptr);

	new_ptr = malloc(new_mem_size);

	if (!new_ptr)
		return (NULL);

	prev_mem_size = prev_mem_size < new_mem_size ? prev_mem_size : new_mem_size;

	while (prev_mem_size--)
		new_ptr[prev_mem_size] = ((char *)first_ptr)[prev_mem_size];
	free(first_ptr);
	return (new_ptr);
}


/**
 * cpy_setof_mem - this function imitates "memset()" function
 * as it fills mem with a unchanging byte
 * @ptr: this is a pointer to mem that is to be filled
 * @value: values to be filled in the mem block
 * @num: the number of bytes to be set in the memory block
 *
 * Return: pointer to the memory area
 */
char *cpy_setof_mem(char *ptr, char value, unsigned int num)
{
	unsigned int x;

	for (x = 0; x < num; x++)
		ptr[x] = value;
	return (ptr);
}

/**
 * free_alot - this function frees mem allocd to a string of strings
 * @str_ptr: pointer to a string of strings
 */

void free_alot(char **str_ptr)
{
	char **my_strings = str_ptr;

	if (!str_ptr)
		return;
	while (*str_ptr)
		free(*str_ptr++);
	free(my_strings);
}


/**
 * to_free_nothing - this function free the mem pointed to by
 * @p: pointer address that is to be freed
 *
 * Return: 1 (freed), else 0
 */
int to_free_nothing(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
