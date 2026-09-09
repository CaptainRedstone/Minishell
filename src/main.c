/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aforcada <aforcada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 16:32:34 by aforcada          #+#    #+#             */
/*   Updated: 2026/09/09 16:32:38 by aforcada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (0 < ct.line_len)
		{
			tokenize(&ct);
			ft_lstiter(ct.token_lst, &print_token);
			init_cmd_lst(&ct);
			// execute_command(line, envp);
		}
	}
	return (0);
}
