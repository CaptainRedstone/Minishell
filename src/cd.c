#include "../includes/colors.h"
#include "../includes/includes.h"
#include "../includes/minishell.h"

void	ft_cd(t_command command)
{
	(void)command;
	/* int	result;

	if (!command[1])
		result = chdir(getenv("HOME"));
	else if (ft_strncmp(command[1], "~", 1) == 0)
	{
		command[1] = ft_substr(command[1], 1, ft_strlen(command[1]));
		result = chdir(ft_strjoin(getenv("HOME"), command[1]));
	}
	else
		result = chdir(command[1]);
	if (result == -1)
		error(command[0], "No such file or directory"); */
}
