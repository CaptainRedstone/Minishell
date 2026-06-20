/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aforcada <aforcada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 15:18:09 by aforcada          #+#    #+#             */
/*   Updated: 2026/06/20 11:27:04 by aforcada         ###   ########.fr       */
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

enum e_token_type
{
	e_null,
	e_word,
	e_pipe,
	e_single_quote,
	e_double_quote,
	e_right_redir,
	e_left_redir,
	e_paranthesis,
};

enum e_node_type
{
	e_node_null,
	e_node_cmd,
	e_node_pipe,
	e_node_redir,
};

#endif
