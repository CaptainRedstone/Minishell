/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:52:44 by ethrober          #+#    #+#             */
/*   Updated: 2025/10/13 13:46:57 by ethrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/*int	main(void)
{
	char str1[100] = "Ceci est un test"; // 16
	char str2[100] = "Hello World !";    // 13
	char str3[100] = "Hi there !";       // 10
	char str4[100] = "Yeaaaah";          // 07
	char str5[100] = "Whoops";           // 06
	char str6[100] = "";                 // 00
	printf("%d\n", ft_strlen(str1));
	printf("%d\n", ft_strlen(str2));
	printf("%d\n", ft_strlen(str3));
	printf("%d\n", ft_strlen(str4));
	printf("%d\n", ft_strlen(str5));
	printf("%d\n", ft_strlen(str6));
}*/