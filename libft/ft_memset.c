/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:14:42 by ethrober          #+#    #+#             */
/*   Updated: 2025/10/01 15:28:11 by ethrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*s;

	s = (unsigned char *)str;
	while (n--)
		*s++ = c;
	return (str);
}

/*int	main(void)
{
	char str[] = "Hello World !";
	int i;

	i = 0;

	ft_memset(str, 'x', 7);

	while(str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}*/