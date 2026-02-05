/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_children.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 12:02:24 by cde-sous          #+#    #+#             */
/*   Updated: 2024/09/23 10:39:11 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	create_pipes(t_cmd *cmd)
{
	t_cmd	*current;
	int		pipefd[2];

	current = cmd;
	while (current)
	{
		if (current->is_first)
			current->in = -1;
		current->out = -1;
		if (current->next)
		{
			if (pipe(pipefd) == -1)
				exit_process(NULL, "Pipe", 2);
			current->out = pipefd[1];
			current->next->in = pipefd[0];
		}
		current = current->next;
	}
}

void	dup_files(t_cmd *cmd, t_pipex *pipex)
{
	int	null_fd;

	if (cmd->is_first && pipex->infile > 0)
		check_dup2(pipex, pipex->infile, STDIN_FILENO);
	else if (cmd->in == -1)
	{
		null_fd = open_fd("/dev/null", O_RDONLY, 2, pipex);
		check_dup2(pipex, null_fd, STDIN_FILENO);
		close(null_fd);
	}
	else
		check_dup2(pipex, cmd->in, STDIN_FILENO);
	if (cmd->is_last && cmd->name != NULL && pipex->outfile > 0)
		check_dup2(pipex, pipex->outfile, STDOUT_FILENO);
	else if (cmd->out == -1)
	{
		null_fd = open_fd("/dev/null", O_WRONLY, 2, pipex);
		check_dup2(pipex, null_fd, STDOUT_FILENO);
		close(null_fd);
	}
	else
		check_dup2(pipex, cmd->out, STDOUT_FILENO);
	close_fds(pipex->cmds, pipex);
}

pid_t	child(t_cmd *cmd, t_pipex *pipex)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit_process(pipex, "Fork", 2);
	if (pid == 0)
	{
		dup_files(cmd, pipex);
		if (cmd->name == NULL)
			exit_process(pipex, cmd->name, 1);
		if (execve(cmd->name, cmd->args, pipex->env) == -1)
			exit_process(pipex, cmd->name, 1);
	}
	return (pid);
}
