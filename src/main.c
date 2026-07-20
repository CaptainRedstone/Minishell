#include "../includes/colors.h"
#include "../includes/includes.h"
#include "../includes/minishell.h"
#include "../includes/parser.h"

int	main(int argc, char **argv, char **envp)
{
	t_context ct;

	(void)argc;
	(void)argv;
	(void)envp;
	print_welcome();
	create_signal();
	ft_bzero(&ct, sizeof(t_context));
	while (1)
	{
		ct.prompt = build_prompt();
		ct.line = readline(ct.prompt);
		if (!(ct.line))
		{
			free(ct.prompt);
			break ;
		}
		if (*(ct.line))
			add_history(ct.line);
		ct.line_len = ft_strlen(ct.line);
		if (ct.line_len > 0)
		{
			tokenize(&ct);
			ft_lstiter(ct.token_lst, tk_print);
			// execute_command(line, envp);
		}
	}
	return (0);
}
