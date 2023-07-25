#include "shell.h"


/**
 * to_find_char - this will search for particular character in string and
 *	return a pointer to the first sign of that character
 * @target_char: the character to be found.
 * @str: the string to be checked
 *
 * Return: this is the character that is found in string *start_of_dest
 */
char *to_find_char(char *str, char target_char)
{
	while (*str++ != '\0')
	{
		if (target_char == *str)
		{
			return (str);
		}
	}
	return (NULL);
}


/**
 * addMore_str - this will concatenate one portion of string, src, with the
 *	end of another string, which is dest
 * @dest: this destination string
 * @src: this source string
 * @max_chars: represents  maximum number of characters to be copied from src
 *
 * Return: the concatenated string
 */
char *addMore_str(char *dest, char *src, int max_chars)
{
	int dest_index, source_index;
	char *start_of_dest = dest;

	dest_index = 0;
	source_index = 0;
	while (dest[dest_index] != '\0')
		dest_index++;
	while (src[source_index] != '\0' && source_index < max_chars)
	{
		dest[dest_index] = src[source_index];
		dest_index++;
		source_index++;
	}
	if (source_index < max_chars)
		dest[dest_index] = '\0';
	return (start_of_dest);
}


/**
 * string_to_copy - this copies characters from the source string (src) to (dest) and sees
 * that the destination
 *	string is null-terminated
 * @dest: this  destination string
 * @src: this source string
 * @limit: this max no characters to copy from src
 *
 * Return: the string that was copied
 */
char *string_to_copy(char *dest, char *src, int limit)
{
	int src_idx, dest_idx;
	char *dest_start = dest;

	src_idx = 0;
	while (src[src_idx] != '\0' && src_idx < limit - 1)
	{
		dest[src_idx] = src[src_idx];
		src_idx++;
	}
	if (src_idx < limit)
	{
		dest_idx = src_idx;
		while (dest_idx < limit)
		{
			dest[dest_idx] = '\0';
			dest_idx++;
		}
	}
	return (dest_start);
}


/**
 * thisRm_comments - this will search then  replace first show of '#' with '\0'
 * @text: the string be modifed
 *
 * Return: 0
 */
void thisRm_comments(char *text)
{
	int idx;

	for (idx = 0; text[idx] != '\0'; idx++)
		if (text[idx] == '#' && (!idx || text[idx - 1] == ' '))
		{
			text[idx] = '\0';
			break;
		}
}


/**
 * selfCreated_get - this converts long int num to a str representer in a base
 * @num: the  number
 * @conversionBase: tis is conversionBase
 * @flags: our flags
 *
 * Return: the converted string
 */
char *selfCreated_get(long int num, int conversionBase, int flags)
{
	static char *conversionArray;
	static char conversionBuffer[50];
	char negativeSign = 0;
	char *currentChar;
	unsigned long unsignedNumber = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		unsignedNumber = -num;
		negativeSign = '-';

	}
	conversionArray = flags & CONVERT_LOWERCASE ?
		"0123456789abcdef" : "0123456789ABCDEF";
	currentChar = &conversionBuffer[49];
	*currentChar = '\0';

	do	{
		*--currentChar = conversionArray[unsignedNumber % conversionBase];
		unsignedNumber /= conversionBase;
	} while (unsignedNumber != 0);

	if (negativeSign)
		*--currentChar = negativeSign;
	return (currentChar);
}
