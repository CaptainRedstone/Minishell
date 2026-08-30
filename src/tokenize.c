/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aforcada <aforcada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 10:43:09 by aforcada          #+#    #+#             */
/*   Updated: 2026/08/29 19:13:25 by aforcada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief	Appends token to token list.
 */
void	token_lst_add_back(t_list **token_lst, t_token *token)
{
	t_list	*node;

	if (!token_lst || !token)
		return ;
	node = ft_lstnew((void *)token);
	if ((*token_lst) == NULL)
		*token_lst = node;
	else
		ft_lstadd_back(token_lst, node);
}

/**
 * @brief Assumes `line` at `index` is the start of a `token_str`.
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
 * @brief Assumes context `ctx` has `line` and `line_len` initialized.
 * extract a list of tokens from line.
 * @return 1 on success, 0 on failure.
 */
int	tokenize(t_context *ctx)
{
	size_t	index;
	t_token	*token;

	index = 0;
	while (index < ctx->line_len)
	{
		token = build_token_at(ctx->line, index);
		token_lst_add_back(&(ctx->token_lst), token);
		if (!token || token->len == 0)
			break ;
		index += token->len;
	}
	return (1);
}
