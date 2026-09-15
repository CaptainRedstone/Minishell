/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aforcada <aforcada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 16:12:50 by aforcada          #+#    #+#             */
/*   Updated: 2026/09/10 07:06:26 by aforcada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_cmd_lst(t_context *ctx)
{
	t_cmd	*cmd;

	if (!ctx || !(ctx->token_lst) || !valid_pipes(ctx->token_lst))
		return (0);
	while (ctx->token_lst)
	{
		printf("ctx.token_cnt=%d\n", ctx->token_cnt);
		cmd = ft_calloc(1, sizeof(t_cmd));
		if (!cmd)
			return (0);
		cmd->token_cnt = count_tokens_upto(ctx->token_lst, TK_PIPE);
		cmd->token_lst = ft_sublst(&(ctx->token_lst), 0, cmd->token_cnt);
		if (cmd->token_lst)
		{
			ctx->token_cnt -= cmd->token_cnt;
			ft_lstadd_back(&(ctx->cmd_lst), ft_lstnew(cmd));
			ctx->cmd_cnt++;
		}
	}
	return (1);
}
