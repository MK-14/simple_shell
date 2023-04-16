#include "shell.h"

/**
 * interactive - returns true if shell is interactive mode
 * @inf: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(inf_t *inf)
{
	return (isatty(STDIN_FILENO) && inf->readfd <= 2);
}

/**
 * is_deli - checks if character is a delimeter
 * @b: the char to check
 * @deli: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_deli(char b, char *deli)
{
	while (*deli)
		if (*deli++ == c)
			return (1);
	return (0);
}

/**
 * _isal - checks for alphabetic character
 * @x: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int _isal(int x)
{
	if ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts a string to an integer
 * @z: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */
int _atoi(char *z)
{
	int y, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (y = 0; z[y] != '\0' && flag != 2; y++)
	{
		if (z[y] == '-')
			sign *= -1;

		if (z[y] >= '0' && z[y] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (z[y] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
