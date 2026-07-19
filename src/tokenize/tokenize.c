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

int	tk_extract(t_context *ctx, int start, size_t len, int type)
{
	t_token	*tk;
	t_list	*node;

	tk = ft_calloc(1, sizeof(t_token));
	if (!tk || !len || ctx->line_len < start + len)
		return (free(tk), 0);
	tk->type = type;
	tk->val = ft_substr(ctx->line, start, len);
	tk->len = len;
	if (!(tk->val))
		return (free(tk), 0);
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
	while (start + (size_t)len < ctx->line_len)
	{
		if (chr_in_set(ctx->line[start + len], stop_set))
			return (len + 1);
		len++;
	}
	if (start + (size_t)len == ctx->line_len)
		return (len);
	return (0);
}

int	chr_to_tk_type(int c)
{
	if (chr_in_set(c, "\'\"|<>"))
	{
		return (c);
	}
	else
	{
		if (ft_isprint(c))
			return (e_tk_word);
		return (e_tk_null);
	}
}

char	*tk_typename(int type)
{
	if (type == e_tk_null)
		return ("null");
	if (type == e_tk_word)
		return ("word");
	if (type == e_tk_pipe)
		return ("pipe");
	if (type == e_tk_quote)
		return ("quote");
	if (type == e_tk_dquote)
		return ("dquote");
	if (type == e_tk_redir_in)
		return ("redir_in");
	if (type == e_tk_redir_out)
		return ("redir_out");
	if (type == e_tk_append)
		return ("append");
	if (type == e_tk_heredoc)
		return ("heredoc");
	return (NULL);
}

void	tk_print(void *content)
{
	t_token	*tk;

	if (content)
	{
		tk = content;
		ft_putstr_fd("token[", STDOUT_FILENO);
		ft_putstr_fd(tk_typename(tk->type), STDOUT_FILENO);
		ft_putstr_fd("]:", STDOUT_FILENO);
		ft_putstr_fd(tk->val, STDOUT_FILENO);
		ft_putstr_fd("(", STDOUT_FILENO);
		ft_putnbr_fd(tk->len, STDOUT_FILENO);
		ft_putstr_fd(")\n", STDOUT_FILENO);
	}
}

int	tokenize(t_context *ctx)
{
	int	i;
	int	len;
	int	type;

	if (!ctx || !(ctx->line) || !(ctx->line_len))
		return (0);
	i = 0;
	while ((size_t)i < ctx->line_len)
	{
		type = chr_to_tk_type(ctx->line[i]);
		if (type == e_tk_word)
			len = tk_len(ctx, i, "\'\"|<>");
		else
			len = tk_len(ctx, i, "\'")
				+ tk_len(ctx, i, "\"")
				+ tk_len(ctx, i, "|<>");
		if (len && tk_extract(ctx, i, (size_t)len, type))
			i += len;
		i++;
	}
	return (1);
}
