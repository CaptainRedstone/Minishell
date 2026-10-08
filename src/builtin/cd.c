/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 14:50:37 by ethrober          #+#    #+#             */
/*   Updated: 2026/10/08 14:50:37 by ethrober         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	update_pwd(t_context *ctx, char *old)
{
	char	*cwd;

	if (old)
		set_env_var(ctx, "OLDPWD", old);
	cwd = getcwd(NULL, 0);
	if (cwd)
		set_env_var(ctx, "PWD", cwd);
	free(cwd);
}

/**
 * @brief	cd with a relative or absolute path (no argument = $HOME).
 *			Updates PWD and OLDPWD.
 */
int	ft_cd(t_context *ctx, char **av)
{
	char	*path;
	char	*old;

	if (av[1] && av[2])
		return (error("cd", "too many arguments"), 1);
	path = av[1];
	if (!path)
		path = get_env(ctx, "HOME");
	if (!path)
		return (error("cd", "HOME not set"), 1);
	if (!path[0])
		return (0);
	old = getcwd(NULL, 0);
	if (chdir(path) < 0)
	{
		error_arg("cd", path, strerror(errno));
		free(old);
		return (1);
	}
	update_pwd(ctx, old);
	free(old);
	return (0);
}
