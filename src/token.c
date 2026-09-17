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
 * @brief Get token `name` from its `type`.
 * @param type Type of token.
 * @return String with token name.
 */
char	*get_token_name(t_token_t type)
{
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
 * @brief Returns the token type from the first character of
 *  the token string.
 * @param c First character of the token string.
 * @return Token type.
 */
t_token_t	get_token_type(char c)
{
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
 * @param content 
 */
void	print_token(void *content)
{
	t_token	*token;

	if (!content)
		return ;
	token = content;
	printf("%s[%lu:%lu]\n",
		get_token_name(token->type),
		token->start,
		token->start + token->len - 1);
}

/**
 * @brief Computes the length of the input quote.
 * @param token_str Start of token string, includes quote char.
 * @param type Type of quote, single or double.
 * @return Quote length.
 */
size_t	quote_len(char *token_str, t_token_t type)
{
	size_t	i;

	i = 1;
	while (token_str[i] && (type != get_token_type(token_str[i])))
		i++;
	if (type == get_token_type(token_str[i]))
		i++;
	return (i);
}

/**
 * @brief Computes the length of token string with the given type.
 * @param token_str Start of token string.
 * @param type Token type.
 * @return Token length.
 */
size_t	token_len(char *token_str, t_token_t type)
{
	size_t	i;

	i = 0;
	if (!token_str)
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
