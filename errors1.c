#include "shell.h"
/**
 * _eratoi - converts a string to an integer
 * @z: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 * -1 on error
 */
int _eratoi(char *z)
{
	int y = 0;
	unsigned long int result = 0;

	if (*z == '+')
		z++;  /* TODO: why does this make main return 255? */
	for (y = 0;  z[y] != '\0'; y++)
	{
		if (z[y] >= '0' && z[y] <= '9')
		{
			result *= 10;
			result += (z[y] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * prnt_error - prints an error message
 * @inf: the parameter & return info struct
 * @estrn: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 * -1 on error
 */
void prnt_error(info_t *inf, char *estrn)
{
	_eputs(inf->fname);
	_eputs(": ");
	print_d(inf->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(inf->argb[0]);
	_eputs(": ");
	_eputs(estrn);
}

/**
 * prnt_d - function prints a decimal (integer) number (base 10)
 * @inp: the input
 * @fc: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int prnt_d(int inp, int fc)
{
	int (*__putchar)(char) = _putchar;
	int y, count = 0;
	unsigned int _abs_, current;

	if (fc == STDERR_FILENO)
		__putchar = _eputchar;
	if (inp < 0)
	{
		_abs_ = -inp;
		__putchar('-');
		count++;
	}
	else
		_abs_ = inp;
	current = _abs_;
	for (y = 1000000000; y > 1; y /= 10)
	{
		if (_abs_ / y)
		{
			__putchar('0' + current / y);
			count++;
		}
		current %= y;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * conv_number - converter function, a clone of itoa
 * @nm: number
 * @bse: base
 * @flag: argument flags
 *
 * Return: string
 */
char *conv_number(long int nm, int bse, int flag)
{
	static char *array;
	static char butfer[50];
	char sign = 0;
	char *qtr;
	unsigned long n = nm;

	if (!(flag & CONVERT_UNSIGNED) && nm < 0)
	{
		n = -nm;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	qtr = &butfer[49];
	*qtr = '\0';

	do	{
		*--qtr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--qtr = sign;
	return (qtr);
}

/**
 * rmve_comments - function replaces first instance of '#' with '\0'
 * @but: address of the string to modify
 *
 * Return: Always 0;
 */
void rmve_comments(char *but)
{
	int y;

	for (y = 0; but[y] != '\0'; y++)
		if (but[y] == '#' && (!y || but[y - 1] == ' '))
		{
			but[y] = '\0';
			break;
		}
}
