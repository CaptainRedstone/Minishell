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

typedef struct s_token	t_token;
typedef struct s_ast	t_ast;

struct s_token
{
	int		type;
	char	*name;
	int		quote;
	t_token	*next;
};

struct s_cmd
{
	char	**args;
};

struct s_pipe
{
	t_ast	*left;
	t_ast	*right;
};

struct s_redir
{
	char	*path;
	int		fd;
	int		mode;
	t_ast	*cmd;
};

struct s_ast
{
	int	node_type;
	union u_node {
		s_cmd	cmd;
		s_pipe	pipe;
		s_redir	redir;
	}	node;
};

enum e_token_type
{
	e_word,
	e_quote,
	e_pipe,
	e_redir,
};
