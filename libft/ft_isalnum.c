/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 12:41:31 by ethrober          #+#    #+#             */
/*   Updated: 2025/10/03 15:15:45 by ethrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0'
			&& c <= '9'))
		return (1);
	else
		return (0);
}

/*int	main(void)
{
	printf("%d", ft_isalnum('a'));
	printf("%d", ft_isalnum('d'));
	printf("%d\n", ft_isalnum('z'));
	printf("%d", ft_isalnum('A'));
	printf("%d", ft_isalnum('D'));
	printf("%d\n", ft_isalnum('Z'));
	printf("%d", ft_isalnum('0'));
	printf("%d", ft_isalnum('5'));
	printf("%d\n", ft_isalnum('9'));
	printf("%d", ft_isalnum('.'));
	printf("%d", ft_isalnum('!'));
	printf("%d\n", ft_isalnum('|'));
}*/