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

int	valid_pipes(t_list *token_lst)
{
	t_token	*token;

	if (!token_lst || !(token_lst->content))
		return (0);
	token = token_lst->content;
	if (token->type == TK_PIPE)
		return (0);
	while (token_lst && token_lst->next)
	{
		token = token_lst->content;
		if (token->type == TK_PIPE)
		{
			token = token_lst->next->content;
			if (token->type == TK_PIPE)
				return (0);
		}
		token_lst = token_lst->next;
	}
	return (1);
}

int	valid_redir_syntax(t_list *token_lst)
{
	t_token	*token;

	if (!token_lst || !(token_lst->next))
		return (0);
	
	token = token_lst->content;
	if (token->type == TK_REDIR_IN || token->type == TK_REDIR_OUT)
	{
		token = token_lst->next->content;
		if (token->type == TK_PIPE
			|| token->type == TK_REDIR_IN || token->type == TK_REDIR_OUT)
			return (0);
	}
	return (1);
}

int	count_cmd_args(t_list *token_lst)
{
	int		count;
	t_token	*token;

	count = 0;
	while (token_lst)
	{
		token = token_lst->content;
		if (token->type == TK_PIPE)
			return (count);
		token_lst = token_lst->next;
		count++;
	}
	return (count);
}
