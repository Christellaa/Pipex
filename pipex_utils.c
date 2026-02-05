/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:08:47 by cde-sous          #+#    #+#             */
/*   Updated: 2024/09/23 10:32:28 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_fd(char *file, int flags, int idx, t_pipex *pipex)
{
	int	fd;

	if (idx == 1)
	{
		fd = open(file, flags, 0644);
		if (fd < 0)
			print_msg(file);
		return (fd);
	}
	else if (idx == 2)
	{
		fd = open(file, flags, 0644);
		if (fd < 0)
			exit_process(pipex, file, 2);
		return (fd);
	}
	return (1);
}

void	check_dup2(t_pipex *pipex, int fd, int std)
{
	if (dup2(fd, std) == -1)
		exit_process(pipex, NULL, 1);
}

void	close_fds(t_cmd *cmd, t_pipex *pipex)
{
	while (cmd)
	{
		if (cmd->in > 0)
			close(cmd->in);
		if (cmd->out > 0)
			close(cmd->out);
		cmd = cmd->next;
	}
	if (pipex->infile > 0)
		close(pipex->infile);
	if (pipex->outfile > 0)
		close(pipex->outfile);
}
