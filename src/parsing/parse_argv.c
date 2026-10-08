/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 14:43:15 by ethrober          #+#    #+#             */
/*   Updated: 2026/10/08 14:43:15 by ethrober         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief	The token touches the previous word (e.g. "a"b): the raw text
 *			is appended to the last word. Quotes are kept, they are
 *			removed later by the expansion.
 */
static int	merge_word(t_cmd *cmd, t_token *tk, char *line)
{
	t_word	*last;
	char	*part;
	char	*joined;

	last = ft_lstlast(cmd->argv)->content;
	part = ft_substr(line, tk->start, tk->len);
	if (!part)
		return (0);
	joined = ft_strjoin(last->str, part);
	free(part);
	if (!joined)
		return (0);
	free(last->str);
	last->str = joined;
	return (1);
}

static int	new_word(t_cmd *cmd, t_token *tk, char *line)
{
	t_word	*word;
	t_list	*node;

	word = ft_calloc(1, sizeof(t_word));
	if (!word)
		return (0);
	word->str = ft_substr(line, tk->start, tk->len);
	node = ft_lstnew(word);
	if (!word->str || !node)
		return (free(word->str), free(word), free(node), 0);
	word->flags = W_WORD;
	if (!cmd->argv)
		word->flags |= W_COMMAND;
	ft_lstadd_back(&(cmd->argv), node);
	cmd->argc++;
	return (1);
}

/**
 * @brief	Adds the first token of token_lst to the arguments of cmd
 *			and moves token_lst to the next token.
 * @return	`1` on success, `0` on failure.
 */
int	init_argv(t_cmd *cmd, t_list **token_lst, char *line)
{
	t_token	*tk;
	int		ok;

	tk = (*token_lst)->content;
	if (cmd->argv && (long)tk->start == cmd->arg_end)
		ok = merge_word(cmd, tk, line);
	else
		ok = new_word(cmd, tk, line);
	if (!ok)
		return (0);
	cmd->arg_end = (long)(tk->start + tk->len);
	*token_lst = (*token_lst)->next;
	return (1);
}
