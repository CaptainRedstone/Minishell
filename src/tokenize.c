/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aforcada <aforcada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 10:43:09 by aforcada          #+#    #+#             */
/*   Updated: 2026/09/02 17:01:51 by aforcada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief	Since fields of the token structure DONT need allocated memory,
 * this function does nothing.
 */
void	delete_token(void *token)
{
	(void)token;
};

/**
 * @brief	Appends token to the token list held by context.
 */
void	token_lst_add_back(t_context *ctx, t_token *token)
{
	t_list	*node;

	if (!ctx || !token)
		return ;
	node = ft_lstnew((void *)token);
	if (!(ctx->token_lst))
		ctx->token_lst = node;
	else
		ft_lstadd_back(&(ctx->token_lst), node);
	ctx->token_lst_len++;
}

/**
 * @brief Builds a token from char(s) in line starting at token_start.
 * Creates a memory allocated `token` from type, position, and length`token_str`.
 */
t_token	*build_token_at(char *line, size_t token_start)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = get_token_type(line[token_start]);
	token->start = token_start;
	token->len = token_len(&line[token_start], token->type);
	return (token);
}

/**
 * @brief Assumes `ctx` has `line` and `line_len` set.
 * Builds tokens from `line` and stores them in `ctx->token_lst`.
 * @return 1 on success, 0 on failure.
 */
int	tokenize(t_context *ctx)
{
	size_t	idx;

	idx = 0;
	while (idx < ctx->line_len)
	{
		ctx->current_token = build_token_at(ctx->line, idx);
		if (!(ctx->current_token) || !(ctx->current_token->len))
			break ;
		if (ctx->current_token->type != TK_BLANK)
			token_lst_add_back(ctx, ctx->current_token);
		idx += ctx->current_token->len;
		if (ctx->current_token->type == TK_BLANK)
			free(ctx->current_token);
	}
	if (idx < ctx->line_len)
		return (ft_lstclear(&(ctx->token_lst), delete_token), 0);
	return (1);
}
