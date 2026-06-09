#include "../includes/colors.h"
#include "../includes/includes.h"
#include "../includes/minishell.h"

void	print_command(t_command command)
{
	int	i;

	i = 0;
	printf("t_command\t:\ninput\t\t: '%s'\noutput\t\t: '%s'\ncommand_line\t: '%s'\n",
		command.input, command.output, command.command_line);
	while (command.commands[i])
	{
		printf("commands[%d]\t: '%s'\n", i, command.commands[i]);
		i++;
	}
}
