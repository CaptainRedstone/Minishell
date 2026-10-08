/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 14:44:48 by ethrober          #+#    #+#             */
/*   Updated: 2026/10/08 14:44:48 by ethrober         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	to_words(t_list *fields)
{
	t_word	*word;

	while (fields)
	{
		word = ft_calloc(1, sizeof(t_word));
		if (word)
		{
			word->str = fields->content;
			word->flags = W_WORD;
		}
		fields->content = word;
		fields = fields->next;
	}
}

static t_list	*expand_argv(t_context *ctx, t_cmd *cmd)
{
	t_list	*new;
	t_list	*fields;
	t_list	*node;
	int		decl;

	new = NULL;
	decl = 0;
	node = cmd->argv;
	while (node)
	{
		fields = expand_arg(ctx, ((t_word *)node->content)->str, decl);
		if (!new && fields && !ft_strncmp(fields->content, "export", 7))
			decl = 1;
		to_words(fields);
		ft_lstadd_back(&new, fields);
		node = node->next;
	}
	return (new);
}

static char	**build_av(t_cmd *cmd)
{
	char	**av;
	t_list	*node;
	int		i;

	av = malloc(sizeof(char *) * (cmd->argc + 1));
	if (!av)
		return (NULL);
	i = 0;
	node = cmd->argv;
	while (node)
	{
		av[i] = ((t_word *)node->content)->str;
		i++;
		node = node->next;
	}
	av[i] = NULL;
	return (av);
}

/**
 * @brief	Expands the arguments of a command (once) and builds cmd->av,
 *			the NULL-terminated array given to builtins and execve.
 *			Must be called right before the command is run, so that $?
 *			holds the status of the previous pipeline.
 */
int	expand_cmd(t_context *ctx, t_cmd *cmd)
{
	t_list	*new;

	if (cmd->expanded)
		return (1);
	new = expand_argv(ctx, cmd);
	ft_lstclear(&cmd->argv, &delete_arg);
	cmd->argv = new;
	cmd->argc = ft_lstsize(new);
	if (new)
		((t_word *)new->content)->flags |= W_COMMAND;
	cmd->av = build_av(cmd);
	cmd->expanded = (cmd->av != NULL);
	return (cmd->expanded);
}

/**
 * @brief	Expands the target of a redirection. It must give exactly one
 *			word, otherwise: "ambiguous redirect".
 * @return	Allocated path, or NULL (error printed).
 */
char	*expand_redir_path(t_context *ctx, t_redir *r)
{
	t_list	*fields;
	char	*path;

	fields = expand_word(ctx, r->val.path);
	if (ft_lstsize(fields) != 1)
	{
		ft_lstclear(&fields, &free);
		error(r->val.path, "ambiguous redirect");
		return (NULL);
	}
	path = fields->content;
	free(fields);
	return (path);
}
