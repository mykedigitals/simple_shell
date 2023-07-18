#include "shell.h"


/**
 * on_startFind_sub - the string str_to_search starts with the
 *	substring substring
 * @str_to_search: searched string
 * @substring: substring being searched
 *
 * Return: address of next char of str_to_search or NULL
 */
char *on_startFind_sub(const char *str_to_search, const char *substring)
{
	while (*substring)
		if (*substring++ != *str_to_search++)
			return (NULL);
	return ((char *)str_to_search);
}


/**
 * string_lent - gets length of a string
 * @str: string length to be checked
 *
 * Return: string length
 */
int string_lent(char *str)
{
	int idx = 0;

	if (!str)
		return (0);

	while (*str++)
		idx++;
	return (idx);
}


/**
 * extend_string - concatenates strings str_dest and str_src
 * @str_dest: the destination buffer
 * @str_src: the source buffer
 *
 * Return: concatenates string
 */
char *extend_string(char *str_dest, char *str_src)
{
	char *result = str_dest;

	while (*str_dest)
		str_dest++;
	while (*str_src)
		*str_dest++ = *str_src++;
	*str_dest = *str_src;
	return (result);
}


/**
 * strings_weigh - compare two strings, str1 and str2, and return an
 *	integer value indicating their relative order
 * @str1: first string
 * @str2: second string
 *
 * Return: 0 (if str1 == str2), negative (str1 < str2), positive (str1 > str2)
 */
int strings_weigh(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}
