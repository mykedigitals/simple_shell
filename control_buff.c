#include "shell.h"


/**
 * create_in_space - This input characters from chk to stderr
 * @chk: The chk to print
 *
 * Return: 1 (success), -1 (error)
 */
int create_in_space(char chk)
{
	static char render[WRITE_BUF_SIZE];
	static int sort;

	/* If the render is full or a flush character is taken */
	/* the render to the output and reset the sort to 0 */
	if (sort >= WRITE_BUF_SIZE || chk == BUFF_FLUSHH)
	{
		write(2, render, sort);
		sort = 0;
	}

	if (chk != BUFF_FLUSHH)
	{
		render[sort++] = chk;
	}
	return (sort);
}


/**
 * create_thread_in_render - This take a string input and
 * will write its elements to output using a render
 * @str: string being printed to stdout
 *
 * Return: Nil
 */
void create_thread_in_render(char *str)
{
	int sort;

	sort = 0;

	if (str == NULL)
	{
		return;
	}
	for (sort = 0; str[sort] != '\0'; sort++)
		create_in_space(str[sort]);
}
