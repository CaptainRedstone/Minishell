/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aforcada <aforcada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 10:43:09 by aforcada          #+#    #+#             */
/*   Updated: 2026/07/15 17:04:27 by aforcada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/colors.h"
#include "../includes/includes.h"
#include "../includes/minishell.h"
#include "../includes/parser.h"

static int	chr_in_set(int c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	tk_extract(t_context *ctx,
	int start, size_t len, int type)
{
	t_token	*tk;
	t_list	*node;

	tk = ft_calloc(1, sizeof(t_token));
	if (!tk || !len || ctx->line_len < start + len)
		return (free(tk), NULL);
	tk->type = type;
	tk->val = ft_substr(ctx->line, start, len);
	tk->len = len;
	if (!(tk->val))
		return (free(tk), NULL);
	node = ft_lstnew(tk);
	if (!node)
		return (free(tk->val), free(tk), 0);
	ft_lstadd_back(&(ctx->token_lst), node);
	ctx->token_cnt++;
	return (1);
}

int	tk_len(t_context *ctx, int start, const char *stop_set)
{
	int		len;

	len = 0;
	if (chr_in_set(ctx->line[start], "\'\""))
		len++;
	while(start + (size_t)len < ctx->line_len)
	{
		if (chr_in_set(ctx->line[start + len], stop_set))
			return (len + 1);
		len++;
	}
	if (start + (size_t)len == ctx->line_len)
		return (len);
	return (0);
}

int	tokenize(t_context *ctx)
{
	int		i;
	int		len;
	t_list	*node;

	if (!ctx || !(ctx->line) || !(ctx->line_len))
		return (0);
	i = 0;
	node = NULL;
	while ((size_t)i < ctx->line_len)
	{
		if (!chr_in_set(ctx->line[i], "\'\"|<>"))
			len = tk_len(ctx, i, "\'\"|<>");
		else
			len = tk_len(ctx, i, "\'")
				+ tk_len(ctx, i, "\"")
				+ tk_len(ctx, i, "|<>");
		node = tk_extract(ctx, i, len, );
		if (len && tk_append(ctx, i, len, ctx->line[i]))
			i += len;
		i++;
	}
	return (1);
}
