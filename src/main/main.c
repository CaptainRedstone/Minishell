/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 14:41:06 by ethrober          #+#    #+#             */
/*   Updated: 2026/10/08 14:41:06 by ethrober         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	read_line(t_context *ct)
{
	int	tty;

	tty = isatty(STDIN_FILENO);
	if (tty)
		ct->prompt = build_prompt(ct);
	ct->line = read_input(ct->prompt);
	if (g_signal == SIGINT)
	{
		ct->exit_status = 130;
		g_signal = 0;
	}
	if (!ct->line)
		return (0);
	if (*ct->line && tty)
		add_history(ct->line);
	ct->line_len = ft_strlen(ct->line);
	return (1);
}

static void	run_line(t_context *ct)
{
	if (ct->line_len == 0 || !tokenize(ct))
		return ;
	if (init_cmd_lst(ct))
		monitor(ct);
}

static void	init_shell(t_context *ct, char **envp)
{
	ft_bzero(ct, sizeof(t_context));
	ct->saved_fd[0] = -1;
	ct->saved_fd[1] = -1;
	init_env(ct, envp);
	if (isatty(STDIN_FILENO))
		print_welcome(ct);
	create_signal();
}

int	main(int argc, char **argv, char **envp)
{
	t_context	ct;

	(void)argc;
	(void)argv;
	init_shell(&ct, envp);
	while (read_line(&ct))
	{
		run_line(&ct);
		free_line(&ct);
	}
	if (isatty(STDIN_FILENO))
		ft_putendl_fd("exit", STDERR_FILENO);
	exit_shell(&ct, ct.exit_status);
	return (0);
}
