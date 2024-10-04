/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 23:41:57 by mliyuan           #+#    #+#             */
/*   Updated: 2024/07/03 18:00:05 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_parent_process(t_pipex *data, int index)
{
	if (index == 0)
	{
		close(data->pipes[index][WRITE]);
		close(data->infile_fd);
	}
	else if (index == data->cmd_count - 1)
	{
		close(data->pipes[index - 1][WRITE]);
		close(data->outfile_fd);
	}
	else
	{
		close(data->pipes[index - 1][READ]);
		close(data->pipes[index][WRITE]);
	}
}

void	ft_child_process(t_pipex *data, int index)
{
	if (index == 0)
	{
		close(data->pipes[index][READ]);
		if (data->is_invalid_infile == 0)
			dup2(data->infile_fd, STDIN_FILENO);
		dup2(data->pipes[index][WRITE], STDOUT_FILENO);
		close(data->pipes[index][WRITE]);
		close(data->infile_fd);
	}
	else if (index == data->cmd_count - 1)
	{
		close(data->pipes[index - 1][WRITE]);
		dup2(data->pipes[index - 1][READ], STDIN_FILENO);
		dup2(data->outfile_fd, STDOUT_FILENO);
		close(data->pipes[index - 1][READ]);
		close(data->outfile_fd);
	}
	else
	{
		close(data->pipes[index - 1][WRITE]);
		dup2(data->pipes[index - 1][READ], STDIN_FILENO);
		dup2(data->pipes[index][WRITE], STDOUT_FILENO);
		close(data->pipes[index][READ]);
	}
}

void	ft_execute(t_pipex *data, char *cmd_paths, char **cmd_args, char **envp)
{
	if (execve(cmd_paths, cmd_args, envp) == -1)
	{
		fprintf(stderr, "./pipex: execve() error! command: %s\n", cmd_paths);
		ft_exit_cleanup(data);
		exit(1);
	}
}
