/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aforcada <aforcada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 16:09:39 by aforcada          #+#    #+#             */
/*   Updated: 2026/09/10 06:55:55 by aforcada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	valid_redirs_syntax(t_list *token_lst)
{
	t_token	*token;

	if (!token_lst)
		return (0);
	while (token_lst && token_lst->next)
	{
		token = token_lst->content;
		if (token->type == TK_REDIR_IN || token->type == TK_REDIR_OUT)
		{
			token_lst = token_lst->next;
			token = token_lst->content;
			if (token->type != TK_WORD)
				return (0);
		}
		token_lst = token_lst->next;
	}
	return (1);
}

int	count_tokens_upto(t_list *token_lst, int token_type)
{
	t_token	*token;
	int		count;

	count = 0;
	if (!token_lst)
		return (0);
	token = token_lst->content;
	while (token_lst && token->type != token_type)
	{
		token_lst = token_lst->next;
		if (token_lst)
			token = token_lst->content;
		count++;
	}
	if (token_lst && token->type == token_type)
		return (count + 1);
	return (count);
}

int	count_cmd_args(t_list *token_lst)
{
	t_token	*token;
	int		count;

	count = 0;
	if (!token_lst)
		return (0);
	while (token_lst)
	{
		token = token_lst->content;
		if (token->type == TK_WORD)
			count++;
		if (token->type == TK_SQUOTE || token->type == TK_DQUOTE)
			count++;
		if (token->type == TK_REDIR_IN || token->type == TK_REDIR_OUT)
			token_lst = token_lst->next;
		token_lst = token_lst->next;
	}
	return (count);
}
