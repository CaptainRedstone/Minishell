/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aforcada <aforcada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 10:43:09 by aforcada          #+#    #+#             */
/*   Updated: 2026/08/28 18:42:04 by aforcada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenize.h"

// string functions
size_t	strlen_if(const char *str, int (*cond)(char c))
{
	size_t	i;

	i = 0;
	while (i < TKZ_MAXITER && cond(str[i]))
		i++;
	return (i);
}

int	is_blank(char c)
{
	if (c == TK_SPACE_VAL)
		return (1);
	if (c == TK_TAB_VAL)
		return (1);
	return (0);
}

// token related
void	tk_print(void *content)
{
	(void)content;
	printf("je suis un token ma gueule\n");
}

// tokenize related
int	tokenize(t_context *ctx)
{
	t_tokenizer	tkz;

	ft_bzero(&tkz, sizeof(t_tokenizer));
	while (tkz.read_pos < ctx->line_len)
	{
		tkz.read_pos++;
	}
	printf("done\n");
	return (0);
}
