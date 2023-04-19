#include "shell.h"

/**
 * list_len - determines length of linked list
 * @g: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *h)
{
	size_t y = 0;

	while (g)
	{
		g = g->next;
		y++;
	}
	return (y);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @hd: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *hd)
{
	list_t *nde = hd;
	size_t y = list_len(hd), k;
	char **strs;
	char *strn;

	if (!hd || !y)
		return (NULL);
	strs = malloc(sizeof(char *) * (y + 1));
	if (!strs)
		return (NULL);
	for (y = 0; nde; nde = nde->next, y++)
	{
		strn = malloc(_strlen(nde->strn) + 1);
		if (!strn)
		{
			for (k = 0; k < y; k++)
				free(strs[k]);
			free(strs);
			return (NULL);
		}

		strn = _strcpy(strn, nde->strn);
		strs[y] = strn;
	}
	strs[y] = NULL;
	return (strs);
}


/**
 * prnt_list - prints all elements of a list_t linked list
 * @g: pointer to first node
 *
 * Return: size of list
 */
size_t prnt_list(const list_t *g)
{
	size_t y = 0;

	while (g)
	{
		_puts(convert_number(g->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(g->str ? h->str : "(nil)");
		_puts("\n");
		g = g->next;
		y++;
	}
	return (y);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @nde: pointer to list head
 * @prfix: string to match
 * @d: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *nde, char *prfix, char d)
{
	char *q = NULL;

	while (nde)
	{
		q = starts_with(nde->strn, prfix);
		if (q && ((d == -1) || (*q == d)))
			return (nde);
		nde = nde->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @hd: pointer to list head
 * @nde: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *hd, list_t *nde)
{
	size_t y = 0;

	while (hd)
	{
		if (hd == nde)
			return (y);
		hd = hd->next;
		y++;
	}
	return (-1);
}

