/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sublst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aforcada <aforcada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 16:05:28 by aforcada          #+#    #+#             */
/*   Updated: 2026/09/09 16:06:07 by aforcada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

static t_list	*safe_next(t_list *node)
{
	if (node)
		return (node->next);
	else
		return (NULL);
}

t_list	*ft_sublst(t_list **lst, int start, int len)
{
	t_list	*prev;
	t_list	*head;
	t_list	*node;

	if (!lst || !(*lst) || start < 0 || len < 1)
		return (NULL);
	prev = NULL;
	head = *lst;
	while (head && start--)
	{
		prev = head;
		head = head->next;
	}
	node = head;
	while (node && --len)
		node = node->next;
	if (prev)
		prev->next = safe_next(node);
	else
		*lst = safe_next(node);
	if (node)
		node->next = NULL;
	return (head);
}
