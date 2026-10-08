/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_name.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 14:46:55 by ethrober          #+#    #+#             */
/*   Updated: 2026/10/08 14:46:55 by ethrober         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief	Length of the variable name in "NAME=value" (or "NAME").
 */
size_t	name_len(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	return (i);
}

/**
 * @brief	A valid identifier is [A-Za-z_][A-Za-z0-9_]*
 */
int	is_valid_name(char *s, size_t len)
{
	size_t	i;

	if (len == 0 || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	i = 1;
	while (i < len)
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
