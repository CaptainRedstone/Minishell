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

#include "../includes/tokenize.h"

t_token	*build_token_at(char *line, size_t index)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = get_token_type(line[index]);
	token->pos = index;
	token->len = token_len(&line[index], token->type);
	return (token);
}

int	tokenize(t_context *ctx)
{
	size_t	index;
	t_token	*token;
	t_list	*node;

	index = 0;
	while (index < ctx->line_len)
	{
		token = build_token_at(ctx->line, index);
		if (!token)
			return (0);
		node = ft_lstnew((void *)token);
		if (!(ctx->token_lst))
			ctx->token_lst = node;
		else
			ft_lstadd_back(&(ctx->token_lst), node);
		if (!(token->len))
			break ;
		index += token->len;
	}
	return (0);
}
