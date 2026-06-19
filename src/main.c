#include "../includes/colors.h"
#include "../includes/includes.h"
#include "../includes/minishell.h"
#include "../includes/parser.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	*prompt;
	t_node	node;

	(void)argc;
	(void)argv;
	print_welcome();
	create_signal();
	printf("sizeof ast node %zu\n", sizeof(node));
	while (1)
	{
		prompt = build_prompt();
		line = readline(prompt);
		if (!line)
		{
			free(prompt);
			break ;
		}
		if (*line)
			add_history(line);
		if (ft_strlen(line) > 0)
			execute_command(line, envp);
		free(line);
		free(prompt);
	}
	return (0);
}
