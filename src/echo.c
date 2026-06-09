#include "../includes/colors.h"
#include "../includes/includes.h"
#include "../includes/minishell.h"

void	ft_echo(char **command)
{
	if (command[1])
	{
		if (ft_strncmp(command[1], "-n", 4) == 0 && command[2])
			printf("%s", command[2]);
		else if (ft_strncmp(command[1], "-n", 4) != 0)
			printf("%s\n", command[1]);
	}
}
