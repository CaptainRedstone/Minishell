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
 * @brief	Free and set input token to NULL.
 * @param	token
 */
void	delete_token(void *token)
{
	free(token);
	token = NULL;
};

/**
 * @brief	Appends token to the token list in context.
 * @param	ctx Context with token list (list can be empty).
 * @param	token Added to the back of the list.
 */
void	token_lst_add_back(t_context *ctx, t_token *token)
{
	t_list	*node;

	if (!ctx || !token)
		return ;
	node = ft_lstnew((void *)token);
	ft_lstadd_back(&(ctx->token_lst), node);
	ctx->token_cnt++;
}

/**
 * @brief Builds token from line string starting from given position.
 * Allocates a `token` with type, starting position, and 
 * computed length.
 * @param line input string to build token from
 * @param token_start starting position of token
 * @return token
 */
t_token	*build_token_from(char *line, size_t token_start)
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
 * @brief Builds tokens from line, storing them in context.
 * @param ctx Context holding line string and empty token list.
 * @return `1` on success, `0` on failure.
 */
int	tokenize(t_context *ctx)
{
	size_t	idx;
	t_token	*token;

	idx = 0;
	while (idx < ctx->line_len)
	{
		token = build_token_from(ctx->line, idx);
		if (!(token) || !(token->len))
			break ;
		if (token->type != TK_BLANK)
			token_lst_add_back(ctx, token);
		idx += token->len;
		if (token->type == TK_BLANK)
			delete_token(token);
	}
	if (idx < ctx->line_len)
		return (ft_lstclear(&(ctx->token_lst), &delete_token),
			delete_token(token), 0);
	return (1);
}
