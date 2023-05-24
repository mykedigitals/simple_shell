#include "shell.h"


/**
 * _putchar - writes a char to stdout
 * @point_char: character to be printed
 *
 * Return: 1 (success), -1 (error)
 */
int _putchar(char point_char)
{
	static int index_word;
	static char buf[WRITE_BUF_SIZE];

	if (point_char == BUFF_FLUSHH || index_word >= WRITE_BUF_SIZE)
	{
		write(1, buf, index_word);
		index_word = 0;
	}
	if (point_char != BUFF_FLUSHH)
		buf[index_word++] = point_char;
	return (1);
}


/**
 *_puts - handles printing string from input
 *@print_string: string being printed
 *
 * Return: nil
 */
void _puts(char *print_string)
{
	int index_word = 0;

	if (!print_string)
		return;
	while (print_string[index_word] != '\0')
	{
		_putchar(print_string[index_word]);
		index_word++;
	}
}


/**
 * clone_str - copies string from begin_string to string_dest
 * @string_dest: string destination
 * @begin_string: string source
 *
 * Return: pointer to destination
 */
char *clone_str(char *string_dest, char *begin_string)
{
	int index_word = 0;

	if (string_dest == begin_string || begin_string == 0)
		return (string_dest);
	while (begin_string[index_word])
	{
		string_dest[index_word] = begin_string[index_word];
		index_word++;
	}
	string_dest[index_word] = 0;
	return (string_dest);
}


/**
 * double_str - handles string duplication
 * @word_txt: string being duplicated
 *
 * Return: pointer to the duplicated string
 */
char *double_str(const char *word_txt)
{
	int xy = 0;
	char *effect;

	if (word_txt == NULL)
		return (NULL);
	while (*word_txt++)
		xy++;
	effect = malloc(sizeof(char) * (xy + 1));
	if (!effect)
		return (NULL);
	for (xy++; xy--;)
		effect[xy] = *--word_txt;
	return (effect);
}
