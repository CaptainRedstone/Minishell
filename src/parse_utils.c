/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aforcada <aforcada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 16:09:39 by aforcada          #+#    #+#             */
/*   Updated: 2026/09/09 16:09:42 by aforcada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_tokens_upto(t_list *token_lst, int token_type)
{
	int		count;

	count = 0;
	if (!token_lst)
		return (0);
	while (token_lst
		&& ((t_token *)(token_lst->content))->type != token_type)
	{
		token_lst = token_lst->next;
		count++;
	}
	if (((t_token *)(token_lst->content))->type == token_type)
		return (count + 1);
	return (count);
}
