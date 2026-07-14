/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aforcada <aforcada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 10:43:09 by aforcada          #+#    #+#             */
/*   Updated: 2026/07/14 14:20:58 by aforcada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/colors.h"
#include "../includes/includes.h"
#include "../includes/minishell.h"
#include "../includes/parser.h"

void	append_token(t_context *ctx, int tk_start, int tk_end, int tk_type)
{
	t_token	*tk;
	t_list	*new;

	tk = ft_calloc(1, sizeof(t_token));
	if (!tk || tk_end <= tk_start)
		return ;
	tk->type = tk_type;
	tk->val = ft_substr(ctx->line, tk_start, (tk_end - tk_start + 1));
	new = ft_lstnew(tk);
	if (!new)
		free(tk);
	else
	{
		if (!(ctx->token_lst))
			ft_lstadd_back(&(ctx->token_lst), new);
	}
}

int	handle_quote(t_context *ctx, int quote_idx)
{
	int	i;

	if (!ctx || !(ctx->line))
		return (-1);
	i = 1;
	while (i + quote_idx < ctx->line_len)
	{
		if (ctx->line[i + quote_idx] == e_tk_quote)
			break ;
		i++;
	}
	if (i + quote_idx < ctx->line_len)

	return (-1);
}

int	tokenize(t_context *ctx)
{
	int	i;
	int	step;

	if (!ctx || !(ctx->line))
		return (0);
	i = 0;
	while (i < ctx->line_len)
	{
		step = 0;
		if (ctx->line[i] == e_tk_quote)
			step = handle_quote(ctx, i);
		if (ctx->line[i] == e_tk_dquote)
			step = handle_dquote(ctx, i);
		if (ctx->line[i] == e_tk_r_redir || ctx->line[i] == e_tk_l_redir)
			step = 1;
		i += step;
	}
}
