#include "shell.h"


/**
 * locate_word_begin - the string find_in_string starts with the
 *	anotherstring
 * @find_in_string: the string to be searched
 * @anotherstring: anotherstring being searched
 *
 * Return: location of next char of find_in_string or NULL
 */
char *locate_word_begin(const char *find_in_string, const char *anotherstring)
{
	while (*anotherstring)
		if (*anotherstring++ != *find_in_string++)
			return (NULL);
	return ((char *)find_in_string);
}


/**
 * string_lent - gets length of a string
 * @word_string: string length to be checked
 *
 * Return: string length
 */
int string_lent(char *word_string)
{
	int index_word = 0;

	if (!word_string)
		return (0);

	while (*word_string++)
		index_word++;
	return (index_word);
}


/**
 * string_add - concatenates strings ending_of_str and begin_string
 * @ending_of_str: the destination buffer
 * @begin_string: the source buffer
 *
 * Return: concatenates string
 */
char *string_add(char *ending_of_str, char *begin_string)
{
	char *effect = ending_of_str;

	while (*ending_of_str)
		ending_of_str++;
	while (*begin_string)
		*ending_of_str++ = *begin_string++;
	*ending_of_str = *begin_string;
	return (effect);
}


/**
 * weigh_strs - weigh two strings, begining_strng and following_strng,
 * and return an whole number value indicating their relative order
 * @begining_strng: first string
 * @following_strng: second string
 *
 * Return: return 0 (if begining_strng == following_strng), negative 
 * (begining_strng < following_strng), positive (begining_strng > following_strng)
 */

int weigh_strs(char *begining_strng, char *following_strng)
{
	while (*begining_strng && *following_strng)
	{
		if (*begining_strng != *following_strng)
			return (*begining_strng - *following_strng);
		begining_strng++;
		following_strng++;
	}
	if (*begining_strng == *following_strng)
		return (0);
	else
		return (*begining_strng < *following_strng ? -1 : 1);
}
