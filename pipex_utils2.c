/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:28:24 by mliyuan           #+#    #+#             */
/*   Updated: 2024/06/27 16:00:09 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_child_process(t_pipex *data, int index, int argc, char **argv, char **envp)
{
	int	i;
	int	j;

	if (index == 0 && data->is_invalid_infile == 0)
	{
		ft_infile_fd(data, index);
		return ;
	}
	else if (index == argc - 1)
	{
		ft_outfile_fd(data, index);
		return ;
	}
	i = -1;
	j = 0;
	dup2(data->pipes[index][write], STDOUT_FILENO);
	close(data->pipes[index][write]);
	while (data->cmd_paths[++i] != NULL && ++j < argc - 1)
	{
		if (execve(data->cmd_paths[i], &argv[j], envp) == -1)
		{
			ft_printf("./pipex: execve() function error!\n");
			exit(1);
		}
	}
	return ;
}

void	ft_infile_fd(t_pipex *data, int index)
{
	char	*buffer;

	dup2(data->pipes[index][write], STDOUT_FILENO);
	close(data->pipes[index][write]);
	buffer = get_next_line(data->infile_fd);
	if (buffer == NULL)
		return ;
	ft_putstr_fd(buffer, data->pipes[index][read]);
	close(data->infile_fd);
	close(data->pipes[index][read]);
	return ;
}

void	ft_outfile_fd(t_pipex *data, int index)
{
	char	*buffer;

	close(data->pipes[index][read]);
	buffer = get_next_line(data->pipes[index][write]);
	if (buffer == NULL)
		return ;
	ft_putstr_fd(buffer, data->outfile_fd);
	close(data->outfile_fd);
	close(data->pipes[index][write]);
	return ;
}
