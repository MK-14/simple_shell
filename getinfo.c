#include "shell.h"

/**
 * clear_info - initializes info_t struct
 * @inf: struct address
 */
void clear_info(info_t *inf)
{
	inf->argu = NULL;
	inf->argb = NULL;
	inf->path = NULL;
	inf->argc = 0;
}

/**
 * set_inf - initializes info_t struct
 * @inf: struct address
 * @arv: argument vector
 */
void set_inf(info_t *inf, char **arv)
{
	int y = 0;

	inf->fname = arv[0];
	if (inf->argu)
	{
		inf->argb = strtow(info->argu, " \t");
		if (!inf->argb)
		{
			inf->argb = malloc(sizeof(char *) * 2);
			if (inf->argb)
			{
				inf->argb[0] = _strdup(inf->argu);
				inf->argb[0] = _strdup(inf->argu);
			}
		}
		for (y = 0; inf->argb && inf->argb[y]; y++)
			;
		inf->argc = y;

		replace_alias(inf);

		replace_vars(inf);
	}
}

/**
 * free_inf - frees info_t struct fields
 * @inf: struct address
 * @all: true if freeing all fields
 */
void free_inf(info_t *inf, int all)
{
	ffree(inf->argb);
	inf->argb = NULL;
	inf->path = NULL;
	if (all)
	{
		if (!inf->cmd_but)
			free(inf->argu);
		if (inf->envi)
			free_list(&(inf->envi));
		if (inf->history)
			free_list(&(inf->history));
		if (inf->alias)
			free_list(&(inf->alias));
		ffree(inf->envirn);
		inf->envirn = NULL;
		bfree((void **)inf->cmd_but);
		if (inf->readfc > 2)
			close(inf->readfc);
		_putchar(BUF_FLUSH);
	}
}
