/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 14:41:13 by ethrober          #+#    #+#             */
/*   Updated: 2026/10/08 14:41:13 by ethrober         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief	Hostname read from /etc/hostname (allocated), "localhost" if
 *			unavailable.
 */
char	*get_hostname(void)
{
	char	buf[256];
	int		fd;
	int		n;

	fd = open("/etc/hostname", O_RDONLY);
	if (fd < 0)
		return (ft_strdup("localhost"));
	n = read(fd, buf, sizeof(buf) - 1);
	close(fd);
	if (n <= 0)
		return (ft_strdup("localhost"));
	buf[n] = '\0';
	if (buf[n - 1] == '\n')
		buf[n - 1] = '\0';
	return (ft_strdup(buf));
}

/**
 * @brief	Current working directory (allocated), "" if it cannot be read.
 */
char	*get_prompt(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_strdup(""));
	return (cwd);
}

char	*join_and_free(char *s1, char *s2)
{
	char	*new;

	new = ft_strjoin(s1, s2);
	free(s1);
	return (new);
}

/**
 * @brief	Builds "user@host : cwd > ". Works even with an empty
 *			environment (env -i): USER falls back to "user".
 */
char	*build_prompt(t_context *ctx)
{
	char	*prompt;
	char	*user;
	char	*tmp;

	user = get_env(ctx, "USER");
	if (!user)
		user = "user";
	prompt = ft_strjoin(P_BGREEN, user);
	prompt = join_and_free(prompt, P_RESET "@");
	prompt = join_and_free(prompt, P_BBLUE);
	tmp = get_hostname();
	prompt = join_and_free(prompt, tmp);
	free(tmp);
	prompt = join_and_free(prompt, P_RESET " : ");
	prompt = join_and_free(prompt, P_GREEN);
	tmp = get_prompt();
	prompt = join_and_free(prompt, tmp);
	free(tmp);
	prompt = join_and_free(prompt, P_RESET " > ");
	return (prompt);
}
