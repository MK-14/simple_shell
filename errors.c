#include "shell.h"

/**
 * _eput - prints an input string
 * @strn: the string to be printed
 *
 * Return: Nothing
 */
void _eput(char *strn)
{
	int y = 0;

	if (!strn)
		return;
	while (strn[y] != '\0')
	{
		_eputchar(strn[y]);
		y++;
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @b: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char b)
{
	static int y;
	static char but[WRITE_BUT_SIZE];

	if (b == BUT_FLUSH || y >= WRITE_BUT_SIZE)
	{
		write(2, but, y);
		y = 0;
	}
	if (b != BUT_FLUSH)
		but[y++] = b;
	return (1);
}

/**
 * _putfc - writes the character b to given fc
 * @b: The character to print
 * @fc: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char b, int fc)
{
	static int y;
	static char but[WRITE_BUT_SIZE];

	if (b == BUT_FLUSH || y >= WRITE_BUT_SIZE)
	{
		write(fc, but, y);
		y = 0;
	}
	if (b != BUT_FLUSH)
		but[y++] = b;
	return (1);
}

/**
 * _putsfc - prints an input string
 * @strn: the string to be printed
 * @fc: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfc(char *strn, int fc)
{
	int y = 0;

	if (!strn)
		return (0);
	while (*strn)
	{
		y += _putfc(*strn++, fc);
	}
	return (y);
}
