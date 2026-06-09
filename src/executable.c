#include "../includes/colors.h"
#include "../includes/includes.h"
#include "../includes/minishell.h"

void	ft_executable(char **command)
{
	pid_t	pid;
	char	*str;

	pid = fork();
	if (pid == 0)
	{
		if (ft_strncmp(command[0], "~", 1) == 0)
		{
			command[0] = ft_substr(command[0], 1, ft_strlen(command[0]));
			command[0] = ft_strjoin(getenv("HOME"), command[0]);
		}
		execve(command[0], command, NULL);
		if (ft_strncmp(strerror(errno), "No such file or directory", 50) == 0)
		{
			str = ft_strjoin("/bin/", command[0]);
			execve(str, command, NULL);
		}
		free(str);
		error(command[0], strerror(errno));
		exit(1);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	else
		perror("fork");
}
