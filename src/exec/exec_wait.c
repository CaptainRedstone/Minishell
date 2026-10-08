/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wait.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 14:47:42 by ethrober          #+#    #+#             */
/*   Updated: 2026/10/08 14:47:42 by ethrober         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief	Converts a wait status to a shell status: exit code, or
 *			128 + signal number (with the usual message for ctrl-C/ctrl-\).
 */
static int	decode_status(int st)
{
	if (WIFEXITED(st))
		return (WEXITSTATUS(st));
	if (WIFSIGNALED(st))
	{
		if (WTERMSIG(st) == SIGINT)
			ft_putchar_fd('\n', STDERR_FILENO);
		else if (WTERMSIG(st) == SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
		return (128 + WTERMSIG(st));
	}
	return (1);
}

/**
 * @brief	Waits for the whole pipeline. The status of the pipeline is
 *			the one of its last command.
 */
void	wait_all(t_context *ctx, pid_t last)
{
	int	st;
	int	pid;

	if (last > 0 && waitpid(last, &st, 0) > 0)
		ctx->exit_status = decode_status(st);
	pid = wait(NULL);
	while (pid > 0)
		pid = wait(NULL);
}
