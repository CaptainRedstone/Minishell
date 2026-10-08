/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 14:40:54 by ethrober          #+#    #+#             */
/*   Updated: 2026/10/08 14:40:58 by ethrober         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief	Reads one line on stdin, one byte at a time (so that nothing
 *			is consumed after the newline: heredoc children and the shell
 *			share the same descriptor).
 * @return	The line without '\n', or NULL at end of input.
 */
static char	*read_fd_line(void)
{
	char	*line;
	char	c[2];
	int		ret;

	ret = read(STDIN_FILENO, c, 1);
	if (ret <= 0)
		return (NULL);
	line = ft_strdup("");
	while (line && ret > 0 && c[0] != '\n')
	{
		c[1] = '\0';
		line = join_and_free(line, c);
		ret = read(STDIN_FILENO, c, 1);
	}
	return (line);
}

/**
 * @brief	Interactive (tty): readline with prompt and line editing.
 *			Non interactive (pipe, file): no prompt, no echo, so the
 *			output is the same as bash's one.
 */
char	*read_input(char *prompt)
{
	if (isatty(STDIN_FILENO))
		return (readline(prompt));
	return (read_fd_line());
}
