#include "../includes/colors.h"
#include "../includes/includes.h"
#include "../includes/minishell.h"
#include "../includes/parser.h"

int	main(int argc, char **argv, char **envp)
{
	t_context ctx;

	(void)argc;
	(void)argv;
	(void)envp;
	print_welcome();
	create_signal();
	ft_bzero(&ctx, sizeof(t_context));
	while (1)
	{
		ctx.prompt = build_prompt();
		ctx.line = readline(ctx.prompt);
		if (!(ctx.line))
		{
			free(ctx.prompt);
			break ;
		}
		if (*(ctx.line))
			add_history(ctx.line);
		if (ft_strlen(ctx.line) > 0)
		{
			printf("ok\n");
			tokenize(&ctx);
			print_tokens(&ctx);
			// execute_command(line, envp);
		}
		free(ctx.line);
		free(ctx.prompt);
	}
	return (0);
}
