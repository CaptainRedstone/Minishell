/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aforcada <aforcada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 20:28:47 by aforcada          #+#    #+#             */
/*   Updated: 2026/08/29 19:15:31 by aforcada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

# include "../includes/minishell.h"
# include "../includes/token.h"

/**
 * @brief Assuming `line` at `index` holds the leading char of 
 * a `token`, builds it.
 * @return	Memory allocated token, filled with relevant data.
 */
t_token	*build_token_at(char *line, size_t index);

/**
 * @brief Assuming `ctx` has `line` and `line_len` initialized,
 * extract a list of tokens from line (see `token.h`)
 * @return 1 on success, 0 on failure.
 */
int		tokenize(t_context *ctx);

#endif
