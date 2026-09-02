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

#include "../minishell.h"

/**
 * @brief Get token `name` from its `type` as in `e_token_type`.
 */
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

/**
 * @brief Get token `type` as in `e_token_type` from first token value `c`.
 */
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

/**
 * @brief Print token
 */
void	print_token(void *content)
{
	t_token	*token;

	token = content;
	if (!token)
		return ;
	printf("%s[%lu:%lu]\n",
		get_token_name(token->type),
		token->start,
		token->start + token->len - 1);
}

/**
 * @brief Assuming `line` starts w/ quote of type `TK_SQUOTE` or `TK_DQUOTE`,
 * compute length of quote.
 * @attention Includes quote char
 */
size_t	quote_len(char *token_str, int token_type)
{
	size_t	i;

	i = 1;
	while (token_str[i] && (token_type != get_token_type(token_str[i])))
		i++;
	if (token_type == get_token_type(token_str[i]))
		i++;
	else
		return (0);
	return (i);
}

/**
 * @brief Assuming `line` starts w/ token of `type` in `e_token_type`, 
 * compute length of token.
 */
size_t	token_len(char *token_str, int type)
{
	size_t	i;

	i = 0;
	if (type == TK_NULL)
		return (0);
	if (type == TK_PIPE)
		return (1);
	if (type == TK_BLANK || type == TK_REDIR_IN || type == TK_REDIR_OUT)
	{
		while (token_str[i] && type == get_token_type(token_str[i]))
			i++;
	}
	if (type == TK_SQUOTE || type == TK_DQUOTE)
		i = quote_len(token_str, type);
	if (type == TK_WORD)
	{
		while (token_str[i] && !(ft_strchr(TK_METACHARS, token_str[i])))
			i++;
	}
	return (i);
}
