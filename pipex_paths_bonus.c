/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_paths_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 11:07:01 by cde-sous          #+#    #+#             */
/*   Updated: 2024/09/23 10:51:54 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**get_paths(char **env)
{
	int		i;
	char	*path;
	char	**paths;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = ft_strdup(env[i] + 5);
			if (!path)
				return (NULL);
			paths = ft_split(path, ':');
			free(path);
			return (paths);
		}
		i++;
	}
	return (NULL);
}

int	is_valid_absolute_path(char *cmd)
{
	if ((ft_strncmp(cmd, "/", 1) == 0 || ft_strncmp(cmd, "./", 2) == 0) \
	&& access(cmd, F_OK | X_OK) == 0)
		return (1);
	return (0);
}

char	*is_valid_relative_path(char *cmd, char **paths)
{
	int		i;
	char	*tmp;
	char	*path;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (NULL);
		path = ft_strjoin_free_s1(tmp, cmd);
		if (!path)
			return (NULL);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, char **paths)
{
	char	*relative_path;

	if (!cmd)
	{
		ft_dprintf(2, "%s: Command not found\n", cmd);
		return (NULL);
	}
	if (paths)
	{
		if (is_valid_absolute_path(cmd))
			return (ft_strdup(cmd));
		relative_path = is_valid_relative_path(cmd, paths);
		if (relative_path)
			return (relative_path);
	}
	else
	{
		if (is_valid_absolute_path(cmd))
			return (ft_strdup(cmd));
	}
	if (ft_strncmp(cmd, "/", 1) == 0 || ft_strncmp(cmd, "./", 2) == 0)
		ft_dprintf(2, "%s: No such file or directory\n", cmd);
	else
		ft_dprintf(2, "%s: Command not found\n", cmd);
	return (NULL);
}
