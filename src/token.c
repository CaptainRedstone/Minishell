/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aforcada <aforcada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 10:43:09 by aforcada          #+#    #+#             */
/*   Updated: 2026/08/29 18:47:38 by aforcada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"

char	*get_token_name(int type)
{
	if (type == TK_NULL)
		return (TK_NULL_NAME);
	if (type == TK_BLANK)
		return (TK_BLANK_NAME);
	if (type == TK_SQUOTE)
		return (TK_SQUOTE_NAME);
	if (type == TK_DQUOTE)
		return (TK_DQUOTE_NAME);
	if (type == TK_PIPE)
		return (TK_PIPE_NAME);
	if (type == TK_REDIR_IN)
		return (TK_REDIR_IN_NAME);
	if (type == TK_REDIR_OUT)
		return (TK_REDIR_OUT_NAME);
	if (type == TK_WORD)
		return (TK_WORD_NAME);
	return (NULL);
}

int	get_token_type(char c)
{
	if (c == TK_NULL_VAL)
		return (TK_NULL);
	if (c == TK_TAB_VAL || c == TK_SPACE_VAL)
		return (TK_BLANK);
	if (c == TK_SQUOTE_VAL)
		return (TK_SQUOTE);
	if (c == TK_DQUOTE_VAL)
		return (TK_DQUOTE);
	if (c == TK_PIPE_VAL)
		return (TK_PIPE);
	if (c == TK_REDIR_IN_VAL)
		return (TK_REDIR_IN);
	if (c == TK_REDIR_OUT_VAL)
		return (TK_REDIR_OUT);
	return (TK_WORD);
}

void	print_token(void *content)
{
	t_token	*token;

	token = content;
	if (!token)
		return ;
	ft_putstr_fd(get_token_name(token->type), STDOUT_FILENO);
	ft_putchar_fd('[', STDOUT_FILENO);
	ft_putnbr_fd(token->pos, STDOUT_FILENO);
	ft_putchar_fd(':', STDOUT_FILENO);
	ft_putnbr_fd(token->pos + token->len - 1, STDOUT_FILENO);
	ft_putchar_fd(']', STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

size_t	quote_len(char *line, int type)
{
	size_t	i;

	i = 1;
	while (line[i] && (type != get_token_type(line[i])))
		i++;
	if (type == get_token_type(line[i]))
		i++;
	return (i);
}

size_t	token_len(char *line, int type)
{
	size_t	i;

	i = 0;
	if (type == TK_NULL)
		return (0);
	if (type == TK_PIPE)
		return (1);
	if (type == TK_BLANK || type == TK_REDIR_IN || type == TK_REDIR_OUT)
	{
		while (line[i] && type == get_token_type(line[i]))
			i++;
	}
	if (type == TK_SQUOTE || type == TK_DQUOTE)
		i = quote_len(line, type);
	if (type == TK_WORD)
	{
		while (line[i] && !(ft_strchr(TK_METACHARS, line[i])))
			i++;
	}
	return (i);
}
