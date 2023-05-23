#include "shell.h"


/**
 * locate_char - searches for a particular character in a string and
 *	returns a pointer to the first occurrence of that character
 * @the_real_char: character being looked for
 * @str: string being checked
 *
 * Return: the character that was found in string *start_of_dest
 */
char *locate_char(char *letter, char the_real_char)
{
	while (*letter++ != '\0')
	{
		if (the_real_char == *letter)
		{
			return (letter);
		}
	}
	return (NULL);
}


/**
 * thread_rearr - this function concatenate a part of one string, 
 * begin, onto the end of another string, dest
 * @ending: ending of the string
 * @begin: foundation of string
 * @threshold: maximum number of characters to copy from begin
 *
 * Return: this returns the string after it is concatenated
 */
char *thread_rearr(char *ending, char *begin, int threshold)
{
	int dest_index, begin_index;
	char *start_of_dest = ending;

	dest_index = 0;
	begin_index = 0;
	while (ending[dest_index] != '\0')
		dest_index++;
	while (begin[begin_index] != '\0' && begin_index < threshold)
	{
		ending[dest_index] = begin[begin_index];
		dest_index++;
		begin_index++;
	}
	if (begin_index < threshold)
		ending[dest_index] = '\0';
	return (start_of_dest);
}


/**
 * string_clone - Wonderfully copies the char from the foundation
 * string (begin) to the final end string (ending) and 
 * make it definite that the final end string is null
 * @ending: destination string
 * @begin: source string
 * @minimz: maximum number of characters to copy from begin
 *
 * Return: copied string
 */
char *string_clone(char *ending, char *begin, int minimz)
{
	int index_start, index_ending;
	char *begin_of_end = ending;

	index_start = 0;
	while (begin[index_start] != '\0' && index_start < minimz - 1)
	{
		ending[index_start] = begin[index_start];
		index_start++;
	}
	if (index_start < minimz)
	{
		index_ending = index_start;
		while (index_ending < minimz)
		{
			ending[index_ending] = '\0';
			index_ending++;
		}
	}
	return (begin_of_end);
}


/**
 * word_comot - searches and replaces first instance of '#' with '\0'
 * @txt_word: string to be modifed
 *
 * Return: 0
 */
void word_comot(char *txt_word)
{
	int index_word;

	for (index_word = 0; txt_word[index_word] != '\0'; index_word++)
		if (txt_word[index_word] == '#' && (!index_word || txt_word[index_word - 1] == ' '))
		{
			txt_word[index_word] = '\0';
			break;
		}
}


/**
 * custom_itoa - converts a long integer num into a string
 *	representation in a given base, which can be specified through the flags
 * @num: number
 * @conversionBase: conversionBase
 * @flags: flags
 *
 * Return: converted string
 */
char *custom_itoa(long int num, int conversionBase, int flags)
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
