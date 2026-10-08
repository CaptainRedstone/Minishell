/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 14:46:59 by ethrober          #+#    #+#             */
/*   Updated: 2026/10/08 14:46:59 by ethrober         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	bump_shlvl(t_context *ctx)
{
	char	*val;
	char	*num;
	int		lvl;

	val = get_env(ctx, "SHLVL");
	lvl = 0;
	if (val)
		lvl = ft_atoi(val);
	if (lvl < 0)
		lvl = -1;
	num = ft_itoa(lvl + 1);
	if (num)
		set_env_var(ctx, "SHLVL", num);
	free(num);
}

static void	ensure_pwd(t_context *ctx)
{
	char	*cwd;

	if (get_env(ctx, "PWD"))
		return ;
	cwd = getcwd(NULL, 0);
	if (cwd)
		set_env_var(ctx, "PWD", cwd);
	free(cwd);
}

/**
 * @brief	Copies envp into ctx->envp_lst (list of "KEY=VALUE" strings).
 */
void	init_env(t_context *ctx, char **envp)
{
	int		i;
	char	*entry;

	i = 0;
	while (envp && envp[i])
	{
		entry = ft_strdup(envp[i]);
		if (entry)
		{
			ft_lstadd_back(&ctx->envp_lst, ft_lstnew(entry));
			ctx->envp_cnt++;
		}
		i++;
	}
	bump_shlvl(ctx);
	ensure_pwd(ctx);
}

/**
 * @brief	NULL-terminated array of pointers on the list strings (for
 *			execve). Only free the array itself, not the strings.
 * @param	only_set 1 = skip variables declared without value.
 */
char	**env_to_array(t_context *ctx, int only_set)
{
	t_list	*node;
	char	**arr;
	int		i;

	arr = malloc(sizeof(char *) * (ft_lstsize(ctx->envp_lst) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	node = ctx->envp_lst;
	while (node)
	{
		if (!only_set || ft_strchr(node->content, '='))
		{
			arr[i] = node->content;
			i++;
		}
		node = node->next;
	}
	arr[i] = NULL;
	return (arr);
}
