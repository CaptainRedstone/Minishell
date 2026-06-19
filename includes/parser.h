/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aforcada <aforcada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 15:18:09 by aforcada          #+#    #+#             */
/*   Updated: 2026/06/09 17:31:16 by aforcada         ###   ########.fr       */
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

struct s_token
{
	int		type;
	char	*name;
	int		quote;
	t_token	*next;
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

typedef union u_node {
	t_node_cmd		cmd;
	t_node_pipe		pipe;
	t_node_redir	redir;
}	t_node_type;

struct s_node
{
	int			type;
	t_node_type	node;
};

enum e_token_type
{
	e_word,
	e_quote,
	e_pipe,
	e_redir,
};

#endif
