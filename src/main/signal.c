/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 14:41:18 by ethrober          #+#    #+#             */
/*   Updated: 2026/10/08 14:41:18 by ethrober         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

volatile sig_atomic_t	g_signal;

/**
 * @brief	SIGINT handler used while the prompt is displayed.
 *			Only the signal number is stored in the global variable.
 */
void	handle_signal(int sig)
{
	g_signal =	sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * @brief	Interactive mode: ctrl-C = new prompt, ctrl-\ = nothing.
 */
void	create_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handle_signal;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * @brief	Parent shell while children run: it must ignore both signals,
 *			the children decide what to do with them.
 */
void	signal_exec(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * @brief	Child processes: default behavior.
 */
void	signal_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

/**
 * @brief	Heredoc reader: ctrl-C kills it, ctrl-\ does nothing.
 */
void	signal_heredoc(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}
