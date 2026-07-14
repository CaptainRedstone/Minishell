/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aforcada <aforcada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 16:34:31 by ethrober          #+#    #+#             */
/*   Updated: 2026/07/14 11:49:57 by aforcada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "tokenize.h"

typedef struct s_node		t_node;

struct s_cmd
{
	int		fd;
	char	*path;
	int		mode;
	char	*args;
};


/**
 * @brief Count number of tokens in array
 * 
 * @param arr array of strings with raw tokens
 * @return number of tokens
 */
int		count_tokens(char **arr);

/**
 * @brief Free memory allocation of tokens
 * 
 * @param ctx context with following field
 * @param tokens list of tokens
 */
void	free_tokens(t_context *ctx);

/**
 * @brief Print tokens in received order
 * 
 * @param ctx context with following field
 * @param tokens list of tokens
 */
void	print_tokens(t_context *ctx);

/**
 * @brief Fill token list from split string array
 * 
 * @param arr split string array with raw tokens
 * @param ctx context with following field
 * @param tokens empty list of tokens to be filled
 * 
 * @return 1 on success, else 0
 */
int		fill_tokens(t_context *ctx, char **arr);

/**
 * @brief	Split input line string into list of tokens for further parsing
 * 
 * @param ctx context with following fields
 * @param line raw string of input commands
 * @param tokens list of tokens to fill from line
 * @return 1 on success, else 0
 */
int		tokenize(t_context *ctx);

#endif
