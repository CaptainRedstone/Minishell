/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aforcada <aforcada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 16:12:50 by aforcada          #+#    #+#             */
/*   Updated: 2026/09/16 14:22:44 by aforcada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	init_argv(t_cmd *cmd, t_list **token_lst, char *line)
// {
// 	t_token *token;
// 	t_word	*word;

// 	token = (*token_lst)->content;
// 	word = ft_calloc(1, sizeof(t_word));
// 	word->flags =
// 	if (!(cmd->argv))
// 		word->flags =
// }

int	init_cmd(t_context *ctx, t_list **token_lst)
{
	t_cmd	*cmd;
	t_token	*token;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (0);
	while (*token_lst)
	{
		token = (*token_lst)->content;
		if (token->type == TK_REDIR_IN || token->type == TK_REDIR_OUT)
			init_redir(cmd, token_lst, ctx->line);
		else if (token->type != TK_PIPE)
		{
			ft_lstadd_back(&(cmd->argv), ft_lstnew(token));
			cmd->argc++;
			*token_lst = (*token_lst)->next;
		}
		else
			break ;
	}
	if (cmd->argc || cmd->redir_cnt)
	{
		ft_lstadd_back(&(ctx->cmd_lst), ft_lstnew(cmd));
		ctx->cmd_cnt++;
		return (1);
	}
	return (free(cmd), 0);
}

int	init_cmd_lst(t_context *ctx)
{
	if (!ctx || !(ctx->token_lst) || !valid_pipes(ctx->token_lst))
		return (0);
	while (ctx->token_lst)
	{
		init_cmd(ctx, &(ctx->token_lst));
		if (ctx->token_lst)
			ctx->token_lst = ctx->token_lst->next;
	}
	ft_lstiter(ctx->cmd_lst, &print_cmd);
	return (1);
}
