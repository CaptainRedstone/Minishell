/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 14:50:56 by ethrober          #+#    #+#             */
/*   Updated: 2026/10/08 14:50:56 by ethrober         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief	unset NAME... Like bash, names that are not valid
 *			identifiers are silently ignored.
 */
int	ft_unset(t_context *ctx, char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (is_valid_name(av[i], ft_strlen(av[i])))
			unset_env(ctx, av[i]);
		i++;
	}
	return (0);
}
