/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:33:57 by ethrober          #+#    #+#             */
/*   Updated: 2025/10/03 12:30:22 by ethrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}

/*int	main(void)
{
	printf("%d\n", ft_tolower('A'));
	printf("%d\n", ft_tolower('G'));
	printf("%d\n", ft_tolower('Z'));
	printf("%d\n", ft_tolower('a'));
	printf("%d\n", ft_tolower('!'));
}*/