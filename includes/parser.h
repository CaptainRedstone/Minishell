/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aforcada <aforcada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 15:18:09 by aforcada          #+#    #+#             */
/*   Updated: 2026/06/09 15:43:38 by aforcada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_token	t_token;

struct s_token
{
	char	*name;
	int		type;
	t_token	*next;
};

struct s_pipe
{
	
};
