#include "shell.h"

/**
 * hsh - main shell loop
 * @inf: the parameter & return info struct
 * @ab: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *inf, char **ab)
{
	ssize_t t = 0;
	int builtin_ret = 0;

	while (t != -1 && builtin_ret != -2)
	{
		clear_info(inf);
		if (interactive(inf))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		t = get_input(inf);
		if (t != -1)
		{
			set_info(inf, ab);
			builtin_ret = find_builtin(inf);
			if (builtin_ret == -1)
				find_cmd(inf);
		}
		else if (interactive(inf))
			_putchar('\n');
		free_info(inf, 0);
	}
	write_history(inf);
	free_info(inf, 1);
	if (!interactive(inf) && inf->status)
		exit(inf->status);
	if (builtin_ret == -2)
	{
		if (inf->err_num == -1)
			exit(inf->status);
		exit(inf->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @inf: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 	0 if builtin executed successfully,
 * 	1 if builtin found but not successful,
 * 	2 if builtin signals exit()
 */
int find_builtin(info_t *inf)
{
	int y, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (y = 0; builtintbl[y].type; y++)
		if (_strcmp(inf->argb[0], builtintbl[y].type) == 0)
		{
			inf->line_count++;
			built_in_ret = builtintbl[y].func(inf);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @inf: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(info_t *inf)
{
	char *path = NULL;
	int y, g;

	inf->pth = inf->argb[0];
	if (inf->linecount_flag == 1)
	{
		inf->line_count++;
		inf->linecount_flag = 0;
	}
	for (y = 0, g = 0; inf->argu[y]; y++)
		if (!is_delim(inf->argu[y], " \t\n"))
			g++;
	if (!g)
		return;

	pth = find_path(inf, _getenv(inf, "PTH="), inf->argb[0]);
	if (pth)
	{
		inf->pth = pth;
		fork_cmd(inf);
	}
	else
	{
		if ((interactive(in) || _getenv(info, "PATH=")
					|| inf->argb[0][0] == '/') && is_cmd(inf, inf->argb[0]))
			fork_cmd(inf);
		else if (*(inf->argu) != '\n')
		{
			inf->status = 127;
			print_error(inf, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @inf: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *in)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->pth, inf->argb, get_environ(inf)) == -1)
		{
			free_info(inf, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(inf->status));
		if (WIFEXITED(inf->status))
		{
			inf->status = WEXITSTATUS(inf->status);
			if (inf->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

