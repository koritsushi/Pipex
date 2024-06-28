/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:28:24 by mliyuan           #+#    #+#             */
/*   Updated: 2024/06/28 19:36:03 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_child_process(t_pipex *data, int index, int cmd, char **envp)
{
	int	i;
	int	j;

	if (index == 0)
	{
		dup2(data->infile_fd, STDIN_FILENO);
		close(data->infile_fd);
		fprintf(stderr, "infile\n");
	}
	else
	{
		dup2(data->pipes[index][read], STDIN_FILENO);
		close(data->pipes[index + 1][write]);
	}
	if (index + 1 == data->cmd_count)
	{
		dup2(data->outfile_fd, STDOUT_FILENO);
		close(data->outfile_fd);
		fprintf(stderr, "outfile\n");
	}
	else
	{
		dup2(data->pipes[index + 1][write], STDOUT_FILENO);
		close(data->pipes[index][read]);
	}
	i = -1;
	j = 1;
	if (execve(data->cmd_paths[cmd], ft_split(data->cmd_args[cmd], ' '), envp) == -1)
		(ft_printf("./pipex: invalid command %s\n", data->cmd_paths[i]), exit(1));
	return ;
}
