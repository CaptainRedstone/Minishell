/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 14:51:29 by ethrober          #+#    #+#             */
/*   Updated: 2026/10/08 14:51:29 by ethrober         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief	Prints "MiniShell > command > error" on stderr.
 */
void	error(char *command, char *error)
{
	ft_putstr_fd(BRED "MiniShell" BWHITE " > " BRED, 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(BWHITE " > " BRED, 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n" RESET, 2);
}

/**
 * @brief	Same as error() with an argument: "cmd > arg: msg".
 */
void	error_arg(char *cmd, char *arg, char *msg)
{
	ft_putstr_fd(BRED "MiniShell" BWHITE " > " BRED, 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(BWHITE " > " BRED, 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n" RESET, 2);
}
