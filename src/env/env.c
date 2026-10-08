/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 14:46:45 by ethrober          #+#    #+#             */
/*   Updated: 2026/10/08 14:46:45 by ethrober         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief	Prints the variables that have a value (KEY=VALUE).
 */
int	ft_env(t_context *ctx, char **av)
{
	t_list	*node;

	if (av[1])
	{
		error_arg("env", av[1], "No such file or directory");
		return (127);
	}
	node = ctx->envp_lst;
	while (node)
	{
		if (ft_strchr(node->content, '='))
			ft_putendl_fd(node->content, STDOUT_FILENO);
		node = node->next;
	}
	return (0);
}
