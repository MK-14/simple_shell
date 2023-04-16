#include "shell.h"

/**
 * _myhist - displays the history list, one command by line, preceded
 * with line numbers, starting at 0.
 * @inf: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _myhist(info_t *inf)
{
	print_list(inf->hist);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @inf: parameter struct
 * @strn: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *inf, char *strn)
{
	char *q, b;
	int ret;

	q = _strchr(strn, '=');
	if (!q)
		return (1);
	b = *q;
	*q = 0;
	ret = delete_node_at_index(&(inf->alias),
			get_node_index(inf->alias, nde_starts_with(inf->alias, strn, -1)));
	*q = b;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @inf: parameter struct
 * @strn: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *inf, char *strn)
{
	char *q;

	q = _strchr(strn, '=');
	if (!q)
		return (1);
	if (!*++q)
		return (unset_alias(inf, strn));

	unset_alias(inf, strn);
	return (add_node_end(&(inf->alias), strn, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @nde: the alias node
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *nde)
{
	char *q = NULL, *v = NULL;

	if (node)
	{
		q = _strchr(nde->strn, '=');
		for (v = nde->strn; v <= q; v++)
		_putchar(*v);
		_putchar('\'');
		_puts(q + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @inf: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _myalias(inf_t *inf)
{
	int y = 0;
	char *q = NULL;
	list_t *nde = NULL;

	if (inf->argc == 1)
	{
		nde = inf->alias;
		while (nde)
		{
			print_alias(nde);
			nde = nde->next;
	}
	return (0);
}
for (y = 1; inf->argb[y]; i++)
{
	q = _strchr(inf->argb[y], '=');
	if (q)
		set_alias(inf, inf->argb[y]);
	else
		print_alias(nde_starts_with(inf->alias, inf->argb[y], '='));
}

return (0);
}
