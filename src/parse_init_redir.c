/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aforcada <aforcada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 13:01:46 by aforcada          #+#    #+#             */
/*   Updated: 2026/09/16 13:07:30 by aforcada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	set_redir_val(t_redir *redir, t_token *token, char *line)
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

static int	set_redir_mode(t_redir *redir)
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

static int	set_redir_type(t_redir *redir, t_token *token)
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

int	init_redir(t_cmd *cmd, t_list **token_lst, char *line)
{
	t_redir	*redir;
	t_token	*token;

	if (!valid_redir_syntax((*token_lst)))
		return (0);
	redir = ft_calloc(1, sizeof(t_redir));
	token = (*token_lst)->content;
	if (redir && token->type == TK_REDIR_OUT)
		redir->fd = 1;
	set_redir_type(redir, token);
	set_redir_mode(redir);
	set_redir_val(redir, (*token_lst)->next->content, line);
	if (!redir)
		return (0);
	ft_lstadd_back(&(cmd->redir_lst), ft_lstnew(redir));
	cmd->redir_cnt++;
	*token_lst = (*token_lst)->next->next;
	return (1);
}
