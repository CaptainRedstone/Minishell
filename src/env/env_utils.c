/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 14:46:50 by ethrober          #+#    #+#             */
/*   Updated: 2026/10/08 14:46:50 by ethrober         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief	Finds the node of variable "key" ("KEY=..." or just "KEY").
 */
t_list	*find_env_node(t_context *ctx, char *key)
{
	t_list	*node;
	size_t	len;
	char	*entry;

	len = ft_strlen(key);
	node = ctx->envp_lst;
	while (node)
	{
		entry = node->content;
		if (!ft_strncmp(entry, key, len)
			&& (entry[len] == '=' || entry[len] == '\0'))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * @brief	Returns the value of "key" (pointer inside the list), or NULL
 *			if unset or declared without value.
 */
char	*get_env(t_context *ctx, char *key)
{
	t_list	*node;
	size_t	len;

	node = find_env_node(ctx, key);
	if (!node)
		return (NULL);
	len = ft_strlen(key);
	if (((char *)node->content)[len] != '=')
		return (NULL);
	return ((char *)node->content + len + 1);
}

/**
 * @brief	Creates or replaces "key=val".
 */
int	set_env_var(t_context *ctx, char *key, char *val)
{
	char	*entry;
	t_list	*node;

	entry = ft_strjoin(key, "=");
	if (!entry)
		return (0);
	entry = join_and_free(entry, val);
	if (!entry)
		return (0);
	node = find_env_node(ctx, key);
	if (node)
	{
		free(node->content);
		node->content = entry;
		return (1);
	}
	ft_lstadd_back(&ctx->envp_lst, ft_lstnew(entry));
	ctx->envp_cnt++;
	return (1);
}

/**
 * @brief	"export KEY" without value: adds KEY if it does not exist yet.
 */
void	set_env_decl(t_context *ctx, char *key)
{
	char	*entry;

	if (find_env_node(ctx, key))
		return ;
	entry = ft_strdup(key);
	if (!entry)
		return ;
	ft_lstadd_back(&ctx->envp_lst, ft_lstnew(entry));
	ctx->envp_cnt++;
}

void	unset_env(t_context *ctx, char *key)
{
	t_list	*node;
	t_list	*prev;

	node = find_env_node(ctx, key);
	if (!node)
		return ;
	if (ctx->envp_lst == node)
		ctx->envp_lst = node->next;
	else
	{
		prev = ctx->envp_lst;
		while (prev->next != node)
			prev = prev->next;
		prev->next = node->next;
	}
	ft_lstdelone(node, &free);
	ctx->envp_cnt--;
}
