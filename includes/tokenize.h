/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aforcada <aforcada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 20:28:47 by aforcada          #+#    #+#             */
/*   Updated: 2026/07/14 13:52:57 by aforcada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_token	t_token;

struct s_token
{
	int		type;
	char	*val;
};

enum e_token_type
{
	e_tk_error = -1,
	e_tk_null = 0,
	e_tk_word = 1,
	e_tk_pipe = '|',
	e_tk_quote = 39,
	e_tk_dquote = '"',
	e_tk_r_redir = '>',
	e_tk_l_redir = '<',
	e_tk_append_redir,
	e_tk_heredoc,
};

int	handle_quote(t_context *ctx, int line_idx);
