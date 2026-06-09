#include "../includes/colors.h"
#include "../includes/includes.h"
#include "../includes/minishell.h"

/* void	find_command(t_command command, char **envp)
{
	if (ft_strncmp(command.commands[0], "cd", 2))
		ft_cd(command);
	if (ft_strncmp(command.commands[0], "color", 5))
		ft_color(command);
	if (ft_strncmp(command.commands[0], "echo", 4))
		ft_echo(command);
	if (ft_strncmp(command.commands[0], "env", 3))
		ft_env(command, envp);
	if (ft_strncmp(command.commands[0], "exit", 4))
		ft_exit(command);
	if (ft_strncmp(command.commands[0], "pwd", 3))
		ft_pwd(command);
	else
		ft_executable(command);
} */

void	execute_command(char *line, char **envp)
{
	t_command	command;

	(void)envp;
	command = parse_command(line, command);
	print_command(command);
	/* find_command(command, envp); */
	free_struct(command);
}
