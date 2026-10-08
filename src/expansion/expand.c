/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 14:44:31 by ethrober          #+#    #+#             */
/*   Updated: 2026/10/08 14:44:31 by ethrober         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	exp_squote(t_exp *x, char *raw, size_t *i)
{
	size_t	end;

	end = *i + 1;
	while (raw[end] && raw[end] != '\'')
		end++;
	exp_add(x, raw + *i + 1, end - *i - 1);
	*i = end;
	if (raw[*i])
		(*i)++;
}

static void	exp_dquote(t_exp *x, char *raw, size_t *i)
{
	(*i)++;
	x->started = 1;
	while (raw[*i] && raw[*i] != '"')
	{
		if (raw[*i] == '$')
			exp_var(x, raw, i, 1);
		else
		{
			exp_add(x, raw + *i, 1);
			(*i)++;
		}
	}
	if (raw[*i])
		(*i)++;
}

/**
 * @brief	Expands a raw word (as typed, quotes included):
 *			variables are replaced, quotes are removed, and, if split
 *			is set, unquoted variable values are split on blanks.
 * @return	List of fields (char *): zero, one or several words.
 */
static t_list	*expand_raw(t_context *ctx, char *raw, int split)
{
	t_exp	x;
	size_t	i;

	exp_init(&x, ctx, split);
	i = 0;
	while (raw[i])
	{
		if (raw[i] == '\'')
			exp_squote(&x, raw, &i);
		else if (raw[i] == '"')
			exp_dquote(&x, raw, &i);
		else if (raw[i] == '$')
			exp_var(&x, raw, &i, 0);
		else
		{
			exp_add(&x, raw + i, 1);
			i++;
		}
	}
	exp_push(&x);
	free(x.buf);
	return (x.fields);
}

t_list	*expand_word(t_context *ctx, char *raw)
{
	return (expand_raw(ctx, raw, 1));
}

/**
 * @brief	Expands one argument of a command.
 * @param	decl 1 if the command is export: like bash, an argument
 *			NAME=value is then expanded without word splitting.
 */
t_list	*expand_arg(t_context *ctx, char *raw, int decl)
{
	size_t	len;

	len = name_len(raw);
	if (decl && raw[len] == '=' && is_valid_name(raw, len))
		return (expand_raw(ctx, raw, 0));
	return (expand_raw(ctx, raw, 1));
}
