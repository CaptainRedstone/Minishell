/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 14:43:37 by ethrober          #+#    #+#             */
/*   Updated: 2026/10/08 14:43:37 by ethrober         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	parse_token(t_cmd *cmd, t_list **token_lst, char *line)
{
	t_token	*token;

	token = (*token_lst)->content;
	if (token->type == TK_REDIR_IN || token->type == TK_REDIR_OUT)
		return (init_redir(cmd, token_lst, line));
	return (init_argv(cmd, token_lst, line));
}

/**
 * @brief	Builds one command from the tokens up to the next pipe
 *			(or the end), and adds it to ctx->cmd_lst.
 *			token_lst is left on the pipe token (or NULL).
 */
static int	init_cmd(t_context *ctx, t_list **token_lst)
{
	t_cmd	*cmd;
	t_token	*token;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (0);
	cmd->arg_end = -1;
	while (*token_lst)
	{
		token = (*token_lst)->content;
		if (token->type == TK_PIPE)
			break ;
		if (!parse_token(cmd, token_lst, ctx->line))
			return (delete_cmd(cmd), 0);
	}
	ft_lstadd_back(&(ctx->cmd_lst), ft_lstnew(cmd));
	ctx->cmd_cnt++;
	return (1);
}

/**
 * @brief	Checks the syntax then builds ctx->cmd_lst from ctx->token_lst.
 *			The token list is kept (freed by free_line).
 * @return	`1` if there is something to execute, `0` otherwise.
 */
int	init_cmd_lst(t_context *ctx)
{
	t_list	*node;

	if (!ctx->token_lst || !check_syntax(ctx))
		return (0);
	node = ctx->token_lst;
	while (node)
	{
		if (!init_cmd(ctx, &node))
			return (0);
		if (node)
			node = node->next;
	}
	return (1);
}
