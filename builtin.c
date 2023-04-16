#include "shell.h"

/**
 * _myext - exits the shell
 * @inf: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if info.argb[0] != "exit"
 */
int _myext(info_t *inf)
{
	int exitcheck;

	if (inf->argb[1]) /* If there is an exit argument */
	{
		exitcheck = _erratoi(inf->argc[1]);
		if (exitcheck == -1)
		{
			inf->status = 2;
			print_error(inf, "Illegal number: ");
			_eputs(inf->argb[1]);
			_eputchar('\n');
			return (1);
		}
		inf->err_num = _erratoi(inf->argb[1]);
		return (-2);
	}
	inf->err_num = -1;
	return (-2);
}

/**
 * _myd - changes the current directory of the process
 * @inf: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _myd(info_t *inf)
{
	char *z, *dir, butfer[1024];
	int chdir_ret;

	z = getcwd(butfer, 1024);
	if (!z)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!inf->argb[1])
	{
		dr = _getenv(inf, "HOME=");
		if (!dr)
			chdir_ret = /* TODO: what should this be? */
				chdir((dr = _getenv(inf, "PWD=")) ? dr : "/");
		else
			chdir_ret = chdir(dr);
	}
	else if (_strcmp(inf->argb[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(inf->argb[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(inf->argb[1]), _eputchar('\n');
	}
	return (0);
}

/**
 * _myhlp - changes the current directory of the process
 * @inf: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _myhlp(info_t *inf)
{
	char **arg_array;

	arg_array = inf->argb;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
