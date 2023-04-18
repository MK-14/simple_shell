#include "shell.h"

/**
 * _strncopy - copies a string
 * @des: the destination string to be copied to
 * @sorc: the source string
 * @a: the amount of characters to be copied
 * Return: the concatenated string
 */
char *_strncopy(char *des, char *sorc, int a)
{
	int y, k;
	char *z = des;

	y = 0;
	while (sorc[y] != '\0' && y < a - 1)
	{
		des[y] = sorc[y];
		y++;
	}
	if (y < a)
	{
		k = y;
		while (k < a)
		{
			des[k] = '\0';
			k++;
		}
	}
	return (z);
}

/**
 * _strnct - concatenates two strings
 * @des: the first string
 * @sorc: the second string
 * @a: the amount of bytes to be maximally used
 * Return: the concatenated string
 */
char *_strnct(char *des, char *sorc, int a)
{
	int y, k;
	char *z = des;

	y = 0;
	k = 0;
	while (des[y] != '\0')
		y++;
	while (sorc[k] != '\0' && k < n)
	{
		des[k] = sorc[k];
		y++;
		k++;
	}
	if (k < a)
		des[y] = '\0';
	return (z);
}

/**
 * _strchar - locates a character in a string
 * @z: the string to be parsed
 * @b: the character to look for
 * Return: (z) a pointer to the memory area b
 */
char *_strchar(char *z, char b)
{
	do {
		if (*z == b)
			return (z);
	} while (*z++ != '\0');

	return (NULL);
}
