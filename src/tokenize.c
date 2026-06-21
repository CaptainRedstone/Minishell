/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aforcada <aforcada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 10:43:09 by aforcada          #+#    #+#             */
/*   Updated: 2026/06/20 16:09:24 by aforcada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/colors.h"
#include "../includes/includes.h"
#include "../includes/minishell.h"
#include "../includes/parser.h"

int	count_tokens(char **arr)
{
	int	count;

	count = 0;
	if (!arr)
		return (count);
	while(arr[count])
		count++;
	return (count);
}

void	free_tokens(t_context *ctx)
{
	int	i;

	i = 0;
	while (i < ctx->tk_count)
	{
		free(ctx->tokens[i].val);
		ctx->tokens[i].val = NULL;
		i++;
	}
	free(ctx->tokens);
	ctx->tokens = NULL;
	ctx->tk_count = 0;
}

void	print_tokens(t_context *ctx)
{
	int		i;

	i = 0;
	while (i < ctx->tk_count)
	{
		printf("token[%d]: %s\n", i, ctx->tokens[i].val);
		i++;
	}
}

int	fill_tokens(t_context *ctx, char **arr)
{
	int		i;

	i = 0;
	while (i < ctx->tk_count)
	{
		if (ft_strncmp(arr[i], "|", 2))
			ctx->tokens[i].type = e_pipe;
		else if (ft_strncmp(arr[i], ">", 2))
			ctx->tokens[i].type = e_right_redir;
		else if (ft_strncmp(arr[i], "<", 2))
			ctx->tokens[i].type = e_left_redir;
		else if (ft_strncmp(arr[i], ">>", 3))
			ctx->tokens[i].type = e_append_redir;
		else if (ft_strncmp(arr[i], "<<", 3))
			ctx->tokens[i].type = e_heredoc;
		else
			ctx->tokens[i].type = e_word;
		ctx->tokens[i].val = ft_strdup(arr[i]);
		i++;
	}
	return (1);
}

int	tokenize(t_context *ctx)
{
	char	**arr;

	arr = ft_split(ctx->line, ' ');
	if (!arr)
		return (0);
	ctx->tk_count = count_tokens(arr);
	if (ctx->tk_count < 1)
		return (free_array(arr), 0);
	ctx->tokens = malloc(ctx->tk_count * sizeof(t_token));
	if (!(ctx->tokens))
		return (free_array(arr), 0);
	if (!fill_tokens(ctx, arr))
		return (free_array(arr), 0);
	return (free_array(arr), 1);
}
