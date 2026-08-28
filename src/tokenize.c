/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aforcada <aforcada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 10:43:09 by aforcada          #+#    #+#             */
/*   Updated: 2026/08/28 18:29:18 by aforcada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenize.h"

// generic functions
size_t	strlen_if(const char *str, int (*cond)(char c))
{
	size_t	i;
	
	i = 0;
	while (i < TKZ_MAXITER && cond(str[i]))
	i++;
	return (i);
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
	(void)ctx;
	return (0);
}
