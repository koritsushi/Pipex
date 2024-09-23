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
		close(data->pipes[index][write]);
		close(data->infile_fd);
	}
	else if (index == data->cmd_count)
	{
		close(data->pipes[index - 1][write]);
		close(data->outfile_fd);
	}
	else
	{
		close(data->pipes[index - 1][read]);
		close(data->pipes[index][write]);
	}
}

void	ft_child_process(t_pipex *data, int index, char **envp)
{
	if (index == 0)
	{
		close(data->pipes[index][read]);
		if (data->is_invalid_infile == 0)
			dup2(data->infile_fd, STDIN_FILENO);
		dup2(data->pipes[index][write], STDOUT_FILENO);
		close(data->pipes[index][write]);
		close(data->infile_fd);
	}
	else if (index == data->cmd_count + 1)
	{
		close(data->pipes[index - 1][write]);
		dup2(data->pipes[index - 1][read], STDIN_FILENO);
		dup2(data->outfile_fd, STDOUT_FILENO);
		close(data->pipes[index - 1][read]);
		close(data->outfile_fd);
	}
	else
	{
		close(data->pipes[index - 1][write]);
		dup2(data->pipes[index - 1][read], STDIN_FILENO);
		dup2(data->pipes[index][write], STDOUT_FILENO);
		close(data->pipes[index][read]);
	}
	if (execve(data->cmd_paths[index], data->cmd_args[index], envp) == -1)
	{
		fprintf(stderr, "./pipex: execve error! command: %s.\n", data->cmd_paths[index]);
		exit(1);
	}
}
