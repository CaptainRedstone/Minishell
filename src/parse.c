/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aforcada <aforcada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 16:12:50 by aforcada          #+#    #+#             */
/*   Updated: 2026/09/10 07:06:26 by aforcada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// TODO: adapt to show args and redirs
void	print_redir(void *content)
{
	t_redir	*rdr;

	if (content)
	{
		rdr = content;
		printf("rdr: fd(%d) mode(%d) type(%d) ",
			rdr->fd, rdr->mode, rdr->type);
		if (rdr->type != R_HEREDOC)
			printf("val(%s)\n", rdr->val.path);
		else
			printf("val(%s)\n", rdr->val.delim);
	}
}

void	print_cmd(void *content)
{
	t_cmd	*cmd;

	if (content)
	{
		cmd = content;
		printf("cmd: state (%d), redir count (%d), argc (%d)\n",
			cmd->status,
			cmd->redir_cnt,
			cmd->argc);
		ft_lstiter(cmd->redir_lst, &print_redir);
		ft_lstiter(cmd->argv, &print_token);
	}
}

int	init_redir(t_list **redir_lst, t_list *token_lst, char *line)
{
	t_redir	*redir;
	t_token	*token;

	if (!valid_redir_syntax(token_lst))
		return (0);
	redir = ft_calloc(1, sizeof(t_redir));
	token = token_lst->content;
	if (redir && token->type == TK_REDIR_OUT)
		redir->fd = 1;
	set_redir_type(redir, token);
	set_redir_mode(redir);
	set_redir_val(redir, token_lst->next->content, line);
	if (!redir)
		return (0);
	ft_lstadd_back(redir_lst, ft_lstnew(redir));
	return (1);
}

// TODO: refactoring
int	init_cmd(t_context *ctx, t_list **token_lst)
{
	t_cmd	*cmd;
	t_token	*token;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (0);
	while (*token_lst)
	{
		token = (*token_lst)->content;
		if (token->type == TK_REDIR_IN || token->type == TK_REDIR_OUT)
		{
			if (!init_redir(&(cmd->redir_lst), (*token_lst), ctx->line))
				return (free(cmd), 0);
			cmd->redir_cnt++;
			*token_lst = (*token_lst)->next->next;
		}
		else if (token->type != TK_PIPE)
		{
			ft_lstadd_back(&(cmd->argv), ft_lstnew(token));
			cmd->argc++;
			*token_lst = (*token_lst)->next;
		}
		else
			break ;
	}
	if (cmd->argc || cmd->redir_cnt)
	{
		ft_lstadd_back(&(ctx->cmd_lst), ft_lstnew(cmd));
		ctx->cmd_cnt++;
		return (1);
	}
	return (free(cmd), 0);
}

int	init_cmd_lst(t_context *ctx)
{
	if (!ctx || !(ctx->token_lst) || !valid_pipes(ctx->token_lst))
		return (0);
	while (ctx->token_lst)
	{
		init_cmd(ctx, &(ctx->token_lst));
		if (ctx->token_lst)
			ctx->token_lst = ctx->token_lst->next;
	}
	ft_lstiter(ctx->cmd_lst, &print_cmd);
	return (1);
}
