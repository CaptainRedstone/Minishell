/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aforcada <aforcada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 20:28:47 by aforcada          #+#    #+#             */
/*   Updated: 2026/08/29 19:15:14 by aforcada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "../includes/minishell.h"

# define TK_MAXITER 10000

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
# define TK_METACHARS " \t\'\"|<>"

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

typedef struct s_token
{
	int		type;
	size_t	pos;
	size_t	len;
}	t_token;

/**
 * @brief Get token `type` as in `e_token_type` from c.
 */
int		get_token_type(char c);

/**
 * @brief Get token `name` from its `type` as in `e_token_type`.
 */
char	*get_token_name(int type);

/**
 * @brief Print token to stdout
 */
void	print_token(void *content);

/**
 * @brief Assuming `line` starts w/ quote of type `TK_SQUOTE` or `TK_DQUOTE`,
 * compute length of quote.
 * @attention Includes quote char
 */
size_t	quote_len(char *line, int type);

/**
 * @brief Assuming `line` starts w/ token of `type` in `e_token_type`, 
 * compute length of token.
 */
size_t	token_len(char *line, int type);

#endif
