#include "../includes/colors.h"
#include "../includes/includes.h"
#include "../includes/minishell.h"
#include "../includes/parser.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	*prompt;
	t_token	**pt_tokens;

	(void)argc;
	(void)argv;
	(void)envp;
	pt_tokens = malloc(sizeof(t_token *));
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
			tokenize(line, pt_tokens);
			print_tokens(*pt_tokens);
			printf("sizeof tokens %zu\n", sizeof(*pt_tokens));
			// execute_command(line, envp);
		}
		free(line);
		free(prompt);
	}
	return (0);
}
