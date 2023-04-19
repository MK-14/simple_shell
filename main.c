#include "shell.h"

/**
 * main - entry point
 * @ad: arg count
 * @ab: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ad, char **ab)
{
	info_t inf[] = { INFO_INIT };
	int fc = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fc)
			: "r" (fc));

	if (ad == 2)
	{
		fc = open(ab[1], O_RDONLY);
		if (fc == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(ab[0]);
				_eputs(": 0: Can't open ");
				_eputs(ab[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		inf->readfc = fc;
	}
	populate_env_list(inf);
	read_history(inf);
	hsh(inf, ab);
	return (EXIT_SUCCESS);
}

