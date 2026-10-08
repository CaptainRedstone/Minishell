/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 14:45:38 by ethrober          #+#    #+#             */
/*   Updated: 2026/10/08 14:45:38 by ethrober         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief	Child process: reads lines until the delimiter and writes
 *			them in fd. ctrl-C kills it, ctrl-D stops it with a warning.
 */
static void	heredoc_child(t_context *ctx, t_redir *r, int fd)
{
	char	*line;
	char	*delim;
	int		quoted;

	signal_heredoc();
	delim = strip_quotes(r->val.delim, &quoted);
	while (delim)
	{
		line = read_input("> ");
		if (!line)
		{
			warn_eof(delim);
			break ;
		}
		if (!ft_strncmp(line, delim, ft_strlen(delim) + 1))
		{
			free(line);
			break ;
		}
		write_line(ctx, fd, line, quoted);
	}
	free(delim);
	close(fd);
	exit_shell(ctx, 0);
}

static int	heredoc_wait(t_context *ctx, pid_t pid, int rfd, t_redir *r)
{
	int	st;

	waitpid(pid, &st, 0);
	if (WIFSIGNALED(st) && WTERMSIG(st) == SIGINT)
	{
		close(rfd);
		ft_putchar_fd('\n', STDERR_FILENO);
		ctx->exit_status = 130;
		return (0);
	}
	r->heredoc_fd = rfd;
	return (1);
}

static int	heredoc_one(t_context *ctx, t_redir *r)
{
	int		rfd;
	int		wfd;
	pid_t	pid;

	wfd = open_tmp(ctx, &rfd);
	if (wfd < 0 || rfd < 0)
		return (tmp_fail(wfd, rfd));
	pid = fork();
	if (pid < 0)
		return (tmp_fail(wfd, rfd));
	if (pid == 0)
	{
		close(rfd);
		heredoc_child(ctx, r, wfd);
	}
	close(wfd);
	return (heredoc_wait(ctx, pid, rfd, r));
}

/**
 * @brief	Reads all the heredocs of the command line, in order, before
 *			anything is executed. Each content goes to an unlinked
 *			temporary file, whose read descriptor is stored in the redir.
 * @return	`1` on success, `0` if interrupted (ctrl-C) or on error.
 */
int	read_heredocs(t_context *ctx)
{
	t_list	*cmd;
	t_list	*node;
	t_redir	*redir;

	cmd = ctx->cmd_lst;
	while (cmd)
	{
		node = ((t_cmd *)cmd->content)->redir_in_lst;
		while (node)
		{
			redir = node->content;
			if (redir->type == R_HEREDOC && !heredoc_one(ctx, redir))
				return (0);
			node = node->next;
		}
		cmd = cmd->next;
	}
	return (1);
}
