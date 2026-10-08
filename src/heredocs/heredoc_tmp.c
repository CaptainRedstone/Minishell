/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 14:45:30 by ethrober          #+#    #+#             */
/*   Updated: 2026/10/08 14:45:30 by ethrober         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*tmp_name(t_context *ctx)
{
	char	*num;
	char	*name;

	num = ft_itoa(ctx->heredoc_cnt);
	ctx->heredoc_cnt++;
	name = NULL;
	if (num)
		name = ft_strjoin("/tmp/.minishell_hd_", num);
	free(num);
	return (name);
}

/**
 * @brief	Creates a temporary file in /tmp, opens it for writing (return
 *			value) and for reading (*rfd), then unlinks it: the file lives
 *			as long as the descriptors are open.
 */
int	open_tmp(t_context *ctx, int *rfd)
{
	char	*name;
	int		wfd;

	name = tmp_name(ctx);
	wfd = -1;
	while (name)
	{
		wfd = open(name, O_WRONLY | O_CREAT | O_EXCL, 0600);
		if (wfd >= 0 || errno != EEXIST)
			break ;
		free(name);
		name = tmp_name(ctx);
	}
	*rfd = -1;
	if (wfd >= 0)
		*rfd = open(name, O_RDONLY);
	if (wfd >= 0)
		unlink(name);
	free(name);
	return (wfd);
}

int	tmp_fail(int wfd, int rfd)
{
	error("heredoc", strerror(errno));
	if (wfd >= 0)
		close(wfd);
	if (rfd >= 0)
		close(rfd);
	return (0);
}
