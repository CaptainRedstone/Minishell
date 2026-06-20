#include "../includes/colors.h"
#include "../includes/includes.h"
#include "../includes/minishell.h"
#include "../includes/parser.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	*prompt;
	t_token	*tokens[1];

	(void)argc;
	(void)argv;
	(void)envp;
	print_welcome();
	create_signal();
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
		{
			tokenize(line, tokens);
			print_tokens(tokens[0]);
			printf("sizeof tokens %zu\n", sizeof(tokens[0]));
			// execute_command(line, envp);
		}
		free(line);
		free(prompt);
	}
	return (0);
}
