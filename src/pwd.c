#include "../minishell.h"

void	ft_pwd(char **command)
{
	(void)command;
	printf("%s\n", get_prompt());
}
