/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aforcada <aforcada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 20:28:47 by aforcada          #+#    #+#             */
/*   Updated: 2026/07/15 14:23:34 by aforcada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

typedef struct s_token
{
	int		type;
	char	*val;
	size_t	len;
}	t_token;

enum e_tk_type
{
	e_tk_null = '\0',
	e_tk_word = 1,
	e_tk_pipe = '|',
	e_tk_quote = '\'',
	e_tk_dquote = '\"',
	e_tk_redir_out = '>',
	e_tk_redir_in = '<',
	e_tk_append = 2,
	e_tk_heredoc = 3,
};

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
int	tk_extract(t_context *ctx, int start, size_t len, int type);

/**
 * @brief	Compute len of token in ctx->line from start to char in stop_set
 * 
 * @param	ctx			Context with placeholders, notably `line` and `line_len`
 * @param	start		Start index in `line`
 * @param	stop_set	Set of chars, each represents the end of a token
 * 
 * @return	Length of token
 */
int		tk_len(t_context *ctx, int start, const char *stop_set);
