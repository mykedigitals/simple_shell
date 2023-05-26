#include "shell.h"


/**
 * write_chk_to_fd - This wlll write character to a file
 * descriptor ent_int in a rendered manner
 * @chk: character to be  printed
 * @ent_int: filedescriptor being writen  to
 *
 * Return: 1 (success), -1 (error)
 */

int write_chk_to_fd(int ent_int, char chk)
{
	static int sort;
	static char render[WRITE_BUF_SIZE];

	if (chk == BUF_FLUSH || sort >= WRITE_BUF_SIZE)
	{
		write(ent_int, render, sort);
		sort = 0;
	}
	if (chk != BUF_FLUSH)
		render[sort++] = chk;
	return (1);
}
