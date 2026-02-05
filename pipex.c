/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 20:06:35 by cde-sous          #+#    #+#             */
/*   Updated: 2024/09/23 10:10:08 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	wait_pids(t_pipex *pipex)
{
	int		status_info;
	int		exit_code;
	t_cmd	*last_cmd;
	pid_t	pid;

	exit_code = 0;
	last_cmd = pipex->cmds;
	while (last_cmd->next)
		last_cmd = last_cmd->next;
	while (errno != ECHILD)
	{
		pid = waitpid(-1, &status_info, 0);
		if (pid == -1)
			break ;
		if (pid == last_cmd->pid)
		{
			if (WIFEXITED(status_info))
				exit_code = WEXITSTATUS(status_info);
		}
	}
	return (exit_code);
}

int	children(t_pipex *pipex)
{
	int		pid_status;
	t_cmd	*tmp;

	tmp = pipex->cmds;
	create_pipes(tmp);
	while (tmp)
	{
		tmp->pid = child(tmp, pipex);
		tmp = tmp->next;
	}
	tmp = pipex->cmds;
	close_fds(tmp, pipex);
	pid_status = wait_pids(pipex);
	free_cmds(pipex->cmds);
	free_groups(pipex->paths);
	if (pipex->outfile < 0)
		pid_status = 1;
	return (pid_status);
}

void	parent(int ac, char **av, t_pipex *pipex)
{
	pipex->infile = open_fd(av[1], O_RDONLY, 1, pipex);
	if (pipex->infile < 0)
		pipex->cmd_start++;
	pipex->outfile = open_fd(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, \
	1, pipex);
	if (pipex->outfile < 0)
		pipex->cmd_end--;
	if (pipex->cmd_end < pipex->cmd_start)
		exit_process(pipex, NULL, 2);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;
	t_cmd	*cmds;

	init_pipex(&pipex, ac);
	if (ac != 5)
		exit_process(&pipex, USAGE, 2);
	parent(ac, av, &pipex);
	pipex.env = env;
	av[ac - 1] = NULL;
	pipex.paths = get_paths(env);
	cmds = get_cmds(&av[pipex.cmd_start], pipex.paths, &pipex);
	pipex.cmds = cmds;
	return (children(&pipex));
}
