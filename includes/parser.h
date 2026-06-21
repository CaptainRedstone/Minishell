/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aforcada <aforcada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 15:18:09 by aforcada          #+#    #+#             */
/*   Updated: 2026/06/20 16:07:20 by aforcada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_token		t_token;
typedef struct s_node		t_node;
typedef struct s_node_cmd	t_node_cmd;
typedef struct s_node_pipe	t_node_pipe;
typedef struct s_node_redir	t_node_redir;
typedef struct s_node_sub	t_node_sub;
typedef struct s_context		t_context;

/**
 * @class token 
 */
struct s_token
{
	char	*val;
	int		type;
};

struct s_node_cmd
{
	char	**args;
};

struct s_node_pipe
{
	t_node	*left;
	t_node	*right;
};

struct s_node_redir
{
	char	*path;
	int		fd;
	int		mode;
	t_node	*cmd;
};

struct s_node_sub
{
	t_node	*parent;
	t_node	*child;
};

typedef union u_node
{
	t_node_cmd		cmd;
	t_node_pipe		pipe;
	t_node_redir	redir;
	t_node_sub		sub;
}	t_node_gen;

struct s_node
{
	int			type;
	t_node_gen	node;
};

struct s_context
{
	char	*line;
	char	*prompt;
	t_token	*tokens;
	int		tk_count;
};

enum e_token_type
{
	e_null,
	e_word,
	e_pipe,
	e_quote,
	e_dquote,
	e_right_redir,
	e_left_redir,
	e_append_redir,
	e_heredoc,
	e_lparen,
	e_rparen,
};

enum e_node_type
{
	e_node_null,
	e_node_cmd,
	e_node_pipe,
	e_node_redir,
};

/**
 * @brief Count number of tokens in array
 * 
 * @param arr array of strings with raw tokens
 * @return number of tokens
 */
int		count_tokens(char **arr);

/**
 * @brief Free memory allocation of tokens
 * 
 * @param ctx context with following field
 * @param tokens list of tokens
 */
void	free_tokens(t_context *ctx);

/**
 * @brief Print tokens in received order
 * 
 * @param ctx context with following field
 * @param tokens list of tokens
 */
void	print_tokens(t_context *ctx);

/**
 * @brief Fill token list from split string array
 * 
 * @param arr split string array with raw tokens
 * @param ctx context with following field
 * @param tokens empty list of tokens to be filled
 * 
 * @return 1 on success, else 0
 */
int		fill_tokens(t_context *ctx, char **arr);

/**
 * @brief	Split input line string into list of tokens for further parsing
 * 
 * @param ctx context with following fields
 * @param line raw string of input commands
 * @param tokens list of tokens to fill from line
 * @return 1 on success, else 0
 */
int		tokenize(t_context *ctx);

#endif
