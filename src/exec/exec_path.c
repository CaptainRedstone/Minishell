/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethrober <ethrober@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 14:48:30 by ethrober          #+#    #+#             */
/*   Updated: 2026/10/08 14:48:30 by ethrober         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*try_dir(char *dir, char *name, int *perm)
{
	char		*tmp;
	char		*cand;
	struct stat	st;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	cand = join_and_free(tmp, name);
	if (cand && stat(cand, &st) == 0 && !S_ISDIR(st.st_mode))
	{
		if (access(cand, X_OK) == 0)
			return (cand);
		*perm = 1;
	}
	free(cand);
	return (NULL);
}

static char	*path_fail(char *name, int perm, int *code)
{
	*code =	127;
	if (perm)
	{
		*code = 126;
		error(name, "Permission denied");
	}
	else
		error(name, "command not found");
	return (NULL);
}

/**
 * @brief	Looks for name in each directory of $PATH (our own copy of
 *			the environment, so "unset PATH" works).
 */
static char	*search_path(t_context *ctx, char *name, int *code)
{
	char	**dirs;
	char	*res;
	int		perm;
	int		i;

	dirs = NULL;
	if (get_env(ctx, "PATH"))
		dirs = ft_split(get_env(ctx, "PATH"), ':');
	if (!dirs)
	{
		*code = 127;
		return (error(name, "No such file or directory"), NULL);
	}
	perm = 0;
	res = NULL;
	i = 0;
	while (dirs[i] && !res)
	{
		res = try_dir(dirs[i], name, &perm);
		i++;
	}
	free_array(dirs);
	if (res)
		return (res);
	return (path_fail(name, perm, code));
}

/**
 * @brief	Name contains a '/': it is used as a path, no PATH lookup.
 */
static char	*check_path(char *name, int *code)
{
	struct stat	st;

	if (stat(name, &st) < 0)
	{
		*code = 126;
		if (errno == ENOENT)
			*code = 127;
		return (error(name, strerror(errno)), NULL);
	}
	if (S_ISDIR(st.st_mode))
	{
		*code = 126;
		return (error(name, "Is a directory"), NULL);
	}
	if (access(name, X_OK) < 0)
	{
		*code = 126;
		return (error(name, "Permission denied"), NULL);
	}
	return (ft_strdup(name));
}

/**
 * @brief	Finds the file to execute for the command name.
 * @param	code Set to 126 / 127 when the command cannot be run.
 * @return	Allocated path, or NULL (error already printed).
 */
char	*resolve_command(t_context *ctx, char *name, int *code)
{
	if (!name[0])
	{
		*code = 127;
		return (error(name, "command not found"), NULL);
	}
	if (ft_strchr(name, '/'))
		return (check_path(name, code));
	return (search_path(ctx, name, code));
}
