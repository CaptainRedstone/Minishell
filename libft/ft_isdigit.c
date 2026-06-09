/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethanael <ethanael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 12:41:26 by ethrober          #+#    #+#             */
/*   Updated: 2026/03/02 12:01:37 by ethanael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

/* int	main(void)
{
	printf("%d\n", ft_isdigit('0'));
	printf("%d\n", ft_isdigit(10));
	printf("%d\n", ft_isdigit('A'));
	printf("%d\n", ft_isdigit('z'));
	printf("%d\n", ft_isdigit('.'));
	printf("%d\n", ft_isdigit('|'));
} */