/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aforcada <aforcada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 16:09:39 by aforcada          #+#    #+#             */
/*   Updated: 2026/09/16 13:06:05 by aforcada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief Check if pipe syntax is valid.
 * @param token_lst List of tokens.
 */
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

/**
 * @brief Check if a redirection has valid syntax.
 * @param token_lst List with first element a redirection token
 * and second element a word/quote.
 */
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

/**
 * @brief Print word
 */
void	print_word(void *content)
{
	t_word	*word;

	if (!content)
		return ;
	word = content;
	printf("flags:");
	if (word->flags & W_COMMAND)
		printf("command ");
	if (word->flags & W_WORD)
		printf("word ");
	if (word->flags & W_SQUOTE)
		printf("squote ");
	if (word->flags & W_DQUOTE)
		printf("dquote ");
	if (word->flags & W_EXPAND)
		printf("expand ");
	printf(" str:%s\n", word->str);
}

/**
 * @brief Print redirection
 */
void	print_redir(void *content)
{
	t_redir	*redir;

	if (!content)
		return ;
	redir = content;
	printf("redir: fd(%d) mode(%d) type(%d) ",
		redir->fd, redir->mode, redir->type);
	if (redir->type != R_HEREDOC)
		printf("val(%s)\n", redir->val.path);
	else
		printf("val(%s)\n", redir->val.delim);
}

/**
 * @brief Print command
 */
void	print_cmd(void *content)
{
	t_cmd	*cmd;

	if (!content)
		return ;
	cmd = content;
	printf("cmd: state (%d), redir count (%d), argc (%d)\n",
		cmd->status,
		cmd->redir_cnt,
		cmd->argc);
	ft_lstiter(cmd->redir_in_lst, &print_redir);
	ft_lstiter(cmd->redir_out_lst, &print_redir);
	ft_lstiter(cmd->argv, &print_word);
}
