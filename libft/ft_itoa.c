/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:19:54 by ethrober          #+#    #+#             */
/*   Updated: 2025/10/13 15:01:55 by ethrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_digit_count(long int i)
{
	int	count;

	count = 0;
	if (i == 0)
	{
		count = 1;
		return (count);
	}
	if (i < 0)
	{
		i *= -1;
		count++;
	}
	while (i > 0)
	{
		i /= 10;
		count++;
	}
	return (count);
}

char	*ft_strcreate(long int nb, int i, char *str)
{
	if (nb == 0)
		str[0] = '0';
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	while (nb > 0)
	{
		str[i--] = nb % 10 + '0';
		nb /= 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			i;
	long int	nb;

	nb = n;
	i = ft_digit_count(nb);
	str = ft_calloc(i + 1, sizeof(char));
	if (!str)
		return (0);
	str[i--] = 0;
	str = ft_strcreate(nb, i, str);
	return (str);
}

// void	*ft_calloc(size_t count, size_t size)
// {
// 	size_t	total_size;
// 	void	*ptr;

// 	total_size = count * size;
// 	ptr = malloc(total_size);
// 	if (ptr == NULL)
// 		return (NULL);
// 	ft_memset(ptr, 0, total_size);
// 	return (ptr);
// }

// void	*ft_memset(void *str, int c, size_t n)
// {
// 	unsigned char	*s;

// 	s = (unsigned char *)str;
// 	while (n--)
// 		*s++ = c;
// 	return (str);
// }

// int	main(void)
// {
// 	char *str;

// 	str = ft_itoa(156);
// 	printf("156\t\t= %s\n", str);
// 	free(str);
// 	str = ft_itoa(0);
// 	printf("0\t\t= %s\n", str);
// 	free(str);
// 	str = ft_itoa(-0);
// 	printf("-0\t\t= %s\n", str);
// 	free(str);
// 	str = ft_itoa(-623);
// 	printf("-623\t\t= %s\n", str);
// 	free(str);
// 	str = ft_itoa((-2147483647 -1));
// 	printf("-2147483648\t= %s\n", str);
// 	free(str);
// 	str = ft_itoa(2147483647);
// 	printf("2147483647\t= %s\n", str);
// 	free(str);
// }