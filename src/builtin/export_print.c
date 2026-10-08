/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 14:50:46 by ethrober          #+#    #+#             */
/*   Updated: 2026/10/08 14:50:46 by ethrober         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief	Compares two "NAME=value" entries on the NAME part only.
 */
static int	cmp_names(char *a, char *b)
{
	size_t	i;
	int		ca;
	int		cb;

	i = 0;
	while (a[i] && a[i] != '=' && a[i] == b[i])
		i++;
	ca = (unsigned char)a[i];
	cb = (unsigned char)b[i];
	if (ca == '=')
		ca = 0;
	if (cb == '=')
		cb = 0;
	return (ca - cb);
}

static void	sort_env(char **arr)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = 0;
	while (arr[i])
	{
		j = i + 1;
		while (arr[j])
		{
			if (cmp_names(arr[i], arr[j]) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	print_value(char *s)
{
	ft_putchar_fd('"', STDOUT_FILENO);
	while (*s)
	{
		if (*s == '"' || *s == '\\' || *s == '$' || *s == '`')
			ft_putchar_fd('\\', STDOUT_FILENO);
		ft_putchar_fd(*s, STDOUT_FILENO);
		s++;
	}
	ft_putchar_fd('"', STDOUT_FILENO);
}

static void	print_one(char *e)
{
	char	*eq;

	if (e[0] == '_' && (e[1] == '=' || e[1] == '\0'))
		return ;
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	eq = ft_strchr(e, '=');
	if (!eq)
	{
		ft_putendl_fd(e, STDOUT_FILENO);
		return ;
	}
	write(STDOUT_FILENO, e, eq - e + 1);
	print_value(eq + 1);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

/**
 * @brief	export with no argument: prints declare -x NAME="value",
 *			sorted by name.
 */
int	print_export(t_context *ctx)
{
	char	**arr;
	int		i;

	arr = env_to_array(ctx, 0);
	if (!arr)
		return (1);
	sort_env(arr);
	i = 0;
	while (arr[i])
	{
		print_one(arr[i]);
		i++;
	}
	free(arr);
	return (0);
}
