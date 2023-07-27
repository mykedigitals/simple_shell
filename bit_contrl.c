#include "shell.h"


/**
 * **created_strt - this functions takes input of string and delimiter
 * it then split str into an array of strings
 * @str: the str input
 * @delimiter: the delimeter str
 * Return: this returns the pointer to array of str, or NULL on failure
 */
char **created_strt(char *str, char *delimiter)
{
	int a, b, c, d, word_count = 0;
	char **substrings;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!delimiter)
		delimiter = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!no_limitation(str[a], delimiter) &&
				(no_limitation(str[a + 1], delimiter) || !str[a + 1]))
			word_count++;

	if (word_count == 0)
		return (NULL);
	substrings = malloc((1 + word_count) * sizeof(char *));
	if (!substrings)
		return (NULL);
	for (a = 0, b = 0; b < word_count; b++)
	{
		while (no_limitation(str[b], delimiter))
			b++;
		c = 0;
		while (!no_limitation(str[a + c], delimiter) && str[a + c])
			c++;
		substrings[b] = malloc((c + 1) * sizeof(char));
		if (!substrings[b])
		{
			for (c = 0; c < b; c++)
				free(substrings[c]);
			free(substrings);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			substrings[b][d] = str[a++];
		substrings[b][d] = 0;
	}
	substrings[b] = NULL;
	return (substrings);
}
