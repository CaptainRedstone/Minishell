/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 14:45:24 by ethrober          #+#    #+#             */
/*   Updated: 2026/10/09 18:50:55 by ethrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_welcome(t_context *ctx)
{
	char	*welcome;
	char	*user;

	user = get_env(ctx, "USER");
	if (!user)
		user = "user";
	welcome = ft_strjoin(BRED "\nWelcome to MiniShell ", user);
	welcome = join_and_free(welcome, " !\n\n" RESET);
	ft_putstr_fd(welcome, STDOUT_FILENO);
	free(welcome);
}
