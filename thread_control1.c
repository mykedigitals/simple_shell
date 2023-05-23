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
 * string_sku - weigh two strings, 1st_string and 2nd_string,
 * and return an whole number value indicating their relative order
 * @1st_string: first string
 * @2nd_string: second string
 *
 * Return: return 0 (if 1st_string == 2nd_string), negative 
 * (1st_string < 2nd_string), positive (1st_string > 2nd_string)
 */

int string_sku(char *1st_string, char *2nd_string)
{
	while (*1st_string && *2nd_string)
	{
		if (*1st_string != *2nd_string)
			return (*1st_string - *2nd_string);
		1st_string++;
		2nd_string++;
	}
	if (*1st_string == *2nd_string)
		return (0);
	else
		return (*1st_string < *2nd_string ? -1 : 1);
}
