#include "shell.h"

/**
 * _myenvi - prints the current environment
 * @inf: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _myenvi(info_t *inf)
{
	print_list_str(inf->envi);
	return (0);
}

/**
 * _getenvi - gets the value of an environ variable
 * @inf: Structure containing potential arguments. Used to maintain
 * @nme: env var name
 *
 * Return: the value
 */
char *_getenv(info_t *inf, const char *nme)
{
	list_t *nde = inf->envi;
	char *q;

	while (nde)
	{
		q = starts_with(nde->str, nme);
		if (q && *q)
			return (q);
		nde = nde->next;
	}
	return (NULL);
}

/**
 * _mysetenvi - Initialize a new environment variable,
 * or modify an existing one
 * @inf: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _mysetenvi(info_t *inf)
{
	if (inf->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenvi(inf, inf->argb[1], inf->argb[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenvi - Remove an environment variable
 * @inf: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _myunsetenvi(info_t *inf)
{
	int y;

	if (inf->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (y = 1; y <= inf->argc; i++)
		_unsetenvi(inf, inf->argb[y]);

	return (0);
}

/**
 * populate_envi_list - populates envi linked list
 * @inf: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int populate_envi_list(info_t *inf)
{
	list_t *nde = NULL;
	size_t y;

	for (y = 0; environ[y]; y++)
		add_node_end(&nde, environ[y], 0);
	inf->env = nde;
	return (0);
}
