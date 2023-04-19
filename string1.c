#include "shell.h"

/**
 * _strcopy - copies a string
 * @dst: the destination
 * @sorc: the source
 *
 * Return: pointer to destination
 */
char *_strcopy(char *dst, char *sorc)
{
	int y = 0;

	if (dst == sorc || sorc == 0)
		return (dst);
	while (sorc[y])
	{
		dst[y] = sorc[y];
		y++;
	}
	dst[y] = 0;
	return (dst);
}

/**
 * _strdup - duplicates a string
 * @strn: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *strn)
{
	int length = 0;
	char *ret;

	if (strn == NULL)
		return (NULL);
	while (*strn++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * _puts - prints an input string
 * @strn: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *strn)
{
	int y = 0;

	if (!strn)
		return;
	while (strn[y] != '\0')
	{
		_putchar(strn[y]);
		y++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @b: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char b)
{
	static int y;
	static char but[WRITE_BUF_SIZE];

	if (b == BUF_FLUSH || y >= WRITE_BUF_SIZE)
	{
		write(1, but, y);
		y = 0;
	}
	if (b != BUF_FLUSH)
		but[y++] = b;
	return (1);
}

