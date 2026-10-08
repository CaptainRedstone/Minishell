/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 14:45:34 by ethrober          #+#    #+#             */
/*   Updated: 2026/10/08 14:45:34 by ethrober         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief	Tells if c opens or closes a quote (and is thus removed).
 */
static int	is_delim(char c, char *q, int *quoted)
{
	if (!*q && (c == '\'' || c == '"'))
	{
		*q = c;
		*quoted = 1;
		return (1);
	}
	if (*q && c == *q)
	{
		*q = 0;
		return (1);
	}
	return (0);
}

/**
 * @brief	Removes the quotes of a heredoc delimiter.
 * @param	quoted Set to 1 if the delimiter contained quotes (then the
 *			body of the heredoc is not expanded).
 */
char	*strip_quotes(char *raw, int *quoted)
{
	char	*out;
	char	q;
	size_t	i;
	size_t	j;

	out = ft_calloc(ft_strlen(raw) + 1, sizeof(char));
	if (!out)
		return (NULL);
	q = 0;
	i = 0;
	j = 0;
	*quoted = 0;
	while (raw[i])
	{
		if (!is_delim(raw[i], &q, quoted))
		{
			out[j] = raw[i];
			j++;
		}
		i++;
	}
	return (out);
}

/**
 * @brief	Expands $VAR and $? in a heredoc line (no quote handling, no
 *			word splitting). Frees line, returns the new string.
 */
char	*expand_heredoc_line(t_context *ctx, char *line)
{
	t_exp	x;
	size_t	i;

	exp_init(&x, ctx, 0);
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			exp_var(&x, line, &i, 1);
		else
		{
			exp_add(&x, line + i, 1);
			i++;
		}
	}
	free(line);
	return (x.buf);
}

void	write_line(t_context *ctx, int fd, char *line, int quoted)
{
	if (!quoted)
		line = expand_heredoc_line(ctx, line);
	ft_putendl_fd(line, fd);
	free(line);
}

void	warn_eof(char *delim)
{
	ft_putstr_fd("MiniShell: warning: here-document delimited ", 2);
	ft_putstr_fd("by end-of-file (wanted '", 2);
	ft_putstr_fd(delim, 2);
	ft_putstr_fd("')\n", 2);
}
