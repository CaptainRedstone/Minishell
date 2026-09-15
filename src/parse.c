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

int	set_redir_val(t_redir *rd, char *line, t_token *token)
{
	if (!rd || !line)
		return (0);
	if (rd->type == R_HEREDOC)
		return (0);
	rd->val.path = ft_substr(line, token->start, token->len);
}

int	init_redir(t_redir *rd, int fd, int mode, t_redir_t type)
{
	if (!rd)
		return (0);
	rd->fd = fd;
	rd->mode = mode;
	rd->type = type;
}

int	init_redir_lst(t_context *ctx, t_cmd *cmd)
{
	t_token	*token;
	t_redir	*redir;

	while (cmd->token_lst && cmd->token_lst->next)
	{
		token = cmd->token_lst->content;
		if (token->type == TK_REDIR_OUT || token->type == TK_REDIR_IN)
		{
			redir = ft_calloc(1, sizeof(t_redir));
			if (!redir)
				return (0);
			if (token->type == TK_REDIR_IN && token->len == 1)
				init_redir(redir, 0, R_MODE_IN, R_IN);
			if (token->type == TK_REDIR_IN && token->len == 2)
				init_redir(redir, 0, R_MODE_APPEND, R_APPEND);
			if (token->type == TK_REDIR_OUT && token->len == 1)
				init_redir(redir, 0, R_MODE_OUT, R_OUT);
			if (token->type == TK_REDIR_OUT && token->len == 2)
				init_redir(redir, 0, R_MODE_HEREDOC, R_HEREDOC);
			set_redir_val(redir, ctx->line, cmd->token_lst->next->content);
			ft_lstadd_back(&(cmd->redir_lst), ft_lstnew(redir));
			cmd->redir_cnt++;
		}
		cmd->token_lst = cmd->token_lst->next;
	}
	return (1);
}

int	init_cmd(t_context *ctx, t_list *token)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (0);
	cmd->token_cnt = count_cmd_args(token);
	cmd->token_lst = ft_sublst(&token, 0, cmd->token_cnt);
	if (!(cmd->token_lst))
		return (free(cmd), 0);
	ft_lstadd_back(&(ctx->cmd_lst), ft_lstnew(cmd));
	print_cmd(cmd);
	ctx->token_cnt -= cmd->token_cnt;
	ctx->cmd_cnt++;
	return (1);
}

int	init_cmd_lst(t_context *ctx)
{
	if (!ctx || !(ctx->token_lst) || !valid_pipes(ctx->token_lst))
		return (0);
	while (ctx->token_lst)
	{
		ctx->current_token = ctx->token_lst->content;
		if (ctx->current_token->type != TK_PIPE)
		{
			init_cmd(ctx, ctx->token_lst);
		}
		if (ctx->token_lst)
			ctx->token_lst = ctx->token_lst->next;
	}
	return (1);
}
