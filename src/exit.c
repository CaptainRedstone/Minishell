#include "../minishell.h"

void	ft_exit(char **command)
{
	free_array(command);
	exit(1);
}
