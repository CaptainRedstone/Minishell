/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aforcada <aforcada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 15:18:09 by aforcada          #+#    #+#             */
/*   Updated: 2026/06/09 17:02:25 by aforcada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_token	t_token;
typedef struct s_cmd	t_cmd;
typedef struct s_pipe	t_pipe;
typedef struct s_redir	t_redir;
typedef struct s_exec	t_exec;

struct s_token
{
	int		type;
	char	*name;
	int		quote;
	t_token	*next;
};

struct s_cmd
{
	int		type;
	char	**args;
};

struct s_pipe
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
};

struct s_redir
{
	int		type;
	char	*path;
	int		fd;
	int		mode;
	t_cmd	*cmd;
};

struct s_exec
{
	int		type;
	char	**args;
};

enum e_token_type
{
	e_word,
	e_quote,
	e_pipe,
	e_redir_in,
	e_redir_out,
	e_redir_append,
	e_exec,
	e_flag,
};
