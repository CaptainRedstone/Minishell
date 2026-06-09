/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 12:41:13 by ethrober          #+#    #+#             */
/*   Updated: 2025/10/01 15:31:02 by ethrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/*int	main(void)
{
	printf("%d", ft_isalpha('a'));
	printf("%d", ft_isalpha('z'));
	printf("%d", ft_isalpha('A'));
	printf("%d", ft_isalpha('Z'));
	printf("%d", ft_isalpha('!'));
	printf("%d", ft_isalpha('1'));
}*/