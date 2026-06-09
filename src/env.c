#include "../includes/colors.h"
#include "../includes/includes.h"
#include "../includes/minishell.h"

void	ft_env(char **command, char **envp)
{
	int		i;
	char	*var;

	if (command[1])
	{
		i = 1;
		while (command[i])
		{
			var = getenv(command[i]);
			if (!var)
				error(command[0], "Environnement variable not found");
			else
				printf("%s=%s\n", command[i], var);
			i++;
		}
	}
	else
	{
		i = 0;
		while (envp[i])
		{
			printf("%s\n", envp[i]);
			i++;
		}
	}
}
