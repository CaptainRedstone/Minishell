/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:52:50 by ethrober          #+#    #+#             */
/*   Updated: 2025/10/01 15:29:17 by ethrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}

/*int	main(void)
{
	printf("%d\n", ft_isprint(' '));
	printf("%d\n", ft_isprint('!'));
	printf("%d\n", ft_isprint('0'));
	printf("%d\n", ft_isprint('9'));
	printf("%d\n", ft_isprint('a'));
	printf("%d\n", ft_isprint('z'));
	printf("%d\n", ft_isprint('A'));
	printf("%d\n", ft_isprint('Z'));
	printf("%d\n", ft_isprint('\\'));
	printf("%d\n", ft_isprint('~'));
	printf("%d\n", ft_isprint('}'));
    printf("%d\n", ft_isprint('\0'));
    printf("%d\n", ft_isprint('\n'));
}*/