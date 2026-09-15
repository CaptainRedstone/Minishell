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

void	print_cmd(void *content)
{
	t_cmd	*cmd;

	if (content)
	{
		cmd = content;
		printf("cmd: state(%d), ntk(%d), rdr(%d), argc(%d)\n",
			cmd->status,
			cmd->token_cnt,
			cmd->redir_cnt,
			cmd->argc);
		ft_lstiter(cmd->token_lst, &print_token);
	}
}

int	set_redir_val(t_redir *rdr, t_token *token, char *line)
{
	if (!rdr || !line)
		return (0);
	if (rdr->type == R_HEREDOC)
		return (0);
	rdr->val.path = ft_substr(line, token->start, token->len);
	if (rdr->val.path)
		return (1);
	return (0);
}

int	set_redir_mode(t_redir *rdr)
{
	if (!rdr)
		return (0);
	if (rdr->type == R_IN)
		rdr->mode = R_MODE_IN;
	if (rdr->type == R_OUT)
		rdr->mode = R_MODE_OUT;
	if (rdr->type == R_APPEND)
		rdr->mode = R_MODE_APPEND;
	if (rdr->type == R_HEREDOC)
		rdr->mode = R_MODE_HEREDOC;
	return (1);
}

int	set_redir_type(t_redir *rdr, t_token *token)
{
	if (!rdr)
		return (0);
	if (token->type == TK_REDIR_IN && token->len == 1)
		rdr->type = R_IN;
	if (token->type == TK_REDIR_OUT && token->len == 1)
		rdr->type = R_OUT;
	if (token->type == TK_REDIR_IN && token->len == 2)
		rdr->type = R_APPEND;
	if (token->type == TK_REDIR_OUT && token->len == 2)
		rdr->type = R_HEREDOC;
	return (1);
}

int	init_redir(t_list *redir_lst, t_list *token_lst, char *line)
{
	t_redir	*rdr;
	t_token	*tok;

	if (!valid_redir_syntax(token_lst))
		return (0);
	rdr = ft_calloc(1, sizeof(t_redir));
	tok = token_lst->content;
	if (rdr && tok->type == TK_REDIR_OUT)
		rdr->fd = 1;
	set_redir_type(rdr, tok);
	set_redir_mode(rdr);
	tok = token_lst->next->content;
	set_redir_val(rdr, tok, line);
	if (!rdr)
		return (0);
	ft_lstadd_back(&redir_lst, ft_lstnew(rdr));
	return (1);
}

int	init_cmd(t_context *ctx, t_list *token_lst)
{
	t_cmd	*cmd;
	t_token	*token;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (0);
	while (token_lst)
	{
		token = token_lst->content;
		if (token->type == TK_REDIR_IN || token->type == TK_REDIR_OUT)
		{
			if (!init_redir(cmd->redir_lst, token_lst, ctx->line))
				return (0);
			cmd->redir_cnt++;
			token_lst = token_lst->next->next;
		}
		else if (token->type != TK_PIPE)
		{
			ft_lstadd_back(&(cmd->argv), ft_lstnew(token));
			cmd->argc++;
		}
		else
		{
			ft_lstadd_back(&(ctx->cmd_lst), ft_lstnew(cmd));
			ctx->cmd_cnt++;
			return (1);
		}
		if (token_lst)
			token_lst = token_lst->next;
	}
	if (!token_lst)
	{
		ft_lstadd_back(&(ctx->cmd_lst), ft_lstnew(cmd));
		ctx->cmd_cnt++;
		return (1);
	}
	return (0);
}

int	init_cmd_lst(t_context *ctx)
{
	if (!ctx || !(ctx->token_lst) || !valid_pipes(ctx->token_lst))
		return (0);
	while (ctx->token_lst)
	{
		ctx->current_token = ctx->token_lst->content;
		if (ctx->current_token->type != TK_PIPE)
			init_cmd(ctx, ctx->token_lst);
		if (ctx->token_lst)
			ctx->token_lst = ctx->token_lst->next;
	}
	return (1);
}
