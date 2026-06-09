/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:45:57 by ethrober          #+#    #+#             */
/*   Updated: 2025/10/20 11:58:04 by ethrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *str, char c)
{
	int	words;
	int	i;

	i = 0;
	while (str[i] && str[i] == c)
		i++;
	if (ft_strlen(str + i) > 0)
		words = 1;
	else
		words = 0;
	while (str[i])
	{
		if (str[i] == c && str[i + 1] && str[i + 1] != c)
			words++;
		i++;
	}
	return (words);
}

static int	len_word(char const *str, char c)
{
	int	i;
	int	chars;

	chars = 0;
	i = 0;
	while (str[i] && str[i] == c)
		i++;
	while (str[i] && str[i] != c)
	{
		chars++;
		i++;
	}
	return (chars);
}

static int	fill_word(char *word, char const *str, char c)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] && str[i] == c)
		i++;
	j = 0;
	while (str[i] && str[i] != c)
		word[j++] = str[i++];
	word[j] = '\0';
	while (str[i] && str[i] == c)
		i++;
	return (i);
}

void	emergency_clean(char **array, int arr_i)
{
	while (--arr_i >= 0)
		free(array[arr_i]);
	free(array);
}

char	**ft_split(char const *str, char c)
{
	char	**array;
	int		arr_i;

	array = NULL;
	array = malloc(sizeof(char *) * (count_words(str, c) + 1));
	if (str && array)
	{
		arr_i = 0;
		if (count_words(str, c))
		{
			while (*str)
			{
				array[arr_i] = malloc(len_word(str, c) + 1);
				if (array)
					str += fill_word(array[arr_i++], str, c);
				else
				{
					emergency_clean(array, arr_i);
					return (NULL);
				}
			}
		}
		array[arr_i] = NULL;
	}
	return (array);
}
