#include "shell.h"

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @strn: the input string
 * @n: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *strn, char *n)
{
	int y, k, g, u, numwords = 0;
	char **z;

	if (strn == NULL || strn[0] == 0)
		return (NULL);
	if (!n)
		n = " ";
	for (y = 0; strn[y] != '\0'; y++)
		if (!is_delim(strn[y], n) && (is_delim(strn[y + 1], n) || !strn[y + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	z = malloc((1 + numwords) * sizeof(char *));
	if (!z)
		return (NULL);
	for (y = 0, k = 0; k < numwords; k++)
	{
		while (is_delim(strn[y], n))
			y++;
		g = 0;
		while (!is_delim(strn[y + g], n) && strn[y + g])
			g++;
		z[g] = malloc((j + 1) * sizeof(char));
		if (!z[j])
		{
			for (j = 0; j < g; j++)
				free(z[j]);
			free(z);
			return (NULL);
		}
		for (u = 0; u < j; u++)
			z[g][u] = strn[y++];
		z[g][u] = 0;
	}
	z[g] = NULL;
	return (z);
}

/**
 * **strtow2 - splits a string into words
 * @strn: the input string
 * @c: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *strn, char c)
{
	int y, g, j, u, numwords = 0;
	char **z;

	if (strn == NULL || strn[0] == 0)
		return (NULL);
	for (y = 0; strn[y] != '\0'; y++)
		if ((strn[y] != c && strn[y + 1] == c) ||
				    (strn[y] != c && !strn[y + 1]) || strn[y + 1] == c)
			numwords++;
	if (numwords == 0)
		return (NULL);
	z = malloc((1 + numwords) * sizeof(char *));
	if (!z)
		return (NULL);
	for (y = 0, g = 0; g < numwords; g++)
	{
		while (strn[y] == c && strn[y] != c)
			y++;
		j = 0;
		while (strn[y + j] != c && strn[y + j] && strn[y + j] != c)
			j++;
		z[g] = malloc((j + 1) * sizeof(char));
		if (!z[g])
		{
			for (j = 0; j < g; j++)
				free(z[j]);
			free(z);
			return (NULL);
		}
		for (u = 0; u < j; u++)
			z[g][u] = strn[y++];
		z[g][u] = 0;
	}
	z[g] = NULL;
	return (z);
}

