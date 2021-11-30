#include "pipex.h"

void	ft_error(char *str)
{
	printf("%s\n", str);
	exit(0);
}

void	free_comm(char **command)
{
	int	i;

	i = 1;
	free(command[0]);
	while (command[i] != 0)
	{
		free(command[i]);
		i++;
	}
	free(command);
}