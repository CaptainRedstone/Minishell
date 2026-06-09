#include "../includes/colors.h"
#include "../includes/includes.h"
#include "../includes/minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_struct(t_command command)
{
	if (command.input)
		free(command.input);
	if (command.output)
		free(command.output);
	if (command.command_line)
		free(command.command_line);
	if (command.commands)
		free_array(command.commands);
}
