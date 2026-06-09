/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:29:00 by ethrober          #+#    #+#             */
/*   Updated: 2025/10/13 12:41:09 by ethrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *str, char (*f)(unsigned int, char))
{
	char	*dest;
	int		i;

	dest = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (str[i])
	{
		dest[i] = f(i, str[i]);
		i++;
	}
	return (dest);
}
