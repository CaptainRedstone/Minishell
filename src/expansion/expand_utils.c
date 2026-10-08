/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 14:44:42 by ethrober          #+#    #+#             */
/*   Updated: 2026/10/08 14:44:42 by ethrober         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief	Initializes an expansion: no field yet, empty buffer.
 */
void	exp_init(t_exp *x, t_context *ctx, int split)
{
	x->ctx = ctx;
	x->fields = NULL;
	x->started = 0;
	x->split = split;
	x->buf = ft_strdup("");
}

/**
 * @brief	Ends the current field (if one was started) and starts a new one.
 */
void	exp_push(t_exp *x)
{
	if (!x->started)
		return ;
	ft_lstadd_back(&x->fields, ft_lstnew(x->buf));
	x->buf = ft_strdup("");
	x->started = 0;
}

/**
 * @brief	Appends len characters of s to the current field.
 */
void	exp_add(t_exp *x, char *s, size_t len)
{
	char	*part;

	part = ft_substr(s, 0, len);
	x->buf = join_and_free(x->buf, part);
	free(part);
	x->started = 1;
}

/**
 * @brief	Appends the value of a variable. Unquoted: blanks split the
 *			value into several fields. Quoted: the value is kept as is.
 */
void	exp_val(t_exp *x, char *val, int quoted)
{
	size_t	i;

	if (quoted || !x->split)
	{
		exp_add(x, val, ft_strlen(val));
		return ;
	}
	i = 0;
	while (val[i])
	{
		if (val[i] == ' ' || val[i] == '\t' || val[i] == '\n')
			exp_push(x);
		else
			exp_add(x, val + i, 1);
		i++;
	}
}
