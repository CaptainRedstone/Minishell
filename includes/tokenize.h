/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aforcada <aforcada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 20:28:47 by aforcada          #+#    #+#             */
/*   Updated: 2026/08/28 17:52:15 by aforcada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#define TK_WORD_NAME "TK_WORD"
#define TK_PIPE_NAME "TK_PIPE"
#define TK_SQUOTE_NAME "TK_SQUOTE"
#define TK_DQUOTE_NAME "TK_DQUOTE"
#define TK_REDIR_IN_NAME "TK_REDIR_IN"
#define TK_REDIR_OUT_NAME "TK_REDIR_OUT"
#define TK_REDIR_APPEND_NAME "TK_REDIR_APPEND"
#define TK_REDIR_HEREDOC_NAME "TK_REDIR_HEREDOC"

#define TK_PIPE_VAL "|"
#define TK_SQUOTE_VAL "\'"
#define TK_DQUOTE_VAL "\""
#define TK_REDIR_IN_VAL "<"
#define TK_REDIR_OUT_VAL ">"
#define TK_REDIR_APPEND_VAL ">>"
#define TK_REDIR_HEREDOC_VAL "<<"

#define TK_METACHARS "\'\"|<>"
#define TK_QUOTE_CHARS "\'\""
#define TK_REDIR_CHARS "<>"
#define TK_BLANK_CHARS " \t"

enum e_token_type
{
	TK_NULL,
	TK_WORD,
	TK_PIPE,
	TK_SQUOTE,
	TK_DQUOTE,
	TK_REDIR_IN,
	TK_REDIR_OUT,
	TK_REDIR_APPEND,
	TK_REDIR_HEREDOC,
	TK_END,
};

enum e_tokenizer_state
{
	TKZ_ERROR,
	TKZ_SKIP,
	TKZ_BUILD,
	TKZ_APPEND,
	TKZ_END,
};

typedef struct s_token
{
	int		type;
	int		pos;
	char	*val;
	size_t	len;
}	t_token;

typedef struct s_tokenizer
{
	int		state;
	size_t	pos;
	int		(*skip_charset)(t_context *ctx, size_t *pos);
	int		(*append_token)(t_context *ctx, t_token *token);
	void	(*handle_err)(t_context *ctx);
}	t_tokenizer;

/**
 * @brief	Extract token from input line (ctx->line) and copies its
 * content and metadata (type + length) at the end of  the token list
 * (ctx->token_lst)
 * 
 * @param	ctx		Context with various placeholders, notably line
 * @param	start	Start index of token in line. 
 * @param	len		End index of token in line
 * @param	type	Type of token
 * 
 * @return	1 is success, 0 is failure
 */
int		tk_extract(t_context *ctx, int start, size_t len, int type);

/**
 * @brief	Compute len of token in ctx->line from start to char in stop_set
 * 
 * @param	ctx			Context with placeholders, notably `line` and `line_len`
 * @param	start		Start index in `line`
 * @param	stop_set	Set of chars, each represents the end of a token
 * 
 * @return	Length of token
 */
int		tk_len(t_context *ctx, int start, int type, const char *stop_set);

/**
 * @brief Return the name of token type
 * 
 * @param type token type, see `e_tk_type`
 */
char	*tk_typename(int type);

/**
 * @brief Print token to stdout
 */
void	tk_print(void *content);

/**
 * @brief Assuming ctx->line isn't empty, tokenize line into a list of 
 * tokens ctx->token_lst then return 1 on success and 0 on failure.
 */
int		tokenize(t_context *ctx);
