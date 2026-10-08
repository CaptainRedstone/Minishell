/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 14:51:34 by ethrober          #+#    #+#             */
/*   Updated: 2026/10/08 14:51:34 by ethrober         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	delete_arg(void *content)
{
	t_word	*word;

	word = content;
	if (!word)
		return ;
	free(word->str);
	free(word);
}

void	delete_redir(void *content)
{
	t_redir	*redir;

	redir = content;
	if (!redir)
		return ;
	if (redir->heredoc_fd >= 0)
		close(redir->heredoc_fd);
	free(redir->val.path);
	free(redir);
}

void	delete_cmd(void *content)
{
	t_cmd	*cmd;

	cmd = content;
	if (!cmd)
		return ;
	ft_lstclear(&cmd->argv, &delete_arg);
	ft_lstclear(&cmd->redir_in_lst, &delete_redir);
	ft_lstclear(&cmd->redir_out_lst, &delete_redir);
	free(cmd->av);
	free(cmd);
}

/**
 * @brief	Frees everything allocated for the current command line.
 */
void	free_line(t_context *ctx)
{
	ft_lstclear(&ctx->cmd_lst, &delete_cmd);
	ft_lstclear(&ctx->token_lst, &delete_token);
	free(ctx->line);
	free(ctx->prompt);
	ctx->line = NULL;
	ctx->prompt = NULL;
	ctx->line_len = 0;
	ctx->token_cnt = 0;
	ctx->cmd_cnt = 0;
}
