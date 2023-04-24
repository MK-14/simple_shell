#include "shell.h"

/**
 * inp_but - butfers chained commands
 * @inf: parameter struct
 * @but: address of butfer
 * @ln: address of len var
 *
 * Return: bytes read
 */

ssize_t inp_but(info_t *inf, char **but, size_t *ln)
{
	ssize_t t = 0;
	size_t len_p = 0;

	if (!*ln) /* if nothing left in the butfer, fill it */
	{
		/*bfree((void **)inf->cmd_but);*/
		free(*but);
		*but = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		t = getline(but, &len_p, stdin);
#else
		t = _getline(inf, but, &len_p);
#endif
		if (t > 0)
		{
			if ((*but)[t - 1] == '\n')
			{
				(*but)[t - 1] = '\0'; /* remove trailing newline */
				t--;
			}
			inf->linecount_flag = 1;
			rmve_comments(*but);
			build_history_list(inf, *but, inf->histcount++);
			/* if (_strchar(*but, ';')) is this a command chain? */
			{
				*ln = t;
				inf->cmd_but = but;
			}
		}
	}
	return (t);
}

/**
 * get_inp - gets a line minus the newline
 * @inf: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_inp(info_t *inf)
{
	static char *but; /* the ';' command chain butfer */
	static size_t y, k, ln;
	ssize_t t = 0;
	char **but_p = &(inf->arg), *q;

	_putchar(BUT_FLUSH);
	t = input_but(inf, &but, &ln);
	if (t == -1) /* EOF */
		return (-1);
	if (ln) /* we have commands left in the chain butfer */
	{
		k = y; /* init new iterator to current but position */
		q = but + y; /* get pointer for return */

		check_chain(inf, but, &k, y, ln);
		while (k < ln) /* iterate to semicolon or end */
		{
			if (is_chain(inf, but, &k))
				break;
			k++;
		}

		y = k + 1; /* increment past nulled ';'' */
		if (y >= ln) /* reached end of butfer? */
		{
			y = ln = 0; /* reset position and length */
			inf->cmd_but_type = CMD_NORM;
		}

		*but_p = q; /* pass back pointer to current command position */
		return (_strlen(q)); /* return length of current command */
	}

	*but_p = but; /* else not a chain, pass back butfer from _getline() */
	return (t); /* return length of butfer from _getline() */
}

/**
 * read_but - reads a butfer
 * @inf: parameter struct
 * @but: butfer
 * @y: size
 *
 * Return: t
 */
ssize_t read_but(info_t *inf, char *but, size_t *y)
{
	ssize_t t = 0;

	if (*y)
		return (0);
	t = read(inf->readfd, but, READ_BUT_SIZE);
	if (t >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - gets the next line of input from STDIN
 * @inf: parameter struct
 * @pntr: address of pointer to butfer, preallocated or NULL
 * @lgth: size of preallocated pntr butfer if not NULL
 *
 * Return: z
 */
int _getline(info_t *inf, char **pntr, size_t *lgth)
{
	static char but[READ_BUT_SIZE];
	static size_t y, ln;
	size_t j;
	ssize_t t = 0, z = 0;
	char *q = NULL, *new_p = NULL, *b;

	q = *pntr;
	if (q && lngth)
		z = *lngth;
	if (y == ln)
		y = ln = 0;

	t = read_but(inf, but, &ln);
	if (t == -1 || (t == 0 && ln == 0))
		return (-1);

	b = _strchar(but + y, '\n');
	j = b ? 1 + (unsigned int)(b - but) : ln;
	new_p = _realloc(q, z, z ? z + j : j + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (q ? free(p), -1 : -1);

	if (z)
		_strncat(new_p, but + y, j - y);
	else
		_strncpy(new_p, but + y, j - y + 1);

	z += j - y;
	y = j;
	q = new_p;

	if (lgth)
		*lgth = z;
	*pntr = q;
	return (z);
}

/**
 * sigintHandlr - blocks ctrl-C
 * @sigl_num: the signal number
 *
 * Return: void
 */
void sigintHandlr(__attribute__((unused))int sigl_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUT_FLUSH);
}


