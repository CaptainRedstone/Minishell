/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 14:50:43 by ethrober          #+#    #+#             */
/*   Updated: 2026/10/08 14:50:43 by ethrober         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	read_digits(char *s, int neg, unsigned char *out)
{
	unsigned long long	n;
	unsigned long long	limit;

	limit = 9223372036854775807ULL + neg;
	n = 0;
	while (ft_isdigit(*s))
	{
		if (n > (limit - (*s - '0')) / 10)
			return (0);
		n = n * 10 + (*s - '0');
		s++;
	}
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s)
		return (0);
	*out = (unsigned char)n;
	if (neg)
		*out = (unsigned char)(0 - n);
	return (1);
}

/**
 * @brief	Parses the argument of exit like bash: optional blanks and
 *			sign, digits only, must fit in a long long.
 * @return	1 if numeric (code = value modulo 256), 0 otherwise.
 */
static int	parse_code(char *s, unsigned char *out)
{
	int	neg;

	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	neg = 0;
	if (*s == '+' || *s == '-')
	{
		neg = (*s == '-');
		s++;
	}
	if (!ft_isdigit(*s))
		return (0);
	return (read_digits(s, neg, out));
}

/**
 * @brief	Frees everything and exits the process.
 */
void	exit_shell(t_context *ctx, int status)
{
	free_line(ctx);
	ft_lstclear(&ctx->envp_lst, &free);
	if (ctx->saved_fd[0] >= 0)
		close(ctx->saved_fd[0]);
	if (ctx->saved_fd[1] >= 0)
		close(ctx->saved_fd[1]);
	rl_clear_history();
	exit(status);
}

/**
 * @brief	exit [n]: no argument = last status. Non numeric argument
 *			exits with 2. Too many arguments: error, does not exit.
 */
int	ft_exit(t_context *ctx, char **av)
{
	unsigned char	code;

	if (!ctx->is_child && isatty(STDIN_FILENO))
		ft_putendl_fd("exit", STDERR_FILENO);
	if (!av[1])
		exit_shell(ctx, ctx->exit_status);
	if (!parse_code(av[1], &code))
	{
		error_arg("exit", av[1], "numeric argument required");
		exit_shell(ctx, 2);
	}
	if (av[2])
		return (error("exit", "too many arguments"), 1);
	exit_shell(ctx, code);
	return (0);
}
