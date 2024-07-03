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

void	ft_child_process(t_pipex *data, int index, int cmd, char **envp)
{
	fprintf(stderr, "index: %d data->cmd_paths[index]: %s\n", index, data->cmd_paths[index]);
	fprintf(stderr, "index: %d ", index);
	if (index == 0 && data->is_invalid_infile == 0)
	{
		dup2(data->infile_fd, STDIN_FILENO);
		close(data->infile_fd);
		fprintf(stderr, " dup infile and");
	}
	else
	{
		dup2(data->pipes[index][write], STDOUT_FILENO);
		close(data->pipes[index][read]);
		fprintf(stderr, " dup write and");
	}
	if (index == data->cmd_count)
	{
		dup2(data->outfile_fd, STDOUT_FILENO);
		close(data->outfile_fd);
		fprintf(stderr, " dup outfile\n");
	}
	else
	{
		dup2(data->pipes[index][read], STDIN_FILENO);
		close(data->pipes[index][write]);
		fprintf(stderr, " dup read\n");
	}
	if (execve(data->cmd_paths[cmd], data->cmd_args[cmd], envp) == -1)
	{
		fprintf(stderr, "./pipex: execve error! command: %s.\n", data->cmd_paths[cmd]);
		exit(1);
	}
}
