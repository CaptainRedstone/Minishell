/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aforcada <aforcada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 16:34:31 by ethrober          #+#    #+#             */
/*   Updated: 2026/08/29 19:21:32 by aforcada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../minishell.h"

enum e_word_flag {
	W_NULL,
	W_FILENAME = 1 << 1,
	W_PATH = 1 << 2,
	W_COMMAND = 1 << 3,
	W_VARIABLE = 1 << 4,
	W_BUILTIN = 1 << 5,
};

typedef struct s_word
{
	char	*val;
	int		flags;
}	t_word;

typedef struct s_redir
{
	int		fd;
	int		mode;
	char	*fname;
}	t_redir;

typedef struct s_cmd
{
	t_list	*words;
	t_list	*redirs;
}	t_cmd;

#endif
