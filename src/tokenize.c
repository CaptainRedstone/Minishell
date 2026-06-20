/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aforcada <aforcada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 10:43:09 by aforcada          #+#    #+#             */
/*   Updated: 2026/06/20 11:58:09 by aforcada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/colors.h"
#include "../includes/includes.h"
#include "../includes/minishell.h"
#include "../includes/parser.h"

int	count_tokens(const char **arr)
{
	int	count;

	count = 0;
	if (!arr)
		return (count);
	while(*arr++)
		count++;
	return (count);
}

int	fill_tokens(t_token *tk, char **arr)
{
	char	**curr;

	if (!tk)
		return (free_array(arr), 0);
	curr = arr;
	while (*curr)
	{
		if (ft_strncmp(*curr, "|", 2))
			(*tk).type = e_pipe;
		else if (ft_strncmp(*curr, ">", 2) || ft_strncmp(*curr, ">>", 3))
			(*tk).type = e_right_redir;
		else if (ft_strncmp(*curr, "<", 2) || ft_strncmp(*curr, "<<", 3))
			(*tk).type = e_left_redir;
		else
			(*tk).type = e_word;
		(*tk++).val = ft_strdup(*curr);
		curr++;
	}
	(*tk).type = e_null;
	(*tk).val = NULL;
	return (free_array(arr), 1);
}

/**
 * @brief	Split string in tokens for parsing
 */
t_token	*tokenize(char *line)
{
	t_token	*tk;
	char	**arr;

	if (!line)
		return (NULL);
	if (!ft_strchr(line, '\'') && !ft_strchr(line, '\"'))
	{
		arr = ft_split(line, ' ');
		tk = malloc((count_tokens(arr) + 1) * sizeof(t_token));
		if (!fill_tokens(tk, arr))
			return (free(tk), NULL);
	}
}
