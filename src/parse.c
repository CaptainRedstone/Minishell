#include "../minishell.h"

t_command	parse_command(char *line, t_command command)
{
	(void)line;
	return (command);
}

t_token	*parse_token(char *line)
{
	(void)line;
	return (NULL);
}

// TODO: tester
t_token	*get_token_at(t_context *ctx, int pos)
{
	t_list	*node;

	if (pos < 0 || ctx->token_lst_len < pos)
		return (NULL);
	node = ctx->token_lst;
	while (0 < pos--)
		node = node->next;
	return (node->content);
}

int	check_pipe(t_context *ctx, int	pipe_idx)
{
	ctx->current_token = get_token_at(ctx, pipe_idx - 1);
	if (!(ctx->current_token) || ctx->current_token->type == TK_PIPE)
		return (0);
	ctx->current_token = get_token_at(ctx, pipe_idx + 1);
	if (!(ctx->current_token) || ctx->current_token->type == TK_PIPE)
		return (0);
	return (1);
}

// TODO: check path exist
int	check_redir(t_context *ctx, int redir_idx)
{
	ctx->current_token = get_token_at(ctx, redir_idx);
	if (2 < ctx->current_token->len)
		return (0);
	ctx->current_token = get_token_at(ctx, redir_idx + 1);
	if (ctx->current_token && ctx->current_token->type != TK_WORD)
		return (0);
	return (1);
}
