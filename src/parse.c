/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aforcada <aforcada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 16:12:50 by aforcada          #+#    #+#             */
/*   Updated: 2026/09/09 16:09:46 by aforcada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// TODO: tester
t_token	*get_token_at(void *placeholder, int idx, int cast_type)
{
	t_list	*token_lst_node;

	token_lst_node = NULL;
	if (idx < 0 || !(cast_type == T_CONTEXT_TYPE || cast_type == T_CMD_TYPE))
		return (NULL);
	if (cast_type == T_CONTEXT_TYPE)
		token_lst_node = ((t_context *)placeholder)->token_lst;
	if (cast_type == T_CMD_TYPE)
		token_lst_node = ((t_cmd *)placeholder)->token_lst;
	while (idx-- && token_lst_node)
		token_lst_node = token_lst_node->next;
	if (!token_lst_node)
		return (NULL);
	return (token_lst_node->content);
}

int	valid_pipes(t_list *token_lst)
{
	t_token	*token;

	token = token_lst->content;
	if (!token || token->type == TK_PIPE)
		return (0);
	while (token_lst->next)
	{
		if (token->type == TK_PIPE)
		{
			token_lst = token_lst->next;
			token = token_lst->content;
			if (token->type == TK_PIPE)
				return (0);
		}
		token_lst = token_lst->next;
		token = token_lst->content;
	}
	return (1);
}

int	init_cmd_lst(t_context *ctx)
{
	t_cmd	*cmd;

	if (!ctx || !(ctx->token_lst) || !valid_pipes(ctx->token_lst))
		return (0);
	while (ctx->token_lst)
	{
		cmd = ft_calloc(1, sizeof(t_cmd));
		if (!cmd)
			return (0);
		cmd->token_lst_len = count_tokens_upto(ctx->token_lst, TK_PIPE);
		cmd->token_lst = ft_sublst(&(ctx->token_lst), 0, cmd->token_lst_len);
		ctx->token_lst_len -= cmd->token_lst_len;
		ft_lstadd_back(&(ctx->cmd_lst), ft_lstnew(cmd));
	}
	return (1);
}
