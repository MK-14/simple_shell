#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @inf: the parameter struct
 * @but: the char buffer
 * @q: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *inf, char *but, size_t *q)
{
	size_t g = *q;

	if (but[g] == '|' && but[g + 1] == '|')
	{
		but[g] = 0;
		g++;
		inf->cmd_buf_type = CMD_OR;
	}
	else if (but[g] == '&' && but[g + 1] == '&')
	{
		but[g] = 0;
		g++;
		inf->cmd_buf_type = CMD_AND;
	}
	else if (but[g] == ';') /* found end of this command */
	{
		but[g] = 0; /* replace semicolon with null */
		inf->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*q = g;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @inf: the parameter struct
 * @but: the char buffer
 * @q: address of current position in buf
 * @y: starting position in buf
 * @ln: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *inf, char *but, size_t *q, size_t y, size_t ln)
{
	size_t g = *q;

	if (inf->cmd_buf_type == CMD_AND)
	{
		if (inf->status)
		{
			but[y] = 0;
			g = ln;
		}
	}
	if (inf->cmd_buf_type == CMD_OR)
	{
		if (!inf->status)
		{
			but[y] = 0;
			g = ln;
		}
	}

	*q = g;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @inf: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *inf)
{
	int y;
	list_t *nde;
	char *q;

	for (y = 0; y < 10; y++)
	{
		nde = node_starts_with(inf->alias, inf->argb[0], '=');
		if (!nde)
			return (0);
		free(inf->argb[0]);
		q = _strchr(nde->strn, '=');
		if (!q)
			return (0);
		q = _strdup(q + 1);
		if (!q)
			return (0);
		inf->argb[0] = q;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @inf: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *inf)
{
	int y = 0;
	list_t *nde;

	for (y = 0; inf->argb[y]; y++)
	{
		if (inf->argb[y][0] != '$' || !inf->argb[y][1])
			continue;

		if (!_strcmp(inf->argb[y], "$?"))
		{
			replace_string(&(inf->argb[y]),
					_strdup(convert_number(inf->status, 10, 0)));
			continue;
		}
		if (!_strcmp(inf->argb[y], "$$"))
		{
			replace_string(&(inf->argb[y]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		nde = node_starts_with(inf->envi, &inf->argb[y][1], '=');
		if (nde)
		{
			replace_string(&(inf->argb[y]),
					_strdup(_strchr(nde->strn, '=') + 1));
			continue;
		}
		replace_string(&inf->argb[y], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @nw: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *nw)
{
	free(*old);
	*old = nw;
	return (1);
}

