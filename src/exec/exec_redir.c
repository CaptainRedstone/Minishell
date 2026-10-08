/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 14:47:47 by ethrober          #+#    #+#             */
/*   Updated: 2026/10/08 14:47:47 by ethrober         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief	Opens the file of a redirection (heredoc: already opened).
 * @return	The descriptor, or -1 (error printed).
 */
static int	open_redir(t_context *ctx, t_redir *r)
{
	char	*path;
	int		fd;

	if (r->type == R_HEREDOC)
		return (r->heredoc_fd);
	path = expand_redir_path(ctx, r);
	if (!path)
		return (-1);
	fd = open(path, r->mode, 0644);
	if (fd < 0)
		error(path, strerror(errno));
	free(path);
	return (fd);
}

static int	apply_list(t_context *ctx, t_list *lst)
{
	t_redir	*r;
	int		fd;
	int		ret;

	while (lst)
	{
		r = lst->content;
		fd = open_redir(ctx, r);
		if (fd < 0)
			return (0);
		ret = dup2(fd, r->fd);
		if (r->type != R_HEREDOC)
			close(fd);
		if (ret < 0)
			return (error("dup2", strerror(errno)), 0);
		lst = lst->next;
	}
	return (1);
}

/**
 * @brief	Applies the redirections of a command on the current process:
 *			inputs first, then outputs, each list in order of appearance.
 * @return	`1` on success, `0` on failure (error printed).
 */
int	apply_redirs(t_context *ctx, t_cmd *cmd)
{
	if (!apply_list(ctx, cmd->redir_in_lst))
		return (0);
	return (apply_list(ctx, cmd->redir_out_lst));
}

/**
 * @brief	Closes every heredoc descriptor still open. Called in the
 *			children once their redirections are applied.
 */
void	close_heredocs(t_context *ctx)
{
	t_list	*c;
	t_list	*r;
	t_redir	*redir;

	c = ctx->cmd_lst;
	while (c)
	{
		r = ((t_cmd *)c->content)->redir_in_lst;
		while (r)
		{
			redir = r->content;
			if (redir->heredoc_fd >= 0)
			{
				close(redir->heredoc_fd);
				redir->heredoc_fd = -1;
			}
			r = r->next;
		}
		c = c->next;
	}
}
