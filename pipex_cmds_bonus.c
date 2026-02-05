/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_cmds_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 11:10:37 by cde-sous          #+#    #+#             */
/*   Updated: 2024/09/22 17:55:33 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**copy_args(char **args)
{
	char	**copy;
	int		i;

	i = 0;
	while (args[i])
		++i;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (args[i])
	{
		copy[i] = ft_strdup(args[i]);
		if (!copy[i])
			return (NULL);
		++i;
	}
	copy[i] = NULL;
	return (copy);
}

t_cmd	*create_cmd(char *cmd_path, char **args)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	if (!cmd_path)
	{
		cmd->name = NULL;
		cmd->args = NULL;
		cmd->next = NULL;
		cmd->pid = -1;
		return (cmd);
	}
	cmd->name = cmd_path;
	cmd->args = copy_args(args);
	if (!cmd->args)
		return (NULL);
	cmd->next = NULL;
	return (cmd);
}

void	cmd_add_back(t_cmd **head, t_cmd *new)
{
	t_cmd	*last;

	if (!*head)
	{
		*head = new;
		new->is_first = 1;
		new->is_last = 1;
		new->next = NULL;
		return ;
	}
	last = *head;
	while (last->next)
		last = last->next;
	last->next = new;
	last->is_last = 0;
	new->is_first = 0;
	new->is_last = 1;
	new->next = NULL;
}

t_cmd	*get_cmds(char **cmd, char **paths, t_pipex *pipex)
{
	t_cmd	*cmds;
	t_cmd	*tmp;
	char	**args;
	char	**next;

	cmds = NULL;
	next = cmd;
	if (!next)
		return (NULL);
	while (*next && pipex->cmd_start <= pipex->cmd_end)
	{
		args = ft_split(*next, ' ');
		tmp = create_cmd(get_cmd_path(args[0], paths), args);
		if (!tmp)
			return (NULL);
		cmd_add_back(&cmds, tmp);
		free_groups(args);
		++next;
		++pipex->cmd_start;
	}
	return (cmds);
}
