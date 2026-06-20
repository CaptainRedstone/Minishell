/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aforcada <aforcada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 10:43:09 by aforcada          #+#    #+#             */
/*   Updated: 2026/06/20 16:09:24 by aforcada         ###   ########.fr       */
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
	printf("ok 3\n");
	while(*arr++)
		count++;
	return (count);
}

int	fill_tokens(t_token *tk, const char **arr)
{
	const char	**curr;

	if (!tk)
		return (free_array((char **)arr), 0);
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
	return (free_array((char **)arr), 1);
}

void	print_tokens(const t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens && tokens->val)
	{
		printf("token[%d]: %s\n", i++, tokens->val);
		tokens++;
	}
}

int	tokenize(char *line, t_token *tokens[])
{
	const char	**arr;

	if (!line)
		return (0);
	arr = (const char **)ft_split(line, ' ');
	tokens[0] = malloc((count_tokens(arr) + 1) * sizeof(t_token));
	if (!fill_tokens(tokens[0], arr))
		return (free(tokens[0]), 0);
	print_tokens(tokens[0]);
	return (1);
}
