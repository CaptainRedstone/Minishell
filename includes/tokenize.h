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

enum e_token_type
{
	e_tk_null = '\0',
	e_tk_word = 1,
	e_tk_pipe = '|',
	e_tk_quote = '\'',
	e_tk_dquote = '\"',
	e_tk_r_redir = '>',
	e_tk_l_redir = '<',
	e_tk_append_redir,
	e_tk_heredoc,
};

/**
 * @brief	Extract token from input line (ctx->line)
 * 
 * @param	ctx[t_context]	Context with various placeholders, notably line
 * @param	tk_start[int] 	Start index of token in line. 
 * @param	tk_end[size_t]	End index of token in line
 * @param	tk_type[int]	Type of token
 * 
 * @return	`t_list` node with newly extracted token see `t_token` else `NULL`
 */
t_list	*extract_token(t_context *ctx,
			int tk_start, size_t tk_end, int tk_type);
/**
 * @brief	Retrieve string between quotes and adds it to token list in 
 * context (ctx->token_lst)
 * 
 * @param	ctx[t_context]	Context with placeholders. See `token_lst`, `line`
 * @param	qi[int]			First quote index in line
 * @param	qtype[int]		Decimal value of quote or dquote in ascii
 * 
 * @return	`int` len of retrieved string else `-1`
 */
int		handle_quote(t_context *ctx, int qi, int qtype);
