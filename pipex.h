/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 10:49:44 by cde-sous          #+#    #+#             */
/*   Updated: 2024/09/23 09:14:31 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/wait.h>
# include "libft/libft.h"

# define USAGE "Usage: ./pipex file1 cmd1 cmd2 file2\n"

typedef struct s_cmd
{
	char			*name;
	char			**args;
	int				in;
	int				out;
	int				is_first;
	int				is_last;
	pid_t			pid;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_pipex
{
	char	**env;
	char	**paths;
	int		infile;
	int		outfile;
	t_cmd	*cmds;
	int		cmd_start;
	int		cmd_end;
}	t_pipex;

// pipex_cleanup.c
void	free_groups(char **groups);
void	free_cmds(t_cmd *cmd);
void	print_msg(char *msg);
void	exit_process(t_pipex *pipex, char *msg, int exit_type);
void	init_pipex(t_pipex *pipex, int ac);
// pipex_paths.c
char	**get_paths(char **env);
int		is_valid_absolute_path(char *cmd);
char	*is_valid_relative_path(char *cmd, char **paths);
char	*get_cmd_path(char *cmd, char **paths);
// pipex_cmds.c
char	**copy_args(char **args);
t_cmd	*create_cmd(char *cmd_path, char **args);
void	cmd_add_back(t_cmd **head, t_cmd *new);
t_cmd	*get_cmds(char **cmd, char **paths, t_pipex *pipex);
// pipex_children.c
void	create_pipes(t_cmd *cmd);
void	dup_files(t_cmd *cmd, t_pipex *pipex);
pid_t	child(t_cmd *cmd, t_pipex *pipex);
// pipex_utils.c
int		open_fd(char *file, int flags, int idx, t_pipex *pipex);
void	check_dup2(t_pipex *pipex, int fd, int std);
void	close_fds(t_cmd *cmd, t_pipex *pipex);

#endif