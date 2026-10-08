/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 14:44:39 by ethrober          #+#    #+#             */
/*   Updated: 2026/10/08 14:44:39 by ethrober         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static size_t	var_len(char *s)
{
	size_t	i;

	if (!ft_isalpha(s[0]) && s[0] != '_')
		return (0);
	i = 0;
	while (ft_isalnum(s[i]) || s[i] == '_')
		i++;
	return (i);
}

static void	exp_named(t_exp *x, char *s, size_t *i, int quoted)
{
	size_t	len;
	char	*key;
	char	*val;

	len = var_len(s + *i + 1);
	key = ft_substr(s, *i + 1, len);
	val = NULL;
	if (key)
		val = get_env(x->ctx, key);
	if (val)
		exp_val(x, val, quoted);
	free(key);
	*i += len + 1;
}

/**
 * @brief	Expands the '$' found at s[*i] and moves *i after it.
 *			$? -> exit status, $NAME -> value, $<digit> -> empty,
 *			$"..." / $'...' (unquoted) -> the '$' is dropped,
 *			anything else -> a literal '$'.
 */
void	exp_var(t_exp *x, char *s, size_t *i, int quoted)
{
	char	*num;

	if (s[*i + 1] == '?')
	{
		num = ft_itoa(x->ctx->exit_status);
		exp_val(x, num, quoted);
		free(num);
		*i += 2;
	}
	else if (var_len(s + *i + 1))
		exp_named(x, s, i, quoted);
	else if (ft_isdigit(s[*i + 1]))
		*i += 2;
	else if (!quoted && (s[*i + 1] == '"' || s[*i + 1] == '\''))
		(*i)++;
	else
	{
		exp_add(x, "$", 1);
		(*i)++;
	}
}
