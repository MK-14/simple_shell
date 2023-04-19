#include "shell.h"

/**
 * _memset - fills memory with a constant byte
 * @w: the pointer to the memory area
 * @c: the byte to fill *s with
 * @x: the amount of bytes to be filled
 * Return: (w) a pointer to the memory area s
 */
char *_memset(char *w, char c, unsigned int x)
{
	unsigned int y;

	for (y = 0; y < x; y++)
		w[y] = c;
	return (w);
}

/**
 * ffree - frees a string of strings
 * @qq: string of strings
 */
void ffree(char **qq)
{
	char **a = qq;

	if (!qq)
		return;
	while (*qq)
		free(*qq++);
	free(a);
}

/**
 * _realloc - reallocates a block of memory
 * @pntr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @nw_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *pntr, unsigned int old_size, unsigned int nw_size)
{
	char *q;

	if (!pntr)
		return (malloc(nw_size));
	if (!nw_size)
		return (free(pntr), NULL);
	if (nw_size == old_size)
		return (pntr);

	q = malloc(nw_size);
	if (!q)
		return (NULL);

	old_size = old_size < nw_size ? old_size : nw_size;
	while (old_size--)
		q[old_size] = ((char *)pntr)[old_size];
	free(pntr);
	return (q);
}

