/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 14:43:21 by ethrober          #+#    #+#             */
/*   Updated: 2026/10/08 14:43:21 by ethrober         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief	Prints a bash-like syntax error. tk == NULL means "newline".
 */
static int	syntax_error(t_context *ctx, t_token *tk)
{
	ft_putstr_fd(BRED "MiniShell" BWHITE " > " BRED "syntax error", 2);
	ft_putstr_fd(BWHITE " > " BRED "near unexpected token `", 2);
	if (!tk)
		ft_putstr_fd("newline", 2);
	else
		write(2, ctx->line + tk->start, tk->len);
	ft_putstr_fd("'\n" RESET, 2);
	ctx->exit_status = 2;
	return (0);
}

static int	quote_ok(t_context *ctx, t_token *tk)
{
	char	*q;

	if (tk->type != TK_SQUOTE && tk->type != TK_DQUOTE)
		return (1);
	q = ctx->line + tk->start;
	if (tk->len >= 2 && q[tk->len - 1] == q[0])
		return (1);
	error("syntax error", "unclosed quote");
	ctx->exit_status = 2;
	return (0);
}

static int	pipe_ok(t_context *ctx, t_list *node, t_list *prev)
{
	t_token	*next;

	if (((t_token *)node->content)->type != TK_PIPE)
		return (1);
	if (!prev)
		return (syntax_error(ctx, node->content));
	if (!node->next)
		return (syntax_error(ctx, NULL));
	next = node->next->content;
	if (next->type == TK_PIPE)
		return (syntax_error(ctx, next));
	return (1);
}

static int	redir_ok(t_context *ctx, t_list *node)
{
	t_token	*tk;

	tk = node->content;
	if (tk->type != TK_REDIR_IN && tk->type != TK_REDIR_OUT)
		return (1);
	if (valid_redir_syntax(node))
		return (1);
	if (!node->next)
		return (syntax_error(ctx, NULL));
	if (tk->len > 2)
		return (syntax_error(ctx, tk));
	return (syntax_error(ctx, node->next->content));
}

/**
 * @brief	Checks the whole token list before building the commands:
 *			closed quotes, pipes and redirections well placed.
 * @return	1 if valid, 0 otherwise (error printed, status set to 2).
 */
int	check_syntax(t_context *ctx)
{
	t_list	*node;
	t_list	*prev;

	prev = NULL;
	node = ctx->token_lst;
	while (node)
	{
		if (!quote_ok(ctx, node->content) || !pipe_ok(ctx, node, prev)
			|| !redir_ok(ctx, node))
			return (0);
		prev = node;
		node = node->next;
	}
	return (1);
}
