/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 10:00:00 by ethrober          #+#    #+#             */
/*   Updated: 2026/10/03 10:00:00 by ethrober         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	if (!redir || !token)
		return (0);
	if (token->type == TK_REDIR_IN && token->len == 1)
		redir->type = R_IN;
	if (token->type == TK_REDIR_OUT && token->len == 1)
		redir->type = R_OUT;
	if (token->type == TK_REDIR_IN && token->len == 2)
		redir->type = R_HEREDOC;
	if (token->type == TK_REDIR_OUT && token->len == 2)
		redir->type = R_APPEND;
	return (1);
}

/**
 * @brief Builds a redirection in the appropriate field
 *  in the command structure
 * @param cmd Command structure with in AND out redirection lists
 * @param token_lst First 2 tokens have the redirection data
 * @param line String with redirection value
 * @return `1` on success, `0` on failure
 */
int	init_redir(t_cmd *cmd, t_list **token_lst, char *line)
{
	t_redir	*redir;
	t_token	*token;
	t_list	*target;

	if (!valid_redir_syntax((*token_lst)))
		return (0);
	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return (0);
	token = (*token_lst)->content;
	redir->heredoc_fd = -1;
	if (token->type == TK_REDIR_OUT)
		redir->fd = 1;
	set_redir_type(redir, token);
	set_redir_mode(redir);
	target = (*token_lst)->next;
	if (!set_redir_val(redir, target->content, line)
		|| !absorb_adjacent(redir, &target, line)
		|| !add_redir(cmd, redir, token))
		return (delete_redir(redir), 0);
	cmd->arg_end = -1;
	*token_lst = target->next;
	return (1);
}
