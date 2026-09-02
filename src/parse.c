#include "../minishell.h"



t_token	*parse_token(char *line)
{
	(void)line;
	return (NULL);
}

// TODO: tester
t_token	*get_token_at(void *placeholder, int idx, int cast_type)
{
	t_list	*node;

	node = NULL;
	if (cast_type != T_CONTEXT_TYPE && cast_type != T_CMD_TYPE)
		return (NULL);
	if (cast_type == T_CONTEXT_TYPE)
		node = ((t_context *)placeholder)->token_lst;
	if (cast_type == T_CMD_TYPE)
		node = ((t_cmd *)placeholder)->token_lst;
	while (node && 0 <= idx--)
		node = node->next;
	if (!node)
		return (NULL);
	return (node->content);
}

// // TODO: split cmd
// int	validate_pipe(t_context *ctx, int	pipe_idx)
// {
// 	if (pipe_idx == 0)
// 		return (0);
// 	ctx->current_token = get_token_at(ctx, pipe_idx + 1);
// 	if (!(ctx->current_token) || ctx->current_token->type == TK_PIPE)
// 		return (0);
// 	return (1);
// }

// // TODO: check path exist
// int	check_redir(t_context *ctx, int redir_idx)
// {
// 	ctx->current_token = get_token_at(ctx, redir_idx, );
// 	if (2 < ctx->current_token->len)
// 		return (0);
// 	ctx->current_token = get_token_at(ctx, redir_idx + 1);
// 	if (ctx->current_token && ctx->current_token->type != TK_WORD)
// 		return (0);
// 	return (1);
// }
