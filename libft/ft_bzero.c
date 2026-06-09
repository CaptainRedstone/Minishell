/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:50:14 by ethrober          #+#    #+#             */
/*   Updated: 2025/10/01 15:27:47 by ethrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, size_t n)
{
	unsigned char	*s;

	s = (unsigned char *)str;
	while (n--)
		*s++ = '\0';
}

/*int	main(void)
{
	char str[] = "Hello World !";
	int i;

	i = 0;

	ft_bzero(str, 5);

	while(i <= 13)
	{
		write(1, &str[i], 1);
		i++;
	}
}*/