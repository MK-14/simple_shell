#include "shell.h"

/**
 * get_histry_fle - gets the history file
 * @inf: parameter struct
 *
 * Return: allocated string containing history file
 */
char *get_histry_fle(info_t *inf)
{
	char *but, *dire;

	dire = _getenv(inf, "HOME=");
	if (!dire)
		return (NULL);
	but = malloc(sizeof(char) * (_strlen(dire) + _strlen(HIST_FILE) + 2));
	if (!but)
		return (NULL);
	but[0] = 0;
	_strcpy(but, dire);
	_strcat(but, "/");
	_strcat(but, HIST_FILE);
	return (but);
}

/**
 * wrte_histry - creates a file, or appends to an existing file
 * @inf: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int wrte_histry(info_t *inf)
{
	ssize_t fc;
	char *fname = get_histry_fle(inf);
	list_t *nde = NULL;

	if (!fname)
		return (-1);

	fc = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fname);
	if (fc == -1)
		return (-1);
	for (nde = inf->histry; nde; nde = nde->next)
	{
		_putsfc(nde->str, fc);
		_putfc('\n', fd);
	}
	_putfc(BUF_FLUSH, fd);
	close(fc);
	return (1);
}

/**
 * rd_histry - reads history from file
 * @inf: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int rd_histry(info_t *inf)
{
	int y, last = 0, linecnt = 0;
	ssize_t fc, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *flename = get_histry_fle(inf);

	if (!fname)
		return (0);

	fc = open(fname, O_RDONLY);
	free(fname);
	if (fc == -1)
		return (0);
	if (!fstat(fc, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	but = malloc(sizeof(char) * (fsize + 1));
	if (!but)
		return (0);
	rdlen = read(fc, but, fsize);
	but[fsize] = 0;
	if (rdlen <= 0)
		return (free(but), 0);
	close(fc);
	for (y = 0; y < fsize; y++)
		if (but[y] == '\n')
		{
			but[y] = 0;
			bld_histry_list(inf, but + last, linecnt++);
			last = y + 1;
		}
	if (last != y)
		bld_histry_list(inf, but + last, linecnt++);
	free(but);
	inf->histcount = linecnt;
	while (inf->histcount-- >= HIST_MAX)
		delete_node_at_index(&(inf->history), 0);
	renumber_histry(inf);
	return (inf->histcount);
}

/**
 * bld_histry_list - adds entry to a history linked list
 * @inf: Structure containing potential arguments. Used to maintain
 * @but: buffer
 * @linecnt: the history linecount, histcount
 *
 * Return: Always 0
 */
int bld_histry_list(info_t *inf, char *but, int linecnt)
{
	list_t *nde = NULL;

	if (inf->history)
		nde = inf->history;
	add_node_end(&nde, but, linecnt);

	if (!inf->history)
		inf->history = nde;
	return (0);
}

/**
 * renumber_histry - renumbers the history linked list after changes
 * @inf: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *inf)
{
	list_t *nde = inf->history;
	int y = 0;

	while (nde)
	{
		nde->num = y++;
		nde = nde->next;

	}
	return (inf->histcount = y);
}
