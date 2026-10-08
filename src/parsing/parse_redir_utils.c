/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 14:43:28 by ethrober          #+#    #+#             */
/*   Updated: 2026/10/08 14:43:28 by ethrober         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	add_redir(t_cmd *cmd, t_redir *redir, t_token *token)
{
	t_list	*node;

	node = ft_lstnew(redir);
	if (!node)
		return (0);
	if (token->type == TK_REDIR_IN)
		ft_lstadd_back(&(cmd->redir_in_lst), node);
	else
		ft_lstadd_back(&(cmd->redir_out_lst), node);
	cmd->redir_cnt++;
	return (1);
}

/**
 * @brief	Tokens that touch the redirection target belong to it
 *			(> "a"b is the file ab). They are appended to the raw value.
 * @param	node Last token of the target, moved on the last absorbed one.
 */
int	absorb_adjacent(t_redir *redir, t_list **node, char *line)
{
	t_token	*prev;
	t_token	*next;
	char	*part;

	while ((*node)->next)
	{
		prev = (*node)->content;
		next = (*node)->next->content;
		if (next->type == TK_PIPE || next->type == TK_REDIR_IN
			|| next->type == TK_REDIR_OUT
			|| next->start != prev->start + prev->len)
			break ;
		part = ft_substr(line, next->start, next->len);
		redir->val.path = join_and_free(redir->val.path, part);
		free(part);
		if (!redir->val.path)
			return (0);
		*node = (*node)->next;
	}
	return (1);
}
