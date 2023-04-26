#include "shell.h"

/**
 * add_nde - adds a node to the start of the list
 * @hd: address of pointer to head node
 * @strn: strn field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_nde(list_t **hd, const char *strn, int num)
{
	list_t *new_head;

	if (!hd)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (strn)
	{
		new_head->strn = _strdup(strn);
		if (!new_head->strn)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *hd;
	*hd = new_head;
	return (new_head);
}

/**
 * add_node_end - adds a node to the end of the list
 * @hd: address of pointer to head node
 * @strn: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **hd, const char *strn, int num)
{
	list_t *new_node, *nde;

	if (!hd)
		return (NULL);

	nde = *hd;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (strn)
	{
		new_node->strn = _strdup(strn);
		if (!new_node->strn)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (nde)
	{
		while (nde->next)
			nde = nde->next;
		nde->next = new_node;
	}
	else
		*hd = new_node;
	return (new_node);
}

/**
 * print_list_strn - prints only the str element of a list_t linked list
 * @g: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_strn(const list_t *g)
{
	size_t y = 0;

	while (g)
	{
		_puts(g->strn ? g->strn : "(nil)");
		_puts("\n");
		g = g->next;
		y++;
	}
	return (y);
}

/**
 * delete_node_at_index - deletes node at given index
 * @hd: address of pointer to first node
 * @indx: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **hd, unsigned int indx)
{
	list_t *nde, *prev_node;
	unsigned int y = 0;

	if (!hd || !*hd)
		return (0);

	if (!indx)
	{
		nde = *hd;
		*hd = (*hd)->next;
		free(nde->strn);
		free(nde);
		return (1);
	}
	nde = *hd;
	while (nde)
	{
		if (y == indx)
		{
			prev_node->next = nde->next;
			free(nde->strn);
			free(nde);
			return (1);
		}
		y++;
		prev_node = nde;
		nde = de->next;
	}
	return (0);
}

/**
 * free_lst - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_lst(list_t **head_ptr)
{
	list_t *nde, *next_node, *hd;

	if (!head_ptr || !*head_ptr)
		return;
	hd = *head_ptr;
	nde = hd;
	while (nde)
	{
		next_node = nde->next;
		free(nde->strn);
		free(nde);
		nde = next_node;
	}
	*head_ptr = NULL;
}

