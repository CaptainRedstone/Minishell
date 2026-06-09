/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:06:27 by ethrober          #+#    #+#             */
/*   Updated: 2025/10/15 12:42:55 by ethrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*dest;

	if ((start == 0 && len > ft_strlen(str)) || len >= ft_strlen(str))
		len = ft_strlen(str) - start;
	if (start > ft_strlen(str))
		len = 0;
	dest = (char *)malloc(len + 1);
	if (!dest)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (i >= start && j < len)
		{
			dest[j] = str[i];
			j++;
		}
		i++;
	}
	dest[j] = 0;
	return (dest);
}

/*size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *str)
{
	char	*dest;
	size_t	i;

	dest = (char *)malloc(sizeof(*str) * (ft_strlen(str) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

int	main(void)
{
	char *str;
	str = ft_strdup("0123456789");
	printf("%s\n", ft_substr(str, 9, 10));
}*/