/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 14:47:36 by ethrober          #+#    #+#             */
/*   Updated: 2026/10/08 14:47:36 by ethrober         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief	Runs a single builtin (or a command with no name, only
 *			redirections) in the shell process itself, which is needed for
 *			cd, export, unset, exit. stdin/stdout are saved and restored.
 */
void	exec_inline(t_context *ctx, t_cmd *cmd)
{
	ctx->saved_fd[0] = dup(STDIN_FILENO);
	ctx->saved_fd[1] = dup(STDOUT_FILENO);
	if (!apply_redirs(ctx, cmd))
		ctx->exit_status = 1;
	else if (cmd->argc == 0)
		ctx->exit_status = 0;
	else
		ctx->exit_status = run_builtin(ctx, cmd->av);
	dup2(ctx->saved_fd[0], STDIN_FILENO);
	dup2(ctx->saved_fd[1], STDOUT_FILENO);
	close(ctx->saved_fd[0]);
	close(ctx->saved_fd[1]);
	ctx->saved_fd[0] = -1;
	ctx->saved_fd[1] = -1;
}

/**
 * @brief	Entry point of the execution of ctx->cmd_lst: reads the
 *			heredocs, then runs the line either inline (one builtin) or as a
 *			pipeline of processes. Sets ctx->exit_status.
 */
void	monitor(t_context *ctx)
{
	t_cmd	*cmd;

	if (!ctx->cmd_lst)
		return ;
	signal_exec();
	if (read_heredocs(ctx))
	{
		cmd = ctx->cmd_lst->content;
		if (ctx->cmd_cnt == 1 && expand_cmd(ctx, cmd)
			&& (cmd->argc == 0 || is_builtin(cmd->av[0])))
			exec_inline(ctx, cmd);
		else
			exec_pipeline(ctx);
	}
	create_signal();
}
