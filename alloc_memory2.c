#include "shell.h"

/**
 *  cpy_memset - copies "memset()" function as
 *  it fill up memory with a steady byte
 *  @ptr: points to the memory space to be filled
 *  @val: the val to be put in the mem spaxe
 *  @num: the no of bytes to be set in the memory block
 *
 *  Return: pointer to the memory space
 */

char *cpy_memset(char *ptr, char val, unsigned int num)
{
	unsigned int h;

	h = 0;
	/* Set each byte of the memory block to the given val */
	while  (num > h)
	{
		ptr[h] = val;
		h++;
	}
	return (ptr);
}

/**
 * alloc_mem - changes a previously allocated memory block
 * @old_memsize: The byte size of old block
 * @present_memsize: The byte size of present block
 * @ptr_one: pointer to old (mallocated) block
 * Description: 1 and decrements old_size on each
 * iteration until it reaches 0. On each iteration, it copies
 * the byte at index "old_size" in the old memory block
 * to the same index in the new memory block.
 *
 * Return: pointer to newly allocated memory block (p)
 */
void *alloc_mem(void *ptr_one, unsigned int
		old_memsize, unsigned int present_memsize)
{
	char *new_ptr;

	if (ptr_one == NULL)
	{
		return (malloc(present_memsize));
	}
	/* deallocates "new size" if memory block is zero */
	if (!present_memsize)
	{
		return (free(ptr_one), NULL);
	}
	/* if the new size of the memory block is equal to the old size. */
	/* If it is, then there's no need to resize the memory block */
	if (old_memsize == present_memsize)
	{
		return (ptr_one);
	}
	new_ptr = malloc(present_memsize);
	if (new_ptr == NULL)
	{
		return (NULL);
	}
	old_memsize = old_memsize < present_memsize ? old_memsize : present_memsize;

	while (old_memsize--)
		new_ptr[old_memsize] = ((char *)ptr_one)[old_memsize];
	free(ptr_one);

	return (new_ptr);
}
