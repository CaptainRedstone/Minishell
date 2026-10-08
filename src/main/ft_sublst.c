/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sublst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 14:51:40 by ethrober          #+#    #+#             */
/*   Updated: 2026/10/08 14:51:40 by ethrober         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"

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
