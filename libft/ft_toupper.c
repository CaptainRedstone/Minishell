/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:22:42 by ethrober          #+#    #+#             */
/*   Updated: 2025/10/03 12:30:30 by ethrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}

/*int main(void)
{
	printf("%d\n", ft_toupper('a'));
	printf("%d\n", ft_toupper('g'));
	printf("%d\n", ft_toupper('z'));
	printf("%d\n", ft_toupper('A'));
	printf("%d\n", ft_toupper('!'));
}*/