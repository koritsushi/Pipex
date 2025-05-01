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
		close(data->pipes[index - 1][READ]);
		close(data->outfile_fd);
	}
	else
	{
		close(data->pipes[index - 1][READ]);
		close(data->pipes[index][WRITE]);
	}
}

void	close_pipe(t_pipex *data, int index)
{
	index = index + 1;
	while (index < data->cmd_count - 1)
	{
		close(data->pipes[index][READ]);
		close(data->pipes[index][WRITE]);
		index++;
	}
}

void	ft_child_process(t_pipex *data, int index)
{
	if (index == 0)
	{
		f_process(data, index);
		close_pipe(data, index);
	}
	else if (index == data->cmd_count - 1)
	{
		l_process(data, index);
	}
	else
	{
		m_process(data, index);
		close_pipe(data, index);
	}
}

void	ft_execute(t_pipex *data, char *cmd_paths, char **cmd_args, char **envp)
{
	if (execve(cmd_paths, cmd_args, envp) == -1)
	{
		write(2, "./pipex: execve() error!\n", 26);
		ft_exit_cleanup(data);
		exit(1);
	}
}
