/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aforcada <aforcada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 16:12:50 by aforcada          #+#    #+#             */
/*   Updated: 2026/09/02 17:11:33 by aforcada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// TODO: tester
t_token	*get_token_at(void *placeholder, int idx, int cast_type)
{
	t_list	*token_lst_node;

	token_lst_node = NULL;
	if (idx < 0 && cast_type != T_CONTEXT_TYPE && cast_type != T_CMD_TYPE)
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

// TODO: split cmd
int	valid_pipe(t_context *ctx, int pipe_idx)
{
	if (pipe_idx == 0)
		return (0);
	ctx->current_token = get_token_at(ctx, pipe_idx + 1, T_CONTEXT_TYPE);
	if (!(ctx->current_token) || (ctx->current_token->type == TK_PIPE))
		return (0);
	return (1);
}

int	init_cmd_lst(t_context *ctx)
{
	int	idx;

	idx = 0;
	while (valid_pipe(ctx, idx))
		idx++;
	return (idx);
}
// // TODO: check path exist
// int	check_redir(t_context *ctx, int redir_idx)
// {
// 	ctx->current_token = get_token_at(ctx, redir_idx, );
// 	if (2 < ctx->current_token->len)
// 		return (0);
// 	ctx->current_token = get_token_at(ctx, redir_idx + 1);
// 	if (ctx->current_token && ctx->current_token->type != TK_WORD)
// 		return (0);
// 	return (1);
// }
