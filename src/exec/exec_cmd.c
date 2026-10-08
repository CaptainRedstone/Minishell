/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 14:48:37 by ethrober          #+#    #+#             */
/*   Updated: 2026/10/08 14:48:37 by ethrober         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief	execve failed with ENOEXEC (script without #!): bash runs it
 *			with sh, so do we.
 */
static void	run_as_script(char *path, char **av, char **envp)
{
	char	**nav;
	int		n;

	n = 0;
	while (av[n])
		n++;
	nav = malloc(sizeof(char *) * (n + 2));
	if (!nav)
		return ;
	nav[0] = "/bin/sh";
	nav[1] = path;
	n = 1;
	while (av[n])
	{
		nav[n + 1] = av[n];
		n++;
	}
	nav[n + 1] = NULL;
	execve("/bin/sh", nav, envp);
	free(nav);
}

/**
 * @brief	Replaces the current (child) process by the command.
 *			Never returns: on failure frees everything and exits with
 *			126 / 127 like bash.
 */
void	exec_external(t_context *ctx, char **av)
{
	char	*path;
	char	**envp;
	int		code;

	code = 1;
	path = resolve_command(ctx, av[0], &code);
	if (!path)
		exit_shell(ctx, code);
	envp = env_to_array(ctx, 1);
	if (!envp)
	{
		free(path);
		exit_shell(ctx, 1);
	}
	execve(path, av, envp);
	if (errno == ENOEXEC)
		run_as_script(path, av, envp);
	error(av[0], strerror(errno));
	free(path);
	free(envp);
	exit_shell(ctx, 126);
}
