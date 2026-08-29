/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aforcada <aforcada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 20:28:47 by aforcada          #+#    #+#             */
/*   Updated: 2026/08/28 18:37:54 by aforcada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	TOKENIZE_H

# include "../includes/minishell.h"

# define TKZ_MAXITER 10000
# define TKZ_METACHARS " \t\'\"|<>"

# define TK_NULL_NAME "TK_NULL"
# define TK_BLANK_NAME "TK_BLANK"
# define TK_SQUOTE_NAME "TK_SQUOTE"
# define TK_DQUOTE_NAME "TK_DQUOTE"
# define TK_PIPE_NAME "TK_PIPE"
# define TK_REDIR_IN_NAME "TK_REDIR_IN"
# define TK_REDIR_OUT_NAME "TK_REDIR_OUT"
# define TK_WORD_NAME "TK_WORD"

# define TK_NULL_VAL '\0'
# define TK_TAB_VAL '\t'
# define TK_SPACE_VAL ' '
# define TK_PIPE_VAL '|'
# define TK_SQUOTE_VAL '\''
# define TK_DQUOTE_VAL '\"'
# define TK_REDIR_IN_VAL '<'
# define TK_REDIR_OUT_VAL '>'

enum e_token_type
{
	TK_NULL,
	TK_BLANK,
	TK_SQUOTE,
	TK_DQUOTE,
	TK_PIPE,
	TK_REDIR_IN,
	TK_REDIR_OUT,
	TK_WORD,
	TK_END,
};

enum e_tokenizer_state
{
	TKZ_START,
	TKZ_BUILD,
	TKZ_END,
};

typedef struct s_token
{
	int		type;
	size_t	pos;
	size_t	len;
}	t_token;

typedef struct s_tokenizer
{
	int		state;
	size_t	read_pos;
	void	(*handle_err)(t_context *ctx);
}	t_tokenizer;

/**
 * @brief Print token to stdout
 */
void	tk_print(void *content);

/**
 * @brief Assuming ctx->line isn't empty, tokenize line into a list of 
 * tokens ctx->token_lst then return 1 on success and 0 on failure.
 */
int		tokenize(t_context *ctx);

#endif
