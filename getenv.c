#include "shell.h"

/**
 * get_envirn - returns the string array copy of our environ
 * @inf: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
char **get_envirn(info_t *inf)
{
	if (!info->envirn || inf->env_changed)
	{
		inf->envirn = list_to_strings(inf->envi);
		inf->env_changed = 0;
	}

	return (inf->envirn);
}

/**
 * _unsetenvi - Remove an environment variable
 * @inf: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenvi(info_t *inf, char *var)
{
	list_t *nde = inf->envi;
	size_t y = 0;
	char *q;

	if (!nde || !var)
		return (0);

	while (nde)
	{
		q = starts_with(nde->str, var);
		if (q && *q == '=')
		{
			inf->env_changed = delete_node_at_index(&(inf->envi), y);
			y = 0;
			nde = inf->envi;
			continue;
		}
		nde = nde->next;
		y++;
	}
	return (inf->env_changed);
}

/**
 * _setenvi - Initialize a new environment variable,
 * or modify an existing one
 * @inf: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * @var: the string env var property
 * @valu: the string env var value
 * Return: Always 0
 */
int _setenvi(info_t *inf, char *var, char *valu)
{
	char *but = NULL;
	list_t *nde;
	char *q;

	if (!var || !valu)
		return (0);

	but = malloc(_strlen(var) + _strlen(valu) + 2);
	if (!but)
		return (1);
	_strcpy(but, var);
	_strcat(but, "=");
	_strcat(but, valu);
	nde = inf->envi;
	while (nde)
	{
		q = starts_with(nde->strn, var);
		if (q && *q == '=')
		{
			free(nde->strn);
			nde->strn = but;
			inf->env_changed = 1;
			return (0);
		}
		nde = nde->next;
	}
	add_node_end(&(inf->envi), but, 0);
	free(but);
	inf->env_changed = 1;
	return (0);
}
