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
		if (2 < token->len)
			return (0);
		token = token_lst->next->content;
		if (token->type == TK_PIPE
			|| token->type == TK_REDIR_IN || token->type == TK_REDIR_OUT)
			return (0);
	}
	return (1);
}

int	set_redir_val(t_redir *redir, t_token *token, char *line)
{
	if (!redir || !line)
		return (0);
	if (redir->type == R_HEREDOC)
		redir->val.delim = ft_substr(line, token->start, token->len);
	else
		redir->val.path = ft_substr(line, token->start, token->len);
	if (redir->val.path || redir->val.delim)
		return (1);
	return (0);
}

int	set_redir_mode(t_redir *redir)
{
	if (!redir)
		return (0);
	if (redir->type == R_IN)
		redir->mode = O_RDONLY;
	if (redir->type == R_OUT)
		redir->mode = O_WRONLY | O_CREAT | O_TRUNC;
	if (redir->type == R_APPEND)
		redir->mode = O_WRONLY | O_CREAT | O_APPEND;
	if (redir->type == R_HEREDOC)
		redir->mode = O_RDONLY;
	return (1);
}

int	set_redir_type(t_redir *redir, t_token *token)
{
	if (!redir)
		return (0);
	if (token->type == TK_REDIR_IN && token->len == 1)
		redir->type = R_IN;
	if (token->type == TK_REDIR_OUT && token->len == 1)
		redir->type = R_OUT;
	if (token->type == TK_REDIR_IN && token->len == 2)
		redir->type = R_APPEND;
	if (token->type == TK_REDIR_OUT && token->len == 2)
		redir->type = R_HEREDOC;
	return (1);
}
