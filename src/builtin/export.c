/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 14:50:50 by ethrober          #+#    #+#             */
/*   Updated: 2026/10/08 14:50:50 by ethrober         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	export_one(t_context *ctx, char *arg)
{
	size_t	len;
	char	*key;

	len = name_len(arg);
	if (!is_valid_name(arg, len))
	{
		error_arg("export", arg, "not a valid identifier");
		return (1);
	}
	key = ft_substr(arg, 0, len);
	if (!key)
		return (1);
	if (arg[len] == '=')
		set_env_var(ctx, key, arg + len + 1);
	else
		set_env_decl(ctx, key);
	free(key);
	return (0);
}

/**
 * @brief	export without argument lists the variables (sorted),
 *			with arguments it creates/updates NAME=value or declares NAME.
 */
int	ft_export(t_context *ctx, char **av)
{
	int	i;
	int	ret;

	if (!av[1])
		return (print_export(ctx));
	i = 1;
	ret = 0;
	while (av[i])
	{
		if (export_one(ctx, av[i]))
			ret = 1;
		i++;
	}
	return (ret);
}
