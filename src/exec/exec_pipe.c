/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 14:48:22 by ethrober          #+#    #+#             */
/*   Updated: 2026/10/08 14:48:22 by ethrober         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	close_fd(int fd)
{
	if (fd >= 0)
		close(fd);
}

/**
 * @brief	Code of the child process (never returns): plugs the pipes,
 *			applies the redirections, then runs a builtin or execve.
 * @param	in Read end of the previous pipe (-1 if none).
 * @param	pp Pipe to the next command (-1, -1 if last command).
 */
static void	run_child(t_context *ctx, t_cmd *cmd, int in, int *pp)
{
	signal_default();
	ctx->is_child = 1;
	if (in >= 0)
		dup2(in, STDIN_FILENO);
	if (pp[1] >= 0)
		dup2(pp[1], STDOUT_FILENO);
	close_fd(in);
	close_fd(pp[0]);
	close_fd(pp[1]);
	if (!apply_redirs(ctx, cmd))
		exit_shell(ctx, 1);
	close_heredocs(ctx);
	if (cmd->argc == 0)
		exit_shell(ctx, 0);
	if (is_builtin(cmd->av[0]))
		exit_shell(ctx, run_builtin(ctx, cmd->av));
	exec_external(ctx, cmd->av);
}

static pid_t	spawn(t_context *ctx, t_cmd *cmd, int in, int *pp)
{
	pid_t	pid;

	if (!expand_cmd(ctx, cmd))
	{
		ctx->exit_status = 1;
		return (-1);
	}
	pid = fork();
	if (pid < 0)
	{
		error("fork", strerror(errno));
		ctx->exit_status = 1;
		return (-1);
	}
	if (pid == 0)
		run_child(ctx, cmd, in, pp);
	return (pid);
}

/**
 * @brief	Runs every command of the line in its own process, connected
 *			by pipes, then waits for all of them.
 */
void	exec_pipeline(t_context *ctx)
{
	t_list	*node;
	int		in;
	int		pp[2];
	pid_t	last;

	node = ctx->cmd_lst;
	in = -1;
	last = -1;
	while (node)
	{
		pp[0] = -1;
		pp[1] = -1;
		if (node->next && pipe(pp) < 0)
			break ;
		last = spawn(ctx, node->content, in, pp);
		close_fd(in);
		close_fd(pp[1]);
		in = pp[0];
		node = node->next;
	}
	close_fd(in);
	wait_all(ctx, last);
}
