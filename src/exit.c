#include "../includes/colors.h"
#include "../includes/includes.h"
#include "../includes/minishell.h"

void	ft_exit(char **command)
{
	free_array(command);
	exit(1);
}
