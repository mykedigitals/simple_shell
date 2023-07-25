#include "shell.h"


/**
 * on_startFind_sub - this is the string str_to_search starts with the
 *	substring x2
 * @str_to_search: the is searched string
 * @substring: substring to be searched
 *
 * Return: this returns address of the next char of str_to_search or NULL
 */
char *on_startFind_sub(const char *str_to_search, const char *substring)
{
	while (*substring)
		if (*substring++ != *str_to_search++)
			return (NULL);
	return ((char *)str_to_search);
}


/**
 * string_lent - this will get length of string
 * @str: this is the string length to be checked
 *
 * Return: the string length
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
 * extend_string - this will concatenate the strings str_dest and str_src
 * @str_dest: this is the destination buffer
 * @str_src: this is the source buffer
 *
 * Return: return the concatenated string
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
 * strings_weigh - this would compare two strings, str1 and str2, then return an
 *	integer value to show us their relative order
 * @str1: this first string
 * @str2: this second string
 *
 * Return: 0 (if str1 == str2) and -ve (str1 < str2) or +ve (str1 > str2)
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
