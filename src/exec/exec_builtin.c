/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 14:48:42 by ethrober          #+#    #+#             */
/*   Updated: 2026/10/08 14:48:42 by ethrober         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_builtin(char *name)
{
	return (!ft_strncmp(name, "cd", 3) || !ft_strncmp(name, "echo", 5)
		|| !ft_strncmp(name, "env", 4) || !ft_strncmp(name, "exit", 5)
		|| !ft_strncmp(name, "export", 7) || !ft_strncmp(name, "pwd", 4)
		|| !ft_strncmp(name, "unset", 6));
}

/**
 * @brief	Runs the builtin av[0].
 * @return	Its exit status.
 */
int	run_builtin(t_context *ctx, char **av)
{
	if (!ft_strncmp(av[0], "cd", 3))
		return (ft_cd(ctx, av));
	if (!ft_strncmp(av[0], "echo", 5))
		return (ft_echo(ctx, av));
	if (!ft_strncmp(av[0], "env", 4))
		return (ft_env(ctx, av));
	if (!ft_strncmp(av[0], "exit", 5))
		return (ft_exit(ctx, av));
	if (!ft_strncmp(av[0], "export", 7))
		return (ft_export(ctx, av));
	if (!ft_strncmp(av[0], "pwd", 4))
		return (ft_pwd(ctx, av));
	if (!ft_strncmp(av[0], "unset", 6))
		return (ft_unset(ctx, av));
	return (1);
}
