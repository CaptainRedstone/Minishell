/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aforcada <aforcada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 10:43:09 by aforcada          #+#    #+#             */
/*   Updated: 2026/07/14 17:59:40 by aforcada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/colors.h"
#include "../includes/includes.h"
#include "../includes/minishell.h"
#include "../includes/parser.h"


t_list	*extract_token(t_context *ctx,
	int tk_start, size_t tk_end, int tk_type)
{
	t_token	*tk;
	t_list	*node;

	tk = ft_calloc(1, sizeof(t_token));
	if (!tk || tk_end <= (size_t)tk_start)
		return (free(tk), NULL);
	tk->type = tk_type;
	tk->val = ft_substr(ctx->line, tk_start, (tk_end - tk_start + 1));
	if (!(tk->val))
		return (free(tk), NULL);
	node = ft_lstnew(tk);
	if (!node)
		return (free(tk->val), free(tk), NULL);
	return (node);
}

int	handle_quote(t_context *ctx, int qi, int qtype)
{
	int		i;
	t_list	*node;

	i = 1;
	while ((size_t)i + qi < ctx->line_len && ctx->line[i + qi] != qtype)
		i++;
	if (ctx->line_len <= (size_t)i + qi)
		return (-1);
	node = extract_token(ctx, qi, (size_t)i + qi, qtype);
	if (!node)
		return (-1);
	ft_lstadd_back(&(ctx->token_lst), node);
	ctx->token_cnt++;
	return (i);
}

int handle_token(t_context *ctx, int tk_i, int tk_type)
{
	t_list	*node;

	node = extract_token(ctx, tk_i, tk_i + (size_t)1, tk_type);
	if (!node)
		return (-1);
	ft_lstadd_back(&(ctx->token_lst), node);
	ctx->token_cnt++;
	return (1);
}

int	tokenize(t_context *ctx)
{
	int	i;
	int	step;

	if (!ctx || !(ctx->line))
		return (0);
	i = 0;
	while ((size_t)i < ctx->line_len)
	{
		step = 0;
		if (ctx->line[i] == e_tk_quote)
			step = handle_quote(ctx, i, e_tk_quote);
		if (ctx->line[i] == e_tk_dquote)
			step = handle_quote(ctx, i, e_tk_dquote);
		if (ctx->line[i] == e_tk_pipe)
			step = handle_token(ctx, i, e_tk_pipe);
		if (ctx->line[i] == e_tk_r_redir)
			step = handle_token(ctx, i, e_tk_r_redir);
		if (ctx->line[i] == e_tk_l_redir)
			step = handle_token(ctx, i, e_tk_l_redir);
		if (step < 0)
			return (0);
		i += step;
	}
	return (1);
}
